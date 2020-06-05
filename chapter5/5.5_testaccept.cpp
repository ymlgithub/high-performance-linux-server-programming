/**
 * g++ chapter5/5.5_testaccept.cpp -o testaccept.app && ./testaccept.app 127.0.0.1 12345
 * 
 * telnet 127.0.0.1 12345
 * 
 * netstat -nt | grep 12345
 * 
 * 代码 5-5 接受一个异常连接
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

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        cout << "Usage: " << argv[0] << " IP port" << endl;
        return 1;
    }
    const char *ip = argv[1];
    int port = atoi(argv[2]);

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
    ret = listen(sock, 3);
    assert(ret != -1);

    // 暂停，等待客户端操作结束
    sleep(20);

    struct sockaddr_in client;
    socklen_t client_addrlength = sizeof(client);
    int conn_fd = accept(sock, (struct sockaddr *)&client, &client_addrlength);
    if (conn_fd < 0)
    {
        cout << "Error:" << errno << endl;
    }
    else
    { //连接成功，打印客户端端口号和IP
        char remote[INET_ADDRSTRLEN];
        printf("Connected IP: %s ,Port: %d\n", inet_ntop(AF_INET, &client.sin_addr, remote, INET_ADDRSTRLEN), ntohs(client.sin_port));
        close(conn_fd);
    }

    //关闭socket
    close(sock);

    return 0;
}