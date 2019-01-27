#include<stdio.h>
#include<unistd.h>
#include<signal.h>
int main()
{
  //我要向阻塞这个集合中的信号
   sigset_t new_block;
  //用于保存原来阻塞集合中的信号，防止后续要将阻塞集合还原回去
  sigset_t old_block;
  //int sigemptyset(sigset_t *set);
  //清空一个信号的集合
  sigemptyset(&new_block);
  // int sigfillset(sigset_t *set);
  //将所有信号都添加到set集合中
  //int sigaddset(sigset_t *set, int signum);
  //添加指定的单个信号到set集合中
  //int sigdelset(sigset_t *set, int signum);
  //从集合中移除一个指定的信号
  //int sigismember(const sigset_t *set, int signum);
  // 判断一个信号是否在一个集合中
  sigfillset(&new_block);
  //int sigprocmask(int how, const sigset_t *set, sigset_t *oldset);
  // 阻塞信号/解除信号
  // how：
  //    SIG_BLOCK 阻塞集合中的信号
  //    SIG_UNBLOCK 对集合中的信号解除阻塞
  //    SIG_SETMASK 将集合中的信号设置到阻塞集合中
  //set：要阻塞/解除阻塞的集合
  //oldset：保存原先阻塞集合中的信号
  sigprocmask(SIG_BLOCK,&new_block,&old_block);
  //不安回车就不往下走
  getchar();
  //解除阻塞
  sigprocmask(SIG_UNBLOCK,&new_block,NULL);
  sigprocmask(SIG_SETMASK,&old_block,NULL);



  return 0;
  }
