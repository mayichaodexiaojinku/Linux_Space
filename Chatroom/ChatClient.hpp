#include"ProtocolUtil.hpp"
#include"UserManager.hpp"
#define TCP_PORT 8080
#define UDP_PORT 8888
class Client{
public:
      Client(std::string ip_)
          :peer_ip(ip_)
      {
          id = 0;
          tcp_sock = -1;
          udp_sock = -1;
      }
      void InitClient()
      {
         tcp_sock = SocketApi::Socket(SOCK_STREAM);
         udp_sock = SocketApi::Socket(SOCK_DGRAM);
      }
      bool ConnectServer()
      {
         return SocketApi::Connect(tcp_sock,peer_ip,TCP_PORT);
      }
      bool Register()
      {
          if(Util::RegisterEnter(nick_name,school,passwd)&&\
                                       ConnectServer()) {
                Request rq;
                rq.method = "REGISTER\n";
                Json::Value root;
                root["name"] = nick_name;
                root["school"] = school;
                root["passwd"] = passwd;
  
                Util::Serializer(root,rq.text);
                rq.content_length ="content lenth: ";
                rq.content_length +=Util::IntToString((rq.text).size());
                rq.content_length +='\n';
                Util::SendRequest(tcp_sock,rq);  
                recv(tcp_sock,&id,sizeof(id),0);       
                bool res = false;
                if(id >= 12345){
                    cout << "Register success! ,You ID is :" << id <<endl;
                    res =  true;              
                }
                else{
                    cout << "Register Failed " << endl;  
                }
                close(tcp_sock);
                return res;
           }
      }
      bool Login()
      {
          if(Util::LoginEnter(id,passwd)&&\
                                       ConnectServer()) {
                Request rq;
                rq.method = "LOGIN\n";
                Json::Value root;
                root["id"] = id;
                root["passwd"] = passwd;
  
                Util::Serializer(root,rq.text);
                rq.content_length ="content lenth: ";
                rq.content_length +=Util::IntToString((rq.text).size());
                rq.content_length +='\n';
                Util::SendRequest(tcp_sock,rq);
                unsigned int result = 0;  
                recv(tcp_sock,&result,sizeof(result),0);       
                bool res = false;
                if(result >= 12345){
                    cout << "Login success!" << id <<endl;
                    res =  true;              
                }
                else{
                    cout << "Login Failed " << endl;  
                }
                close(tcp_sock);
                return res;
           }

      }
      void Chat()
      {}
      ~Client()
      {}
       

private:
      unsigned int id;
      string peer_ip;
      int tcp_sock;
      int udp_sock;
};
