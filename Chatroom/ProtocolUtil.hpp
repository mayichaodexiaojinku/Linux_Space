#pragma once
#include<sstream>
#include"log.hpp"
#include<iostream>
#include<sys/socket.h>
#include<sys/types.h>
#include<json/json.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#define BACKLOG 5
#define MESSAGE_SIZE 1024
using namespace std;
class Request{
public:
   string method;
   string content_length;
   string blank;
   string text;
public:
   Request():blank("\n")
   {}
   ~Request()
   {}
};
class Util{
public:
     static void AddUser(vector<string> &online_user,string &onlineString)
     {
          for(auto it=online_user.begin();it<online_user.end() ; it++){
                 if(*it == onlineString)
                      return;
          }
          online_user.push_back(onlineString);
     }
     static void DeleteUser(vector<string> &online_user,\
                            string &onlineString){
          for(auto it=online_user.begin();it<online_user.end() ; it++){
                 if(*it == onlineString)
                      online_user.erase(it);
          }
     }
     static bool RegisterEnter(string &nick_name,string &school,\
                                 string &passwd)
     {
         string again;
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
     static bool LoginEnter(unsigned int  &id,string &passwd)
     { 
         cout << "Please Enter Your ID :";
         cin >> id;
         cout << "Please Enter Your Passad:";
         cin >> passwd;
         return true;  
     }
     
     static void Serializer(Json::Value &root,string &sendString)
     {
         Json::FastWriter w;
         sendString = w.write(root);
     }
     static void UnSerializer(string &sendString,Json::Value &root)
     {
         Json::Reader r;
         r.parse(sendString,root,false);
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
          ssize_t s = recv(sock,&c,1,0);
          if(s > 0){
             if(c == '\n')
                  break;
             OutString.push_back(c);    
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
          string sub = cl.substr(pos+2);
          int size = StringToInt(sub);
          char c;
          for(auto i = 0; i < size ; i++){
                  recv(sock,&c,1,0);
                  (rq.text).push_back(c);
          }
     }
	 static void SendRequest(int tcp_sock,const Request& rq)
	 {
		 string m_ = rq.method;
		 string cl_ = rq.content_length;
		 string b_ = rq.blank;
		 string text_ = rq.text;
		 send(tcp_sock,m_.c_str(),m_.size(),0);
		 send(tcp_sock,cl_.c_str(),cl_.size(),0);
		 send(tcp_sock,b_.c_str(),b_.size(),0);
		 send(tcp_sock,text_.c_str(),text_.size(),0);
	 }
     static void RecvMessage(int sock,string &recvString,\
       struct sockaddr_in &peer)
     {
         char msg[MESSAGE_SIZE];
         socklen_t len = sizeof(peer); 
         ssize_t s = recvfrom(sock,msg,sizeof(msg)-1,0,\
                   (struct sockaddr*)&peer,&len);
         if( s > 0 ){
               recvString = msg;
         }

     }
     static void SendMessage(int sock,const string &message,\
                             struct sockaddr_in &peer)
     {
          sendto(sock,message.c_str(),message.size(),0,(struct sockaddr*)&peer,sizeof(peer));
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
             perror("bind");
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
        return sock;
    }   
    static bool Connect(int &sock,string peer_ip,const int &port) 
    {
        struct sockaddr_in peer;
        peer.sin_family = AF_INET;
        peer.sin_addr.s_addr = inet_addr(peer_ip.c_str());
        peer.sin_port = htons(port);
        if(connect(sock,(struct sockaddr*)&peer,sizeof(peer)) < 0){
          perror("ddsad");
          LOG("connect error",WARNING);
          return 0;
        }
        return 1;
	} 
};
