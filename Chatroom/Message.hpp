#pragma once 
#include<iostream>         
#include<string>
#include"ProtocolUtil.hpp"
class Message{
private:
    string nick_name;
	string school;
	string text;
	unsigned int id;
public:
    Message()
    {}
	Message(const string &n_,const string &s_,const string &t_,\
			const unsigned int &id_)
		:nick_name(n_)
        ,school(s_)
        ,text(t_)
        ,id(id_)
	{}
    void ToSendString(string &sendString)
    {
        Json::Value root;
        root["name"] = nick_name;
        root["school"] = school;
        root["text"] = text;
        root["id"] = id;
        Util::Serializer(root,sendString);
    }
    void ToRecvValue(string &recvString)
    {
          Json::Value root;
          Util::UnSerializer(recvString,root);
          nick_name = root["name"].asString();
          school = root["school"].asString();
          text = root["text"].asString();
          id = root["id"].asInt(); 
    }
    string &NickName()
    {
       return nick_name;
    }
    string &School()
    {
       return school;
    }
    string &Text()
    {
       return text;
    }
    unsigned int  &Id()
    {
       return id;
    }
	~Message()
	{}



};
