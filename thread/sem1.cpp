/*使用c++中的vector实现一个环形队列
 * 使用信号量对这个环形队列资源进行计数
 * 两个信号量：
 *    一个空闲空间资源的计数      等于vector节点数
 *    一个写入数据的空间资源计数  初始值：0
 *
 */
#include<stdio.h>
#include<unistd.h>
#include<semaphore.h>
#include<pthread.h>
#include<iostream>
#define MAX_QUEUE  10
class RingQueue
{
    private:
       std::vector<int>  _q;
       int _cap;
       int _consumer_step;
       int _prodector_step;
       sem_t _idle;
       sem_t _data;
    public:
       RingQueue(int cap = MAX_QUEUE)
       :_cap(cap)
       ,_q(cap)
       {
           _consumer_step = 0;
           _prodector_step = 0;
          sem_init(&_idle,0,cap);
	  sem_init(&_data,0,0);
       }
       ~RingQueue()
       {
         sem_destroy(&_idle);
	 sem_destroy(&_data);
       bool GetData(int & data)
       {
           sem_wait(&_data);
	   data = _q[_consumer_step++];
	   _consumer_step %= _cap;
	   sem_post(&_idle);
           return true;
       }
       bool PutData(int &data)
       {
           sem_wait(&_idle);
	    _q[_prodector_step++] = data;
	   _prodector_step %= _cap;
	   sem_post(&_data);
        return true;
       }
}
int main()
{
  RingQueue q;
  pthread_t tid1,tid2;
  pthread_create(&tid1,0,NULL);
  pthread_create(&tid2,0,NULL);

  return 0;
}
