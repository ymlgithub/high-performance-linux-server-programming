/**
 * g++ chapter5/5.1_byteorder.cpp -o out.app && ./out.app
 * 
 * 代码5-1 判断机器字节序
 */

#include <iostream>
using namespace std;

// 字节序转换函数：
#include <netinet/in.h>
unsigned long int htonl(unsigned long int hostlong);
unsigned short int htons(unsigned short int hostlong);
unsigned long int ntohl(unsigned long int netlong);
unsigned short int ntohs(unsigned short int netshort);

int main()
{

    union {
        short value;
        char union_bytes[sizeof(short)];
    } test;

    test.value = 0x0102;

    if ((test.union_bytes[0] == 1) && (test.union_bytes[1] == 2))
    {
        cout << "Big Endian" << endl;
    }
    else if ((test.union_bytes[0] == 2) && (test.union_bytes[1] == 1))
    {
        cout << "Little Endian" << endl; //实际输出
    }
    else
    {
        cout << "Unknown..." << endl;
    }

    return 0;
}