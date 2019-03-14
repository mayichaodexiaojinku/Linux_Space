#pragma once
#include<iostream>
#include<string>
#include<unordered_map>
#define BEGIN_ID 10000
class User{
private:
	string nick_name;
	string school;
	string passwd;
public:
	User(const string &n_,const string &s_,const string &pwd_)
         :nick_name(n_)
         ,school(s_)
         ,passwd(pwd_)
	{}
    bool IsPasswdRight(string p_)
    {
         return  passwd == p_ ? true : false;  
    } 
	~User()
	{}
};
class UserManager{
private:
    unsigned int assign_id;
    unordered_map<unsigned int,User> users;
    unordered_map<unsigned int,struct sockaddr_in> online_user;
public:    
   pthread_mutex_t lock; 
public:
    UserManager():assign_id(BEGIN_ID)
    {
        pthread_mutex_init(&lock,NULL);
    }
    void Lock()
    {
        pthread_mutex_lock(&lock);
    }
    void UnLock()
    {
        pthread_mutex_unlock(&lock);
    }
    unsigned int Insert(const string &n_,const string &s_\
                        ,const string &p_)
    {
        Lock();
        unsigned int id = assign_id++;
        User u(n_,s_,p_);
        if(users.find(id) == users.end()){
             users.insert({id,u});
             UnLock();
             return id;             
        } 
        UnLock();
        return 1;
    }
    unsigned int Check(const unsigned int &id,const string &passwd)
    {
        Lock();
        auto it = users.find(id);
        if( it != users.end()){
             User &u = it->second;
             if(u.IsPasswdRight(passwd)){
                UnLock();
                return id;
             }  
        }
        UnLock();
        return 2;
    }
    int DeleteOnlineUser(const unsigned int &id)
    {
        Lock();
        auto it =online_user.find(id);
        online_user.erase(it);
        UnLock();
        return 1;
    }
    void AddOnlineUser(const unsigned int &id,struct sockaddr_in &peer)
    {
       Lock();
       auto it = online_user.find(id);
       if( it == online_user.end()){
             online_user.insert({id,peer});
       }
       UnLock();   
    }
    unordered_map<unsigned int,struct sockaddr_in> Online()
    {
         Lock();
         auto online =  online_user;
         UnLock();
         return online;
    }
    
    ~UserManager()
    {
        pthread_mutex_destroy(&lock);
    }
};
