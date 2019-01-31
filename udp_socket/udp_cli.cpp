#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>
#include <iostream>
class UdpSocket
{
   private:
        int _sockfd;
   public:
         bool Socket()
	 {
	    _sockfd = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
	    if(_sockfd < 0 )
	    {
	      perror("socket error");
	      return false;
	    }
	    return true;
         }
	 bool Bind(std::string &ip,uint16_t port)
	 {
	   sockaddr_in addr;
	   addr.sin_family = AF_INET;
	   addr.sin_port = htons(port);
	   addr.sin_addr.s_addr = inet_addr(ip.c_str());
	   socklen_t len = sizeof(sockaddr_in);
	   int ret = bind(_sockfd,(sockaddr*)&addr,len);
           if(ret  < 0)
	   {
	      perror("bind error");
	      return  false;
	   }
	    return true;
          }
	  ssize_t Recv(std::string *buf,sockaddr_in *addr = NULL)
	  {
	     ssize_t  rlen;
	     socklen_t len =sizeof(sockaddr_in);
	     char tmp[1024] = { 0 };
	     rlen = recvfrom(_sockfd,tmp,1024,0,(sockaddr*)addr,&len);
	     if(rlen < 0 )
	         return -1;
	      buf->assign(tmp,rlen);
	      return rlen;
	  }
          ssize_t Send(std::string &buf, struct sockaddr_in *addr)
	  {
	      ssize_t slen;
	      socklen_t len = sizeof(sockaddr_in);
	      slen = sendto(_sockfd, buf.c_str(), buf.length(), 0,
		      (sockaddr*)addr, len);
	      return slen;
	  }
	  //关闭套接字
	   bool Close()
	  {
	       close(_sockfd);
          }
                         
};
#define CHECK_RET(e) if((e) == false) { return false; }
int main()
{
   UdpSocket sock;
   CHECK_RET(sock.Socket());
   sockaddr_in addr;
   addr.sin_family = AF_INET;
   addr.sin_port = htons(9000);
   addr.sin_addr.s_addr =inet_addr("192.168.204.128");
   while(1){
      std::string buff;
      printf("client say:");
      fflush(stdout);
      std::cin >> buff;
      sock.Send(buff,&addr);
      buff.clear();
      sock.Recv(&buff);
      printf("server say:%s\n",buff.c_str());
      }
      sock.Close();
   return 0;
}
