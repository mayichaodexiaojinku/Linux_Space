#include"ProtocolUtil.hpp"
#include"UserManager.hpp"
#include"DataPool.hpp"
#include"Message.hpp"
class Server;
class Param
{
public:
    Server* sp;
    int sock;
    string ip;
    int port;
public:
    Param(Server *sp_,int sock_,string ip_,int port_)
        :sp(sp_)
        ,sock(sock_)
        ,ip(ip_)
        ,port(port_)
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
    DataPool pool;
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
    void Product()
    {
        string message;
        struct sockaddr_in peer;
        Util::RecvMessage(udp_work_sock,message,peer);
        cout << "debug :" << message <<endl;
        if(!message.empty()){
             pool.PutMessage(message);
             Message m;
             m.ToRecvValue(message);
             um.AddOnlineUser(m.Id(),peer);
        }
    }
    void Consume()
    {
        string message;
        pool.GetMessage(message);
        cout << "debug:" << message <<endl;

        auto online = um.Online();
        for(auto it = online.begin(); it != online.end();it++){
                  Util::SendMessage(udp_work_sock,message,it->second); 
        }
    }
    unsigned int RegisterUser(const string &name,const string school\
                              ,const string &passwd)
    {
          return um.Insert(name,school,passwd);
    } 
    unsigned int LoginUser(unsigned int &id,string &passwd)        
    {
         return  um.Check(id,passwd);
        
    }  
	static void* HeaderRequest(void *arg)
	{
		Param *p = (Param*)arg;
		int sock = p->sock;
		Server* sp = p->sp;
        int port = p->port;
		delete p;
		pthread_detach(pthread_self());
		Request rq;
		Util::RecvRequest(sock,rq);
        Json::Value root;
        Util::UnSerializer(rq.text,root);
		if(rq.method == "REGISTER"){
              string name = root["name"].asString();
              string school = root["school"].asString();
              string passwd = root["passwd"].asString();
              unsigned int id = sp->RegisterUser(name,school,passwd);  
              send(sock,&id,sizeof(id),0);
		} 
 		else if(rq.method == "LOGIN"){
              unsigned int id = root["id"].asInt();
              string passwd = root["passwd"].asString();
              unsigned int result = sp->LoginUser(id,passwd);
              send(sock,&result,sizeof(result),0);
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
                 Param *p = new Param(this,sock,ip,port);
                 pthread_t tid;
                 pthread_create(&tid,NULL,HeaderRequest,p);    
             }
        }

     }
     ~Server()
     {}

};
