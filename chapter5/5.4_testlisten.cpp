/**
 * g++ chapter5/5.4_testlisten.cpp -o testlisten.app && ./testlisten.app 127.0.0.1 12345 3
 * 
 * telnet 127.0.0.1 12345 # 多次执行
 * 
 * netstat -nt | grep 12345
 * 
 * 代码 5-3 backlog参数
 */

#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <signal.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
using namespace std;

static bool stop = false;

static void handle_term(int sig)
{
    stop = true;
}

int main(int argc, char *argv[])
{
    signal(SIGTERM, handle_term);
    if (argc <= 3)
    {
        cout << "Usage: " << argv[0] << " IP port backlog" << endl;
        return 1;
    }
    const char *ip = argv[1];
    int port = atoi(argv[2]);
    int backlog = atoi(argv[3]);

    int sock = socket(PF_INET, SOCK_STREAM, 0);
    assert(sock > 0);
    // 创建一个IPv4 socket地址
    struct sockaddr_in address;
    bzero(&address, sizeof(address));
    address.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &address.sin_addr);
    address.sin_port = htons(port);

    // 命名socket
    int ret = bind(sock, (struct sockaddr *)&address, sizeof(address));
    assert(ret != -1);

    // 开始监听
    cout << "backlog : " << backlog << endl;
    ret = listen(sock, backlog);
    assert(ret != -1);

    while (!stop)
    {
        sleep(1);
    }
    //关闭socket
    close(sock);

    return 0;
}