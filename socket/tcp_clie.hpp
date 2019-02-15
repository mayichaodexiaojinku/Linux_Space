#ifndef _TCP_CLIENT_HPP_
#define _TCP_CLIENT_HPP_
#include<iostream>
#include<string>
#include<stdlib.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<strings.h>
#include<string.h>
using namespace std;
class Client{
   private:
      int sock;
      string peer_ip;
      int peer_port;
    public:
      Client(const int &port_,const string &ip_)
       :peer_port(port_)
       ,peer_ip(ip_)
       {}
       void InitClient()
       {
         sock = socket(AF_INET,SOCK_STREAM,0);
	 if( sock < 0 ){
	  cerr << "socket error" << endl;
	  exit(2);
         }
       }
       void Connect()
       {
         struct sockaddr_in peer;
	 bzero(&peer,sizeof(peer));
	 peer.sin_family = AF_INET;
	 peer.sin_port =htons(peer_port);
	 peer.sin_addr.s_addr = inet_addr(peer_ip.c_str());
	 if(connect(sock,(struct sockaddr*)&peer,sizeof(peer)) == 0)
         	   cout << "connect success" << endl;
         else{
	    cerr << "connect error" << endl;
	    exit(3);
	 }
        }
	void Run()
	{
	   string message;
	   char buf[1024];
	   while(1){
	     cout << "Please Enter#" << endl;
	     cin >> message;
	     write(sock,message.c_str(),message.size());
	     read(sock,buf,sizeof(buf)-1);
	     cout << "Server echo# " << buf <<endl;
            }
	}
	~Client()
	{
  	   close(sock);
	}
};
#endif	
