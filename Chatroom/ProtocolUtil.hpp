#pragma once
#include<sstream>
#include"log.hpp"
#include<iostream>
#include<sys/socket.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#define BACKLOG 5
using namespace std;
class Request{
private:
   string method;
   string content_length;
   string blank;
   string text;
public:
   Request():blank('\n')
   {}
   ~Request()
   {}
};
class Util{
     static bool ResgisterEnter(string &nick_name,string &school,\
                                 string &passwd)
     {
         stirng again;
         cout <<"Please Enter name:";
         cin >> nick_name;
         cout <<"Please Enter school:";
         cin >> school;
         cout <<"Please Enter passwd:";
         cin >> passwd;
         cout <<"Please Enter again:";
         cin >> again;
         if(again == passwd){
             return true;
         }
         return false;
     }
     static bool LoginEnter(string &id,string &passwd)
     { 
         cout << "Please Enter Your ID :";
         cin >> id;
         cout << "Please Enter Your Passad:";
         cin >> passed;
         return true;  
     }
     static string IntToString(int a)
     {
       stringstream ss;
       ss << a;
       return ss.str();
     }
     static int StringToInt(string &s)
     {
         stringstream ss(s);
         int x = 0;
         ss >> x; 
         return x;
     }
     static void RecvOneline(int sock,string &OutString)
     {
        char c = 'x';
        while(c != '\n'){
          ssize_t s = recv(sock,&c,1,0)
          if(s > 0){
             if(c == '\n')
                  break;
             OutString.push_back();    
          }
          else 
             break;
        }
 
     }
     static void RecvRequest(int sock,Request &rq)
     {
          RecvOneline(sock,rq.method);
          RecvOneline(sock,rq.content_length);
          RecvOneline(sock,rq.blank);
          string &cl = rq.content_length;
          size_t pos = cl.find(": ");
          if(string::npos == pos){
          return;
          }
          string sub = cl.substr(s+2);
          int size = StringToint(sub);
          char c;
          for(auto i; i < size ; i++){
                  recv(sock,&c,1,0);
                  (rq.text).push_back(c);
          }
     }
	 static void SendRequest(int tcp_sock,const Request& rq)
	 {
		 string &m_ = rq.method;
		 string &cl_ = rq.content_length;
		 string &b_ = rq.blank;
		 string &text_ = rq.text;
		 send(tcp_sock,m_.c_str(),m_.size(),0);
		 send(tcp_sock,cl_.c_str(),cl_.size(),0);
		 send(tcp_sock,b_.c_str(),b_.size(),0);
		 send(tcp_sock,text_.c_str(),text_.size(),0);
	 }
};
class SocketApi{
public:
    static int Socket(int type)
    {
        int sock = socket(AF_INET,type,0);
        if(sock < 0){
            LOG("socket error",ERROR);
            exit(2);
        }
    }
    static void Bind(int sock,int port)
    {
        struct sockaddr_in local;
        local.sin_family = AF_INET;
        local.sin_addr.s_addr =htonl(INADDR_ANY);
        local.sin_port =htons(port);
        if(bind(sock,(struct sockaddr*)&local,sizeof(local)) < 0){
             LOG("bind error",ERROR);
             exit(3);
        }
    }
    static void Listen(int listen_sock)
    {
        
        if(listen(listen_sock,BACKLOG) < 0){
             LOG("listen error",ERROR);
             exit(4);
        }
    }
    static int Accept(int listen_sock,string &out_ip,int &out_port)
    {
        struct sockaddr_in peer;
        socklen_t len = sizeof(peer);
        int sock = accept(listen_sock,(struct sockaddr*)&peer,&(len));
        if(sock < 0){     
             LOG("accept error",WARNING);
             return -1;       
        }       
        out_ip = inet_ntoa(peer.sin_addr);
        out_port =htons(peer.sin_port); 
    }   
    static bool Connect(const int&sock,string peer_ip,const int &port) 
    {
        struct sockaddr_in peer;
        peer.sin_family = AF_INET;
        peer.sin_addr.s_addr = inet_addr(peer_ip.c_str());
        peer.sin_port = htons(port);
        if(connect(sock,(struct sockaddr*)&peer,sizeof(peer)) < 0){
          LOG("connect error",WARNING);
          return -1;
        }
        return 1;
    } 
};
