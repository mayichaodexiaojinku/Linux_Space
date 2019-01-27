#include<stdio.h>
#include<signal.h>
#include<unistd.h>
int main()
{
   // kill(getpid(),SIGINT);
   // int raise(int sig);
   // 向自身发送信号
   // raise(SIGTERM);
   // void abort(void);
   //  向自身发送信号
   // alarm(2);
   //  在n秒之后向进程发送SIGALRM信号
   // 设置一个定时器，取消上一个定时器，并且返回上一个定时剩余时间
   while(1){
     sleep(1); 
   }
   
   return 0;
}
