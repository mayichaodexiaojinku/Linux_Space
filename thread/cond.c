/*这是一个条件变量的使用demo
 *
 */
#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
int g_judue = 0;
void *sald_noodle(void *arg)
{
   while(1){
       printf("create\n");
       }
       return NULL;
       //如果不满足条件需要挂起等待，但是这个线程却获取到锁了
       //要是休眠了，大家就都卡死在获取锁这里了，因此需要在挂起等待之前先解锁
       //但是如果先解锁了，在还没有休眠之前别人就修改完毕条件唤醒你，
       //但是这个线程却是在唤醒之后才开始睡眠，那么久可能会卡死在睡眠这里
       //因此解锁和休眠必须是原子性的操作；
       //cond: 条件变量
       //mutex：互斥量
       //这个函数在挂起之前对互斥锁进行解锁操作
       //这时候解锁操作和挂起操作必须是一个原子操作
       //否则不安全
void *buy_noodle(void *arg)
{
    while(1){
       if(g_judge == 0){
       //

