#pragma once
#include<iostream>
#include<unistd.h>
#include<sys/types.h>
#include<strings.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<pthread.h>
using namespace std;
typedef struct{
       int x;
       int y;
       char op;
}Request;
typedef struct{
       int status;
       int result;
}Respond;
