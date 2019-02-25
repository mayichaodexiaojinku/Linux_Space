#include"ProtocolUtil.hpp"
#include"UserManager.hpp"
class Server;
class Param
{
public:
    Server* sp;
    int sock;
public:
    Param(Server *sp_,int sock_)
        :sp(sp_)
        ,sock(sock_)
    {}
    ~Param()
    {}


};

class Server
{
private:
	int tcp_listen_sock;
	int tcp_port;
	int udp_work_sock;
	int udp_port;
	UserManager um;
public:
	Server(int tcp_port_ = 8080,int udp_port_ = 8888)
		:tcp_listen_sock(-1)
		 ,udp_work_sock(-1)
		 ,tcp_port(tcp_port_)
		 ,udp_port(udp_port_)
	{}
	void InitServer()
	{ 
		tcp_listen_sock = SocketApi::Socket(SOCK_STREAM);
		udp_work_sock = SocketApi::Socket(SOCK_DGRAM); 
		SocketApi::Bind(tcp_listen_sock,tcp_port);
		SocketApi::Bind(udp_work_sock,udp_port);
		SocketApi::Listen(tcp_listen_sock);
	}
	static void* HeaderRequest(void *arg)
	{
		Param *p = (Param*)arg;
		int sock = p->sock;
		Server* sp = p->sp;
		delete p;
		pthread_detach(pthread_self());
		Request rq;
		Util::RecvRequest(sock,rq);
        Json::Value root;
        Util::UnSeralizer(rq.text,root);
		if(rq.method == "REGISTER"){
              string name = root["name"].asString();
              string name = root["school"].asString();
              string name = root["passwd"].asString();
              unsigned int id = sp->RegisterUser(name,school,passwd);  
              send(sock,&id,sizeof(id),0);
		} 
 		else if(rq.method == "LOGIN"){
              string name = root["id"].asInt();
              string name = root["name"].asString();
              unsigned int result = sp->LoginUser(id,passwd);  
              send(sock,&result,sizeof(result),0);
             
		} 
		else{

        }
  






        close(sock);
     }
    
     void Strat()
     {
        string ip;
        int port;
        for(;;){
             int sock = SocketApi::Accept(tcp_listen_sock,ip,port);
             if(sock > 0){
                 cout << "get a new client" << ip << " : "<<port<<endl;
                 Param *p = new Param(this,sock);
                 pthread_t tid;
                 pthread_create(&tid,NULL,HeaderRequest,p);    
             }
        }

     }
     ~Server()
     {}

};
