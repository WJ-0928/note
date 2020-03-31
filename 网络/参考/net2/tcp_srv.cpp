/*=============================================================== 
*   Copyright (C) . All rights reserved.")
*   文件名称： 
*   创 建 者：zhang
*   创建日期：
*   描    述：使用封装的TcpSocket类实例化对象实现tcp服务端程序 
================================================================*/

#include <iostream>
#include <stdlib.h>
#include "tcpsocket.hpp"


int main(int argc, char *argv[])
{
    if (argc != 3) {
        printf("em:./tcp_srv 192.168.122.132 9000\n");
        return -1;
    }
    std::string ip = argv[1];
    uint16_t port = atoi(argv[2]);

    TcpSocket lst_sock;
    CHECK_RET(lst_sock.Socket());//创建套接字
    //#define CHECK_RET(q) if((q)==false){return -1;}
    //if (lst_sock.Socket() == false) {return -1;}
    CHECK_RET(lst_sock.Bind(ip, port));//绑定地址信息
    CHECK_RET(lst_sock.Listen());//开始监听
    while(1) {
        TcpSocket cli_sock;
        bool ret = lst_sock.Accept(&cli_sock);
        if (ret == false) {
            continue;
        }
        int fd = cli_sock.GetFd();
        cal_t tmp;//定义变量申请了一块空间
        recv(fd, (void*)&tmp, sizeof(cal_t), 0);

        int sum = tmp.num1 + tmp.num2;
        printf("%d %c %d = %d\n", tmp.num1, tmp.op, tmp.num2, sum);
    }
    lst_sock.Close();
    return 0;
}
