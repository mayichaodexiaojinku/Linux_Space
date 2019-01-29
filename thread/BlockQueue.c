/*这是一个生产者消费者模型的demo
 * 实现一个线程安全访问的队列
 */
#include<queue>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>
#define NUM 10
class BlockQueue
{
public:
   BlockQueue(int cap =NUM)
       :_cap(cap)
       {
          pthread_mutex_init(&mutex,NULL);
          pthread_cond_init(&empty,NULL);
          pthread_cond_init(&full,NULL);
       }
   ~BlockQueue()
   {

          pthread_mutex_destroy(&mutex);
          pthread_cond_destroy(&full,NULL);
          pthread_cond_destroy(&empty,NULL);
   }
   bool PushData(int data)
   {
       QueueLock();
       while(QueueIsFull()){
          printf("e\n");
          ProductWait();
       }
       _q.push(data);
       ConsumerNotice();
       QueueUnLock();
       return true;
   }
   bool PopData(int& data)
   {
       QueueLock();
       while(QueueIsEmpty()){
          printf("f\n");
          ProductWait();
       }
        data= _q.front();
	_q.pop();
	ProdectNotice();
	QueueUnLock();
       return true;
   }
private:
   int _cap;
   std::queue<int> _q;
   pthread_mutex_t mutex;
   pthread_cond_t full;
   pthread_cond_t empty;
   void QueueLock()
   {
    pthread_mutex_lock(&mutex); 
   }
   void QueueUnLock()
   {
    pthread_mutex_unlock(&mutex);
   }
   void ProductWait()
   {
     pthread_cond_wait(&full,&mutex);
   }
   void ConsumerWait()
   {  
     pthread_cond_wait(&empty,&mutex);
   }
   void ProductNotice()
   {
     pthread_cond_signal(&full);
   }
   void ConsumerNotice()
   {  
     pthread_cond_signal(&empty);
   }
   bool QueueIsFull()
   {
     return !(_q.size() == 0);
   }
   bool QueueIsEmpty()
   {
     return (_q.size() == 0);
   }
}
int main()
{
  pthread_t  tid1,tid2;
  int ret;
  BlockQueue q;
  ret = pthread_create(&tid1,NULL,productor,(void *)&q);
  if(ret != 0){
   printf("error\n");
   return -1;
   }
  ret = pthread_create(&tid1,NULL,productor,(void *)&q);
  if(ret != 0){
   printf("error\n");
   return -1;
   }
}
