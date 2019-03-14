#include"ChatClient.hpp"
#include<signal.h>
#include<sys/types.h>
#include<stdlib.h>
static Client *cp= new Client;
static void Uages(std::string proc)
{
    cout << "Uages:"<< proc << "peer_ip"<<endl;
}
static void Menu(int &s)
{
   cout << "**************************************"<<endl;
   cout << "*********** 1.Register ***************"<<endl;
   cout << "*********** 2.Login    ***************"<<endl;
   cout << "*********** 3.Exit     ***************"<<endl;
   cout << "**************************************"<<endl;
   cout << "Plaser Select :>";
    cin >> s;  
}
void Headler(int a)
{
  cp->InitTcpClient();
  cp->Logout();
  cp->Chat(0);
  exit(0);
  return;
}
int main(int argc,char *argv[])
{
   if(argc != 2){
      Uages(argv[0]);
      exit(6);
   }
   cp= new Client(argv[1]);
   if(signal(SIGINT,Headler) == SIG_ERR){
       perror("signal error");
   }
   int select = 0;
   while(1){
       cp->InitClient();
	   Menu(select);
	   switch(select){
		   case 1:
			   cp->Register();
			   break;
		   case 2:
			   if(cp->Login())
				   cp->Chat(1);
			   else
				   cout << "Login default"<<endl; 
			   break;
		   case 3:
			   exit(0);
			   break;
		   default:
			   exit(1);
			   break;
	   }
   }
}
