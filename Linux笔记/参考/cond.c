/*=============================================================== 
*   Copyright (C) . All rights reserved.")
*   文件名称： 
*   创 建 者：zhang
*   创建日期：
*   描    述：owl of delicious rice
*
*   owl这个demo以一个顾客吃饭/厨师做饭为例体会调价变量实现同步的流程与细节 
================================================================*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

int bowl = 0; // 初始为0，表示没有面
pthread_mutex_t mutex;
pthread_cond_t consumer_cond;
pthread_cond_t cook_cond;

void *thr_customer(void *arg)
{
    //这是一个顾客的流程
    while(1) {
        //0. 加锁操作
        pthread_mutex_lock(&mutex);
        while (bowl == 0) {//顾客加锁成功，发现没有饭，则要陷入休眠,如果没解锁就会导致厨师无法做饭
            //pthread_mutex_unlock();
            //----------------//厨师在这期间做好饭，唤醒就白唤醒了，因为顾客还没睡
            //pause();//休眠等待唤醒
            //pthread_mutex_lock();
            //如果没饭，则要等待,因为已经加过锁了，因此等待之前要解锁，被唤醒之后要加锁
            //因此pthread_cond_wait集合了三步操作：解锁/挂起/加锁
            //解锁和挂起是一个原子操作-不可被打断
            //顾客解锁，还没来得及挂起休眠；这时候厨师进来做饭,做好后唤醒顾客(实际顾客还没休眠)
            //会导致顾客这时候拿到时间片休眠彻底卡死(厨师不会进行第二次唤醒)
            pthread_cond_wait(&consumer_cond, &mutex);
        }
        //能走下来应该表示有饭了，bowl是等于1的
        printf("It's delicious.\n");
        bowl = 0; // 饭被吃完了
        //唤醒厨师，再做一碗
        pthread_cond_signal(&cook_cond);
        //解锁操作
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}
void *thr_cook(void *arg)
{
    //这是一个厨师的流程
    while(1) {
        //0. 加锁操作，因为咬对碗进行操作
        pthread_mutex_lock(&mutex);
        while (bowl == 1) {
            //表示有饭，则不能做，陷入等待
            pthread_cond_wait(&cook_cond, &mutex);
        }
        //能走下来表示没饭，则做饭  bowl=0
        printf("Made a bowl of delicious rice\n");
        bowl = 1;//做了一碗饭
        //唤醒顾客
        pthread_cond_signal(&consumer_cond);
        //解锁操作
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}
int main()
{
    pthread_t ctid[2]; 
    int ret, i;

    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&consumer_cond, NULL);
    pthread_cond_init(&cook_cond, NULL);

    for (i = 0; i < 4; i++) {
        ret = pthread_create(&ctid[0], NULL, thr_customer, NULL);
        if (ret != 0) {
            printf("create thread failed!!\n");
            return -1;
        }
    }
    for (i = 0; i < 4; i++) {
        ret = pthread_create(&ctid[1], NULL, thr_cook, NULL);
        if (ret != 0) {
            printf("create thread failed!!\n");
            return -1;
        }
    }

    pthread_join(ctid[0], NULL);
    pthread_join(ctid[1], NULL);

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&consumer_cond);
    pthread_cond_destroy(&cook_cond);
    return 0;
}
