#pragma once 
#include<iostream>         
#include<string>
#include"ProtocolUtil.hpp"
#define NO_TYPE 0
#define LOGIN_TYPE 1
class Message{
private:
    string nick_name;
	string school;
	string text;
	unsigned int id;
    int type;
public:
    Message()
    {}
	Message(const string &n_,const string &s_,const string &t_,\
			const unsigned int &id_,int type_ = NO_TYPE)
		:nick_name(n_)
        ,school(s_)
        ,text(t_)
        ,id(id_)
        ,type(type_)
	{}
    void ToSendString(string &sendString)
    {
		Json::Value root;
		root["name"] = nick_name;
		root["school"] = school;
		root["text"] = text;
		root["id"] = id;
		root["type"] = type;
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
		type = root["type"].asInt();
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
    int &Type()
    {
       return type;
    }
	~Message()
	{}



};
