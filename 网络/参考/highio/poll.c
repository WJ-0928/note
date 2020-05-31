#include <poll.h> 
#include <unistd.h> 
#include <stdio.h>
 
int main() 
{  
    //1. 定义数组
    struct pollfd poll_fd;
    //2. 填充监控的描述符信息
    poll_fd.fd = 0;
    poll_fd.events = POLLIN;
    for (;;) {
        //开始监控，将就绪的事件填充到对应描述符的事件结构体的revents成员中
       int ret = poll(&poll_fd, 1, 3000);
       if (ret < 0) {
          perror("poll");
          continue;
       }
       if (ret == 0) {
           printf("poll timeout\n");
           continue;
       }
       //遍历数组，根据revents判断就绪了什么事件，进行相应操作
       if (poll_fd.revents == POLLIN) {
           char buf[1024] = {0};
           read(0, buf, sizeof(buf) - 1);
           printf("stdin:%s", buf);
       }
    }
    return 0;
}

