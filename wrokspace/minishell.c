/* 这个代码是我们自己来实现一个建议的迷你shell，能够执行一些其他的命令;
 * 初步看起来的效果跟我们的shell有一定的相似性
 *  1. 写一个shell入口用于提示要输入信息
 *  2. sancf接收一个输入信息
 *  3. 创建子进程
 *  4. 程序替换
 */ 
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
int main()
{
	while(1){
		printf("minishell:");	
		fflush(stdout);
		char cmd[1024] = { 0 };
		//^\n:scanf本身是遇到空格就要获取一次，这样的话就无法获取到一个完整的命令
		//  因此‘%[^\n]’表示的是获取数据直到遇到\n为止
		//  %*c：将缓冲区中得字符都取出来，但是不要它，直接丢掉
		//   目的是为了将最后的\n从缓冲区取出来，防止陷入死循环
		if(scanf("%[^\n]%*c",cmd) != 1){
			getchar();
		}
		//将获取到的命令解析一下，然后创建子进程进行程序替换
		char *ptr = cmd;
		char *argv[32] = {NULL};
		int argc = 0;
		argv[argc++] = ptr;
		while(*ptr != '\0'){
			if(isspace(*ptr)){
				while(isspace(*ptr) &&*ptr != '\0'){
					*ptr++ = '\0';
				}
				argv[argc++] = ptr;
			}
			ptr++;
		}
		if(fork() == 0){
			execvp(argv[0],argv);
		}
		wait(NULL);
	}
	//需要等待的原因：
	//   1.避免产生僵尸子进程
	//   2.等待子进程完毕，让程序逻辑更加完善
	return 0;
}
