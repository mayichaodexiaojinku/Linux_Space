#include"ChatClient.hpp"
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
int main(int argc,char *argv[])
{
   if(argc != 2){
      Uages(argv[0]);
      exit(6);
   }
   int select = 0;
   Client *cp= new Client(argv[1]);
   cp->InitClient();
   while(1){
	   Menu(select);
	   switch(select){
		   case 1:
			   cp->Register();
			   break;
		   case 2:
			   if(cp->Login())
				   cp->Chat();
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
