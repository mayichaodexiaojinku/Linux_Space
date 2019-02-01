/*   这是一个程序替换的demo
 *     演示几种程序替换接口如何使用以及不同之处
 */
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
int main()
{
    pid_t pid = fork();
    if(pid < 0)
    {
       perror("fork error");
       exit(-1);
    }else if(pid == 0){
      // execl("/bin/ls","ls","-l","-a",NULL);
      // execlp("/bin/ls","ls","-a",NULL);
      // 添加参数的时候记住要有一个NULL表示参数的结尾
      //  NULL之后还有一个参数是用于设置环境变量
      //     并且这个函数会清空所有的环境变量，因为这个接口就是让我们用户自己来设置环境变量的
       char *ptr = "PATH = hello world";
       char *env[3]={NULL};
       env[0] = ptr;
       execle("/home/chaochao/workspace/test","test",NULL,env);
       printf("```````````````````````");
       perror("execle error");
      }
       printf("leihou!!!\n");
       return 0;
}
