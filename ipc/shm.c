/* 这是一块共享内存的demo，共享数据
 */
#include<stdio.h>
#include<sys/shm.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
#define IPC_KEY 0x01234567
int main()
{
    int shmid = -1;
//int shmget(key_t key, size_t size, int shmflg);
//key:共享内存在系统中的标识
//    ftok这个接口可以通过一个文件计算出一个key值
//size：共享内存大小
//shmflg：IPC_CREAT 创建|权限
//返回值：共享内存的操作句柄
    shmid =  shmget(IPC_KEY,32,O_CREAT|0);
    if(shmid < 0 ){
	printf("shemget error\n");
	  return -1;
         }
//创建的共享内存无法直接操作，因为我们只能操作虚拟地址空间中的地址
//因此第二步就是将共享内存映射到虚拟地址空间，让我们能够通过虚拟地址空间来访问
// void *shmat(int shmid, const void *shmaddr, int shmflg);
//  shmid :共享内存句柄
//  shmaddr：映射首地址（通常置空）
//  shmflg：
//      SHM_RDONLY 只读 否则可读可写
//      返回：映射到虚拟地址空间的首地址 失败：（void*）-1
    void *shm_start = shmat(shmid,NULL,0);
    if(shm_start ==(void*)-1){
      perror("shmat error");
      return -1;
      }
    int i = 0 ;
    while(1){
       sprintf(shm_start,"asas",i++);
       sleep(1);
    }
    //接触共享内存在虚拟地址空间中的映射关系
    //int shmdt(const void *shmaddr);
    //shmaddr： 映射的首地址
    //返回值 成功 0 失败 -1
    shmdt(shm_start);
    // int shmctl(int shmid, int cmd, struct shmid_ds *buf);
    //  cmd:
    //      IPC_PMID 删除共享内存
    //  buf：存放获取共享内存的信息
    shmctl(shmid,IPC_RMID,NULL);
    return 0;









}
