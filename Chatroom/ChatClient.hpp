#include"ProtocolUtil.hpp"
#include"Message.hpp"
#include"Window.hpp"
#include"UserManager.hpp"
#define TCP_PORT 8080
#define UDP_PORT 8888
class Client;
class Window;
struct ParamPair{
    Window* w;
    Client* cl;
};
class Client{
public:
      Client()
      {}
      Client(std::string ip_)
          :peer_ip(ip_)
      {
          id = 0;
          tcp_sock = -1;
          udp_sock = -1;
          server.sin_family = AF_INET;
          server.sin_port = htons(UDP_PORT);
          server.sin_addr.s_addr = inet_addr(peer_ip.c_str());
      }
      void InitClient()
      {
         tcp_sock = SocketApi::Socket(SOCK_STREAM);
         udp_sock = SocketApi::Socket(SOCK_DGRAM);
      }
      void InitTcpClient()
      {
         tcp_sock = SocketApi::Socket(SOCK_STREAM);
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
                if(id >= BEGIN_ID){
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
		  if(Util::LoginEnter(id,passwd) &&\
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
			  if(result >= BEGIN_ID){
				  cout << "Login success!" << id <<endl;
				  res =  true;
				  string t = "I am coming,talk with me....";
				  Message m(nick_name,school,t,id,LOGIN_TYPE);
				  string sendString;
				  m.ToSendString(sendString);
				  UdpSend(sendString); 
			  }
			  else{
				  cout << "Login Failed " << endl;  
			  }
			  close(tcp_sock);
			  return res;
	       }
	  }
	  void Logout()
	  {
		  if(ConnectServer()){
			  Request rq;
			  rq.method = "LOGOUT\n";
			  Json::Value root;
			  root["id"] = id;
			  Util::Serializer(root,rq.text);
			  rq.content_length ="content lenth: ";
			  rq.content_length +=Util::IntToString((rq.text).size());
			  rq.content_length +='\n';
			  Util::SendRequest(tcp_sock,rq);
			  unsigned int result = 0;  
			  recv(tcp_sock,&result,sizeof(result),0); 
			  if(result == 1){
				  string t = "Goodbye !!!!";      
				  Message m(nick_name,school,t,id,LOGOUT_TYPE);
				  string sendString;
				  m.ToSendString(sendString);
				  UdpSend(sendString); 
			  }
			  close(tcp_sock);
		  }
	  } 
	  void UdpSend(const string &msg)
	  {
		  Util::SendMessage(udp_sock,msg,server);
	  }
	  void UdpRecv(string &msg)
	  {
		  struct sockaddr_in peer;
		  Util::RecvMessage(udp_sock,msg,peer);
	  }
	  static void *RunHead(void *arg)
	  {
		  pthread_detach(pthread_self());
		  Window* w = (Window*)arg;
		  w->DrawHeader();
		  w->RunWelcome();
	  }
	  static void *Input(void *arg)
	  {
		  pthread_detach(pthread_self());
		  struct ParamPair *ptr = (struct ParamPair*)arg;
		  Window *wp = ptr->w;
		  Client *cp= ptr->cl;
		  wp->DrawInput();
		  string text;
		  for(;;){
			  wp->GetStringFromInput(text);
			  Message msg(cp->nick_name,cp->school,text,cp->id);
			  string sendString;
			  msg.ToSendString(sendString);
			  cp->UdpSend(sendString);             
			  }
      }
      void Chat(int flag)
      {
          Window w;
          if(flag == 1){
			  pthread_t r,l;
			  struct ParamPair pp = {&w,this};
			  pthread_create(&r,NULL,RunHead,&w);
			  pthread_create(&l,NULL,Input,&pp);
			  w.DrawOutput();
			  w.DrawOnline();
			  string recvString;
			  string showString;
			  vector<string> online;
			  for(;;){
				  string onlineString;
				  Message msg;
				  UdpRecv(recvString);
				  msg.ToRecvValue(recvString);
				  showString = msg.NickName();
				  showString +="-";
				  showString +=msg.School();
				  onlineString = showString;
				  if(msg.Id() != id ||msg.Type() == LOGIN_TYPE){
					  Util::AddUser(online,onlineString);
					  w.PutUserToOnline(online);
				  }
				  showString +=": ";
				  showString +=msg.Text();
				  w.PutMessageToOutput(showString);
				  if(msg.Type() == LOGOUT_TYPE){
					  Util::DeleteUser(online,onlineString);
					  w.PutUserToOnline(online);
				  }
			  }
		  }
          else
             w.~Window();
	  }
      ~Client()
      {}
       
public:
      unsigned int id;
      string nick_name;
      string school;
private:
      string passwd;
      string peer_ip;
      int tcp_sock;
      int udp_sock;
      struct sockaddr_in server;
      
};
