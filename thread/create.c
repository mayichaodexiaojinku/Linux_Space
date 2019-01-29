/* 这是一个线程创建的demo
 */
#include<pthread.h>
#include<stdio.h>
#include<unistd.h>
void *thr_start(void* arg)
{
  while(1){
    printf("c\n");
    sleep(1);
    }
}
int main()
{
    //演示多线程并行
    //int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
    //                          void *(*start_routine) (void *), void *arg);
    //thread :用于获取线程id（用户态的线程id）
    //attr：  设置线程属性
    //start_routine:线程入口函数，线程所运行的代码
    //arg：线程入口函数的参数
    //返回值: 成功0     失败：非0
    pthread_t tid;
    int ret = pthread_create(&tid,NULL,thr_start,(void*)&tid);
    if(ret != 0){
       printf("pthread create error\n");
       return -1;
       }
    while(1){
      //pthread_self(void)
      printf("主------%lu\n",pthread_self());
      sleep(1);
     }
}
