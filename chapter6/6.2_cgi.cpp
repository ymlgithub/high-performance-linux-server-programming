/**
 * g++ chapter6/6.2_cgi.cpp -o cgi.app && ./cgi.app 127.0.0.1 12345
 * 
 * telnet 127.0.0.1 12345
 * 
 * 代码 6-1 CGI服务器原理
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

    struct sockaddr_in client;
    socklen_t client_addrlength = sizeof(client);
    int conn_fd = accept(sock, (struct sockaddr *)&client, &client_addrlength);
    if (conn_fd < 0)
    {
        cout << "Error:" << errno << endl;
    }
    else
    { //连接成功
        close(STDOUT_FILENO);
        // dup创建新的文件描述符，它与原有文件描述符指向相同的文件
        // 总是返回系统中最小的可用文件描述符，所以返回值实际是1，即STDOUT_FILENO
        // dup2函数返回第一个不小于file_descriptor_two的整数值
        int new_fd = dup(conn_fd);
        cout << "fd=" << new_fd << endl;
        cout << "hello!" << endl;

        close(conn_fd);
    }

    //关闭socket
    close(sock);

    return 0;
}