#include"common.hpp"
static void Usage(string arg)
{
    cout << "Usage :" << arg <<endl;
}
void* HandleRequest(void* arg)
{
	int sock = (int)arg;
	Request req;
	Respond res;
        
	for( ; ; ){ 
		ssize_t s = recv(sock,&req,sizeof(req),0);
		if( s < 0){
			cerr<< "recv error " << endl;
		}
		else if( s == 0){
			cout << "client quit"<<endl;
		}
		else{
			switch(req.op){
				case '+':
					res.result = req.x+req.y;
					break;
				case '-':
					res.result = req.x-req.y;
					break;
				case '*':
					res.result = req.x*req.y;
					break;
				case '/':
					if(req.y == 0)
						res.status = -1;
					else
						res.result = req.x/req.y;
					break;
				case '%':
					if(req.y == 0)
						res.status = -1;
					else 
						res.result = req.x%req.y;
					break;
                                default:
                                        res.status = -2;
					res.result = 0;
                                        break;
			}
		}
		send(sock,&res,sizeof(res),0);
	}
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
