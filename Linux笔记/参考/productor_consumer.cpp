/*=============================================================== 
*   Copyright (C) . All rights reserved.")
*   文件名称： 
*   创 建 者：zhang
*   创建日期：
*   描    述：这个demo中封装一个RingQueue类，实现生产者与消费者模型 
================================================================*/

#include <cstdio>
#include <iostream>
#include <queue>
#include <pthread.h>
#include <semaphore.h>

#define MAX_QUEUE 5
#define MAX_THREAD 5
class RingQueue{
    private:
        std::vector<int> _queue;
        int _capacity;
        int _step_read; // 当前即将读取数据的位置的下标
        int _step_write; // 当前即将写入数据的位置的下标
        sem_t _sem_lock;//  用于实现互斥的信号量
        // 使用这个计数器，实现对当前队列中的数据资源的数量进行计数；
        // 如果<=0表示没有资源，则消费者会陷入等待
        sem_t _sem_data; 
        // 使用这个计数器，实现对当前队列 中的空闲空间数量进行计数；
        // 如果<=0表示队列满了，则生产者陷入等地啊
        sem_t _sem_space; 
    public:
        RingQueue(int max = MAX_QUEUE) : _queue(max), _capacity(max),
        _step_read(0), _step_write(0){
            //...初始化过程...
            //互斥信号量的初始化
            //pshare设置为0，表示当前用于线程间的同步互斥
            //value信号量初值，初始化为1，数值最大不大于1，实现互斥
            sem_init(&_sem_lock, 0, 1);
            sem_init(&_sem_data, 0, 0);//数据资源初始为0
            sem_init(&_sem_space, 0, max);//空闲空间初值就是节点数量
        }
        ~RingQueue() {
            //...销毁资源过程...
            sem_destroy(&_sem_lock);
            sem_destroy(&_sem_data);
            sem_destroy(&_sem_space);
        }
        bool Push(int data) {
            sem_wait(&_sem_space);//统计空间节点数量，自动判断是否有空闲空间，没有则阻塞
            //互斥保护临界资源，注意上边的信号量不需要保护
            //若保护了上边的信号量操作，反而回出问题：若先加锁再判断，有可能会陷入休眠而没解锁
            sem_wait(&_sem_lock);
            _queue[_step_write] = data;
            _step_write = (_step_write + 1) % _capacity;
            sem_post(&_sem_lock);
            sem_post(&_sem_data);//入队数据之后，数据资源的数量增加一个,并且唤醒消费者

            return true;

        }
        bool Pop(int *data) {
            sem_wait(&_sem_data);//消费者判读数据资源数量，若<=0则回陷入等待 ,计数-1
            sem_wait(&_sem_lock);
            *data = _queue[_step_read];
            _step_read = (_step_read + 1) % _capacity;
            sem_post(&_sem_lock);
            sem_post(&_sem_space);//空间资源多了一个，唤醒生产者

            return true;
        }
};

void *thr_consumer(void *arg)
{
    RingQueue *q = (RingQueue*)arg;
    while(1) {
        //消费者处理数据
        int data;
        q->Pop(&data);
        printf("消费者:%p 出队数据:%d\n", pthread_self(), data);
    }
    return NULL;
}
void *thr_productor(void *arg)
{
    RingQueue *q = (RingQueue*)arg;
    int i = 0;
    while(1) {
        //生产者生产数据
        q->Push(i);
        printf("生产者：%p 入队数据：%d\n", pthread_self(), i++);
    }
    return NULL;
}
int main()
{
    //完成生产者与消费者模型
    //创建生产者角色的线程以及消费者角色的线程
    pthread_t ctid[MAX_THREAD], ptid[MAX_THREAD];
    int ret , i;
    RingQueue q;

    //创建消费者线程
    for (i = 0; i < MAX_THREAD; i++) {
        ret = pthread_create(&ctid[i], NULL, thr_consumer, (void*)&q);
        if (ret != 0) {
            printf("thread create error\n");
            return -1;
        }
    }
    //创建生产者线程
    for (i = 0; i < MAX_THREAD; i++) {
        ret = pthread_create(&ptid[i], NULL, thr_productor, (void*)&q);
        if (ret != 0) {
            printf("thread create error\n");
            return -1;
        }
    }
    //等待所有线程退出
    for (i = 0; i < MAX_THREAD; i++) {
        pthread_join(ctid[i], NULL);
        pthread_join(ptid[i], NULL);
    }
    return 0;
}
