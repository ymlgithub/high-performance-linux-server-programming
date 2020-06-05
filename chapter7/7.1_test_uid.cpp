/**
 * g++ chapter7/7.1_test_uid.cpp -o test_uid.app
 * 
 * sudo chown root:root test_uid.app
 * #设置目标文件的set-user-id标志，使得运行程序的用户拥有该程序有效用户的权限
 * sudo chmod +s test_uid.app 
 * 
 * ./test_uid.app
 * 
 * 代码 7-1 测试进程的UID和EUID
 */

#include <iostream>
#include <unistd.h>
using namespace std;

int main()
{
    uid_t uid = getuid();
    uid_t euid = geteuid();
    cout << "UID: " << uid << " EUID: " << euid << endl;
    return 0;
}