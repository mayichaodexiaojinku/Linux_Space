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
	Message(const string &n_,const string &s_,const string &t_,\
			const unsigned int &id_)
		:
	{}
	~Message()
	{}



};
