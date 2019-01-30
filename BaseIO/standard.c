 /*这是一个回顾标准C库中 文件I/O的demo
*   fopen fclose fseek fwrite fread fprintf
 */
 #include<string.h>
 #include<stdio.h>
 int main()
 {  
     FILE *fp = NULL;
     fp = fopen("./test.txt","w+");
     if(fp == NULL){
       return -1;
       printf("perror\n");
       }
     char *ptr = "apple!";
     fwrite(ptr,strlen(ptr),1,fp);
     fseek(fp,0,SEEK_SET);
     char buf[1024] = {0};
     fread(buf,1024,1,fp);
     printf("buff:[%s]\n",buf);
     fprintf(fp,"\n%s-%d-%s\n","apple",3,"ass");
     fclose(fp);
     return 0;
}

