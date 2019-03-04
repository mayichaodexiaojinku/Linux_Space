#include"Window.hpp"
#include<unistd.h>
#include<locale.h>
int main()
{
    Window w;
    w.DrawHeader();
    //w.DrawOutput();
    //w.DrawOnline();
    //w.DrawInput();
    sleep(1000000000);
	return 0;
}
