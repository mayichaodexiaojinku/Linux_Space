#include"ChatServer.hpp"
static void Uages(string proc)
{
     cout << "Uages:" << proc << "tcp_port udp_port"<< endl;
}
// ./Server  tcp_prot , udp_prot
int main(int argc,char *argv[])
{
   if(argc != 3){
      Uages(argv[0]);
      exit(1);
   }
   int tcp_port_ = atoi(argv[1]);
   int udp_port_ = atoi(argv[2]);
   Server *sp = new Server(tcp_port_,udp_port_);
   sp->InitServer();
   sp->Strat();
   return 0;
}
