#include<stdio.h>
#include<stdlib.h>
#include<mcheck.h>
int main()
{
   setenv("MALLOC_TRACE","output.out",1);
   mtrace();
   int *p = (int*)malloc(2*sizeof(int));
   return 0;
}
