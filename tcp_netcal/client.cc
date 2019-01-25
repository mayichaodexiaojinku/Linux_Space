#include"common.hpp"
static void Usage(string arg)
{
    cout << "Usage :" << arg <<endl;
}
int main(int argc,char *argv[])
{
    if(argc != 3){
       Usage(argv[0]);
       exit(0);
    }
    int sock =socket(AF_INET,SOCK_STREAM,0);
    if(sock < 0){
       cerr << "socket error"<<endl;
       exit(1);
    }
    struct sockaddr_in server;
    bzero(&server,sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(atoi(argv[2]));
    server.sin_addr.s_addr = inet_addr(argv[1]);
    if(connect(sock,(struct sockaddr*)&server,sizeof(server)) < 0){
          cerr <<"connect error " <<endl;
          exit(2);
      }  
    Request req;
    Respond res;
    for( ; ; ){
       cout << "Please enter < x, y,op >";
       cin >>req.x >>req.y>>req.op;
       send(sock,&req,sizeof(req),0);
       recv(sock,&res,sizeof(res),0);
       cout<< "status=" <<res.status <<endl;
       cout<< "result=" <<res.result <<endl;
    }
    close(sock);
    return 0;
}
