#pragma once
#include<iostream>
#include<ncurses.h>
class Window{
private:
	WINDOW *header;
	WINDOW *output;
	WINDOW *online;
	WINDOW *input;
public:
	Window()
	{
		initscr();

	}
	void DrawHeader()
	{
		int h = LINES/5;
		int w = COLS;
		int y = 0;
		int x = 0;
        header = newwin*(h,w,y,x);
        box(header,0,0);
        wrefresh(online);
	}
	~Window()
	{
		endwin();
	}


}
