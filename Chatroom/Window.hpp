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
        box(header,0,0);
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
        getmaxyx(header,y,x);
        string RunMessage = "Welcome To My Chat Room";
        for( ; ; ){
            delwin(header);
            DrawHeader();
            PutStringToWin(header,y/2,num,RunMessage);
            if( num > x - RunMessage.size()-2){
                num--;
            }
            if( num <= 2 ){
                num++;
            }
        }
        
    }
    void PutMessageToOutput(string &message)
    { 
        int x,y;
        int line = 2;
        getmaxyx(output,y,x);
        for( ; ; ){
             PutStringToWin(output,line++,2,message);
             if(line > y - 2){
                 delwin(output);
			     DrawOutput();
                 line = 2;
             }
             
        }
    }
	~Window()
	{
        pthread_mutex_destroy(&lock);
  		endwin();
	}
};

