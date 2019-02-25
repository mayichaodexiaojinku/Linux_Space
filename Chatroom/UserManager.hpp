#pragma once
#include<iostream>
#include<string>
#include<unordered_map>
class User{
private:
	string nick_name;
	string school;
	string passwd;
public:
	User(const string &n_,const string &s_,const string &pwd_)
         :nick_name(n_)
         ,school(s_)
         ,passwd(pwd)
	{} 
	~User()
	{}
};
class UserManager{
private:
    unsigned int assign_id;
    unordered_map<unsigned int,User> users;
    unordered_map<unsigned int,struct sockaddr_in> online_user; 
public:
    UserManager():assign_id(12345)
    {}
    ~UserManager()
    {}
};
