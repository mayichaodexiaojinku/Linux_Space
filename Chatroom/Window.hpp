#pragma once
#include<string.h>
#include<iostream>
#include<ncurses.h>
#include"Message.hpp"
#include<pthread.h>
#include<string>
using namespace std;
class Window{
private:
	WINDOW *header;
	WINDOW *output;
	WINDOW *online;
	WINDOW *input;
    pthread_mutex_t lock;
public:
	Window()
	{
        pthread_mutex_init(&lock,NULL);
		initscr();
        curs_set(0);
	}
	void DrawHeader()
	{
		int h = LINES*0.2;
		int w = COLS;
		int y = 0;
		int x = 0;
        header = newwin(h,w,y,x);
        box(header,0,0);
        SafeWrefresh(header);
	}
	void DrawOutput()
	{
		int h = LINES*0.6;
		int w = COLS*0.7;
		int y = LINES*0.2;
		int x = 0;
        output = newwin(h,w,y,x);
        box(output,0,0);
        SafeWrefresh(output);
	}
	void DrawOnline()
	{
		int h = LINES*0.6;
		int w = COLS*0.3;
		int y = LINES*0.2;
		int x = COLS*0.7;
        online = newwin(h,w,y,x);
        box(online,0,0);
        SafeWrefresh(online);
	}
	void DrawInput()
	{
		int h = LINES*0.2;
		int w = COLS;
		int y = LINES*0.8;
		int x = 0;
        input = newwin(h,w,y,x);
        box(input,0,0);
        string tips = "Please Enter:";
        PutStringToWin(input,2,2,tips);
        SafeWrefresh(input);
    }
    void SafeWrefresh(WINDOW *w) 
    {
         pthread_mutex_lock(&lock);
         wrefresh(w);
         pthread_mutex_unlock(&lock);
    }
    void PutStringToWin(WINDOW* w,int y,int x,const string &message)
    {
         mvwaddstr(w,y,x,message.c_str());
         SafeWrefresh(w);
    }
    void GetStringFromInput(string &message)
    {
        char buffer[1024];
        memset(buffer,'\0',sizeof(buffer));
        wgetnstr(input,buffer,sizeof(buffer));
        message = buffer; 
        delwin(input);
        DrawInput();
    }
    void RunWelcome()
    {
        int x,y;
        int num = 2;
        int dict = 1;
        getmaxyx(header,y,x);
        string RunMessage = "Welcome To My Chat Room!";
        for( ; ; ){
            delwin(header);
            DrawHeader();
            PutStringToWin(header,y/2,num,RunMessage);
            if( num > x - RunMessage.size()-2){
                dict = 0;
            }
            if( num <= 2 ){
                dict = 1;
            }
            if(dict == 0){
                num--;
            }
            if(dict == 1){
                num++;
            }
            usleep(50000);
       
    
      
        }
        
    }
    void PutUserToOnline(vector<string> &online_user)
    {
        int line = 1;
        delwin(online);
        DrawOnline();
        for(int i = 0;i < online_user.size();i++){
		      PutStringToWin(online,line++,2,online_user[i]);
        }
    }
    void PutMessageToOutput(string &message)
    { 
        int x,y;
        static int line = 1;
        getmaxyx(output,y,x);
        PutStringToWin(output,line++,2,message);
		if(line > y - 1){
			delwin(output);
            DrawOutput();
			line = 1;
            PutStringToWin(output,line++,2,message);
		} 
	}
	~Window()
	{
        pthread_mutex_destroy(&lock);
  		endwin();
	}
};

