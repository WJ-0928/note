/*=============================================================== 
*   Copyright (C) . All rights reserved.")
*   文件名称： 
*   创 建 者：zhang
*   创建日期：
*   描    述：通过封装的TcpSocket类实例化对象实现tcp客户端程序 
================================================================*/

#include <iostream>
#include <stdlib.h>
#include <signal.h>
#include "tcpsocket.hpp"

void sigcb(int signo)
{
    printf("连接已经断开，继续发送数据触发异常SIGPIPE信号\n");
}
int main(int argc, char *argv[])
{
    if (argc != 3) {
        printf("em:./tcp_cli 192.168.122.132 9000--服务绑定的地址\n");
        return -1;
    }
    signal(SIGPIPE, sigcb);
    std::string ip = argv[1];
    uint16_t port = atoi(argv[2]);
    TcpSocket cli_sock;
    //创建套接字
    CHECK_RET(cli_sock.Socket());
    //绑定地址信息（不推荐）
    //向服务端发起请求
    CHECK_RET(cli_sock.Connect(ip, port));
    //循环收发数据
    int fd = cli_sock.GetFd();
    while(1) {
        cal_t tmp;//定义一个结构体变量，申请了一块空间
        tmp.num1 = 10;
        tmp.num2 = 20;
        tmp.op = '+'; // 这个成员变量赋值的过程就是数据对象在内存中组织排布的过程

        send(fd, (void*)&tmp, sizeof(cal_t), 0);//将这块空间中的数据发送给服务端
        sleep(100);
    }
    cli_sock.Close();
    return 0;
}
