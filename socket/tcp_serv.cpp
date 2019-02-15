#include "tcp_serv.hpp"
static void Usage(string proc)
{
  cout << "Usage:" << proc << " port" <<endl;
}
int main(int argc,char *argv[])
{
  if(argc != 2){
     cout<< argc << endl;
     Usage(argv[0]);
     exit(1);
     }
    int port_ = atoi(argv[1]);
    Server *sp = new Server(port_);
    sp->InitServer();
    sp->Run();
    delete sp;

    return 0;
}
    
