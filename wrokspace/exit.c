/* main函数中得return
 * exit（int status）库函数调用
 *    在程序任意位置调用都会使进程退出
 *    status是进程的退出状态
 * _exit(int status)系统调用接口
 *    在程序任意位置调用都会使进程退出
 *    exit最终调用的就是这个借口退出的
 *    exit与_exit的区别
 *       exit是温和性的退出，在退出前会温和的释放资源，刷新缓冲区
 *       _exit是暴力退出，直接释放资源，不会刷新缓冲区。
 */
#include<string.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
int main()
{
    printf("hello world \n");
    sleep(2);
    return 0;
}
