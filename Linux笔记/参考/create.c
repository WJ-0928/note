#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

void test()
{
    pthread_exit(NULL);
    return ;
}
void *thread_start(void *arg)
{
    printf("The parameters passed are:%s", (char*)arg);
    //sleep(3);
    //pthread_exit(NULL);
    //return NULL;
    while(1) {
        printf("this is a normal thread:%p\n", pthread_self());
        sleep(1);
    }
    return NULL;
}
//程序运行起来之后，操作系统会创建一个主线程pcb调度运行main函数
//在这个线程中可以创建另一个线程，创建一个pcb运行线程入口函数
int main()
{
    pthread_t tid;
    char *buf = "今天的天气不太好~心情有点郁闷~~\n";
    int ret = pthread_create(&tid, NULL, thread_start, (void*)buf);
    if (ret != 0) {
        printf("Thread creation failed\n");
        return -1;
    }
    printf("normal thread id:%p\n", tid);
    //sleep(3);
    //pthread_cancel(tid);//取消普通线程
    pthread_exit(NULL);
    while(1) {
        printf("this is main thread:%p\n", pthread_self());
        sleep(1);
    }
    return 0;
}
