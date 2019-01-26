#include"tcp_clie.hpp"
static void Usage(string proc)
{
  cout << "Usage:" <<proc<<"server.port,server.ip"<<endl;
}
int main(int argc,char *argv[])
{
  if(argc != 3){
   Usage(argv[0]);
   exit(1);
   }
   int port_ = atoi(argv[2]);
   string ip_ = argv[1];
   Client * cp = new Client(port_,ip_);
   cp->InitClient();
   cp->Connect();
   cp->Run();
   delete cp;
   return 0;
}
