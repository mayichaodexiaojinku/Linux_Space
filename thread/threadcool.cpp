/* 自己造轮子：实现一个简单的线程池（固定数量线程池）
 * 线程池 = 多个线程+任务队列
*/
#include<iostream>
#include<queue>
#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#define max_thread 10
#define max_queue 100
class Task
{
private:
       void *_data;
pubilc:
    
}
class ThreadPool
{
private:
     int _max_thread;
     int _cur_thread;
     int _stop_flags;
     int _cap;
     std::queue<Task *> _tlist;
     pthread_mutex_t _lock;
     pthread_cond_t _emtpy;
     pthread_cond_t _full;
     void ThreadLock()
     {
       pthread_mutex_lock(&_lock);
     }

     void ThreadUnLock()
     {
       pthread_mutex_unlock(&_lock);
     }
     bool QueueIsempty()
     {
        return _tlist.empty();
     }
     bool QueueIsFull()
     {
         return (
public:
       ThreadPool(int  max_thread,int max_queue)
}
int main()
{
   return 0;


}
