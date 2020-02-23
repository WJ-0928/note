/*=============================================================== 
*   Copyright (C) . All rights reserved.")
*   文件名称： 
*   创 建 者：zhang
*   创建日期：
*   描    述：
*       这个demo用于演示线程等待/线程分离的接口使用 
================================================================*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

void *thr_start(void *arg)
{
    pthread_detach(pthread_self());//分离自己
    printf("Normal thread will exit in 3 seconds\n");
    sleep(3);
    char *buf = "leihoua~~\n";  //返回的是常量的地址
    //char buf[] = "leihoua~~\n"; //返回的是局部空间的地址

    return buf;
}
int main()
{
    pthread_t tid;
    int ret = pthread_create(&tid, NULL, thr_start, NULL);
    if (ret != 0) {
        printf("thread create failed!!\n");
        return -1;
    }
    printf("Main thread waiting for normal thread to exit\n");
    char *retval = NULL;
    //pthread_join(tid, (void**)&retval);//等待一个线程的退出，若线程没有退出，则会一直等待
    //pthread_detach(tid);
    while(1) {
        printf("retval:%s\n", retval);
        sleep(1);
    }
    return 0;
}

