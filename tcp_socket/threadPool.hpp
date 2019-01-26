#ifndef THREADPOOL_HPP_
#define _THREADPOOL_HPP_
#include<iostream>
#include<queue>
#include<pthread.h>
using namespace std;
typedef void (*handler_t)(int);
class Task
{
private:
      int sock;
      handler_t handler;
public:
     Task(int sock_,handler_t h_)
       :sock(sock_)
       ,handler(h_)
       {}
     void  Run()
     {
       handler(sock);
     }
};
class ThreadPool
{
private:
     int nums;
     int Idle_nums;
     queue<Task> Task_queue;
     pthread_mutex_t lock;
     pthread_cond_t cond;
public:
     ThreadPool(int nums_):nums(nums_),Idle_nums(0)
     { 
       pthread_mutex_init(&lock,NULL);
       pthread_cond_init(&cond,NULL);
     }
     void LockQueue()
     {
          pthread_mutex_lock(&lock);
     }
     void UnLockQueue()
     {
         pthread_mutex_unlock(&lock);
     }
     bool IsQueueEmpty()
     {
         return Task_queue.size() > 0 ? false:true;
     }
     Task PopTask()
     {
          LockQueue();
          Task t = Task_queue.front();
	  Task_queue.pop();
          UnLockQueue();
	  return t;
     }
     void WakeOneThread()
     {
        pthread_cond_signal(&cond);
     }
     void PushTask(const Task &t)
     {
         LockQueue();
	 Task_queue.push(t);
	 WakeOneThread();
	 UnLockQueue();
     }
     void QueueIdle()
     {
        Idle_nums++;
        pthread_cond_wait(&cond,&lock);
        Idle_nums--;
     }
     static void *ThreadRoutine(void * arg)
     {
          pthread_detach(pthread_self());
          ThreadPool *tp = (ThreadPool *)arg;
	  while(1){
	      tp->LockQueue();
	      while(tp->IsQueueEmpty()){
	         tp->QueueIdle();
		 }
	      Task t = tp->PopTask();
	      tp->UnLockQueue();
	      t.Run();
	}      
     }
     void InitThreadPool()
     {
        pthread_t tid;
	for(auto i = 0;i < nums;i++)
	     pthread_create(&tid,NULL,ThreadRoutine,(void *)this);
     }
     ~ThreadPool()
     {
      pthread_mutex_destroy(&lock);
      pthread_cond_destroy(&cond);
     }
};
#endif
