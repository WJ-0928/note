/*=============================================================== 
*   Copyright (C) . All rights reserved.")
*   文件名称： 
*   创 建 者：zhang
*   创建日期：
*   描    述：这个demo中封装一个BlockQueue类，实现生产者与消费者模型 
================================================================*/

#include <cstdio>
#include <iostream>
#include <queue>
#include <pthread.h>

#define MAX_QUEUE 5
class BlockQueue
{
    public:
        BlockQueue(int max = MAX_QUEUE):_capacity(max){
            pthread_mutex_init(&_mutex, NULL);
            pthread_cond_init(&_cond_con, NULL);
            pthread_cond_init(&_cond_pro, NULL);
        }
        ~BlockQueue(){
            pthread_mutex_destroy(&_mutex);
            pthread_cond_destroy(&_cond_con);
            pthread_cond_destroy(&_cond_pro);
        }
        bool Push(int data) {
            //入队的操作，肯定是生产者
            //1. 加锁操作
            pthread_mutex_lock(&_mutex);
            //2. 判断队列是否满了
            while (_queue.size() == _capacity) {
                //若不满足（队列已经满了），则线程陷入阻塞
                pthread_cond_wait(&_cond_pro, &_mutex);
            }
            //3. 向队列中添加一个节点
            _queue.push(data);
            //4. 唤醒消费者
            pthread_cond_signal(&_cond_con);
            //5. 解锁操作
            pthread_mutex_unlock(&_mutex);

            return true;
        }
        // const & 表示输入参数
        // * 表示输出参数
        // & 表示输入输出参数
        bool Pop(int *data) {
            //出队的操作，肯定是消费者
            //1. 加锁操作
            pthread_mutex_lock(&_mutex);
            //2. 判断队列是否为空
            while (_queue.empty()) {
                //若不满足（队列为空），则线程陷入阻塞
                pthread_cond_wait(&_cond_con, &_mutex);
            }
            //3. 从队列中获取一个节点
            *data = _queue.front();//获取队首节点
            _queue.pop();//节点出队
            //4. 唤醒生产者
            pthread_cond_signal(&_cond_pro);
            //5. 解锁操作
            pthread_mutex_unlock(&_mutex);
        }
    private:
        std::queue<int> _queue;
        int _capacity;//定义队列最大节点数量
        pthread_mutex_t _mutex;//实现互斥，保护_queue;
        pthread_cond_t _cond_con;//实现同步，消费者等待队列
        pthread_cond_t _cond_pro;//实现同步，生产者等待队列
};

#define MAX_THREAD 5
void *thr_consumer(void *arg)
{
    BlockQueue *q = (BlockQueue*)arg;
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
    BlockQueue *q = (BlockQueue*)arg;
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
    BlockQueue q;

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
