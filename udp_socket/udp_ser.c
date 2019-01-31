/*这是一个服务端的程序udp
*
 */
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int main()
{
   //创建套接字
   //int socket(int domain, int type, int protocol);
   // domain :地址域  AF_INET   IPV4
   // type：套接字类型
   //    SOCK_STREAM  流式套接字 tcp
   //    SOCK_DGRAM   数据报套接字 udp
   //protocol:   协议类型
   //    IPPROTO_TCP 6 tcp协议
   //    IPPROTO_UDP 17 UDP协议
   //返回值：非负整数（套接字描述符）   失败：-1
   int sockfd = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
   if(sockfd < 0){
       perror("s");
       return -1;
       }
    //为套接字绑定地址
    //int bind(int sockfd, const struct sockaddr *addr,
    //                socklen_t addrlen);
    // sockfd：套接字描述符
    // addr：地址信息
    // addrlen ：地址信息长度
    // 返回值：成功 0   失败 -1
    // int16_t htons(uint16_t hostshort);
    // 将一个短整型（16位）数据从主机字节序转换为网络字节序
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(9000);
    // in_addr_t inet_addr(const char *cp);
    // 将点分十进制的字符串转换为网络字节序的地址
    // INADDR_ANY 0.0.0.0 只能用于服务端
    // INADDR_BROADCAST 255.255.255.255
    addr.sin_addr.s_addr = inet_addr("192.168.204.128");
    socklen_t len = sizeof(struct sockaddr_in);
    int ret =bind(sockfd,(struct sockaddr*)&addr,len);
    if(ret <0){
      perror("bind");
      return -1;
      }
    while(1)
    {
        //接收
	//ssize_t recvfrom(int sockfd, void *buf, size_t len, int flags,
	//              struct sockaddr *src_addr, socklen_t *addrlen);
	//sockfd:   套接字描述符
	//buf :     要发送的数据
	//len：     要发送的数据长度
 	//flags：   发送标志，0-默认阻塞
	//          MSG_PEEK    接收数据后数据并不会从缓冲区删除
	//          场景：探测性获取数据
	//src_addr : 发送端的地址信息
	//addrlen :  地址信息长度
	//返回值：实际读取到的数据字节长度
	char buff[1024] = { 0 };
	struct sockaddr_in cli_addr;
        recvfrom(sockfd,buff,1023,0,(struct sockaddr *)&cli_addr,&len);
	printf("client say:%s\n",buff);
	//发送
	memset(buff,0x00,1024);
	printf("serever say:");
        fflush(stdout);
	scanf("%s",buff);
	//ssize_t sendto(int sockfd, const void *buf, size_t len, int flags,
	//              const struct sockaddr *dest_addr, socklen_t addrlen);
	//socket: 套接字描述符
	//buf：   要发送的数据
	//len：    要发送的数据长度
	//flag :   默认 0 ，阻塞发送
	//dest_addr ：数据要发送到的对端地址信息
	//addrlen：  地址信息长度
	//返回值： 实际发送的数据长度   失败 -1
	sendto(sockfd,buff,strlen(buff),0,(struct sockaddr *)&cli_addr,len);
        
    }
    //关闭套接字
    close(sockfd);
   return 0;
}
