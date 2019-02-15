#ifndef _TCP_SERVER_HPP_
#define _TCP_SERVER_HPP_
#include<iostream>
#include<sys/socket.h>
#include<sys/types.h>
#include<unistd.h>
#include<strings.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<string>
#include<string.h>
#include<pthread.h>
#include<sys/wait.h>
#include"ThreadPool.hpp"
using namespace std;
class Server;
typedef struct{
     Server *sp;
     int sock;
}info_t;
class Server{
    private:
	int listen_sock;
	int port;
	ThreadPool pool;
    public:
	Server(const int &port_)
	    :port(port_),listen_sock(-1),pool(5)
	{}
	void  InitServer()
	{
	    listen_sock = socket(AF_INET,SOCK_STREAM,0);
	    if(listen_sock < 0)
	    {
		cerr << "socket error" <<  endl;
		exit(2);
	    }
	    int opt = 1;
	    setsockopt(listen_sock,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));//如何某个端口号的链接断开，能够立即重启这个端口
	    struct sockaddr_in local;
	    bzero(&local,sizeof(local));
	    local.sin_family = AF_INET;
	    local.sin_port = htons(port);
	    local.sin_addr.s_addr = htonl(INADDR_ANY);//本机任意主机号

	    if(bind(listen_sock,(struct sockaddr*)&local,sizeof(local)) < 0){
		cerr << "bind error "<< endl;
		exit(3);
	    }
	    if(listen(listen_sock,5) < 0){
		cerr <<  "listen error" << endl;
		close(listen_sock);
		exit(4);
	    }
	    signal(SIGCHLD,SIG_IGN);
	}
  
/*	static void *ThreadRun(void *arg)
	{
	  pthread_detach(pthread_self());
          info_t *info = (info_t*)arg;
	  Server *sp =info->sp;
          int sock = info->sock;
	  delete info;
	  sp->Service(sock);
	  close(sock);
	}
*/
	void Run()
	{
	    struct sockaddr_in peer;
	    for( ; ; ){
		socklen_t len = sizeof(peer);
		int sock = accept(listen_sock,(struct sockaddr*)&peer,&len);
		if(sock < 0){
		    cout << "accept error" << endl;
		    continue;
		}
		cout << "Get a new client" <<inet_ntoa(peer.sin_addr) << ":" <<ntohs(peer.sin_port) << endl;
	        Task t(sock,Service());
		pool.InitThreadPool();
	 /*     pthread_t tid;
		info_t *info = new info_t;
		info->sock = sock;
		info->sp = this;
		pthread_create(&tid,NULL,ThreadRun,(void*)info);
	*/
	/*	pid_t pid = fork();
		if(pid < 0){
		    cout << "fork error" <<endl;
		}
		else if(pid == 0){
		       if(fork() == 0){
		       Service(sock);
		       }
		    }
		else{
          	    close(sock);
		    waitpid(pid,NULL,0);
	        }
	*/
	   }
	}
        static void Service(int sock)
	{
	    char buf[1024];
	    while(1){
		ssize_t s = read(sock,buf,sizeof(buf)-1);
		if(s > 0){
		    buf[s] = '\0';
		    cout << "Client# "<<buf<<endl;
		    write(sock,buf,strlen(buf));
		}
		if(s == 0){
		    cout << "Client quit"<< endl;
		    break;
		}
		if(s < 0){
		    cerr << "read error"<<endl;
		    exit(5);
		}
	    }
	}
	~Server()
	{
	    close(listen_sock);
	}
};
#endif

