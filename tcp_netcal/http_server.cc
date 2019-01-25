#include"common.hpp"
#include<string.h>
static void Usage(string arg)
{
    cout << "Usage :" << arg <<endl;
}
void* HandleRequest(void* arg)
{
    int sock = (int)arg;
    char buf[10240];
    recv(sock,buf,sizeof(buf)-1,0);
    const char* status_line = "HTTP/1.1 200 OK\r\n";
    send(sock,status_line,strlen(status_line),0);
    const char* header  = "Content-Type:test/html\r\n";
    send(sock,header,strlen(header),0);
    const char* blank = "\r\n";
    send(sock,blank,strlen(blank),0);
    const char* text = "<html><h2>hello world</he></html>\r\n";
    send(sock,text,strlen(text),0);
    close(sock); 
}
int main(int argc,char* argv[])
{
    if(argc != 2){
       Usage(argv[0]);
       exit(0);
    }
    int listen_sock =socket(AF_INET,SOCK_STREAM,0);
    if(listen_sock < 0){
       cerr << "socket error"<<endl;
       exit(1);
    }
    struct sockaddr_in local;
    bzero(&local,sizeof(local));
    local.sin_family = AF_INET;
    local.sin_port = htons(atoi(argv[1]));
    local.sin_addr.s_addr = htonl(INADDR_ANY);
    if(bind(listen_sock,(struct sockaddr*)&local,sizeof(local)) < 0){
       cerr << "bind error" <<endl;
       exit(2);
      }
    if(listen(listen_sock,5) < 0){
       cerr << "listen  error" <<endl;
       close(listen_sock);
       exit(3);
      }
    struct sockaddr_in client;
    for( ; ; ){
       socklen_t len=sizeof(client);
       int sock = accept(listen_sock,(struct sockaddr*)&client,&len);
       if( sock < 0){
            continue; 
       }
       pthread_t tid;
       pthread_create(&tid,NULL,HandleRequest,(void*)sock);
    }
    return 0;
}
