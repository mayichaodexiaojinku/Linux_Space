#include<my_global.h>
#include<mysql.h>
#include<stdio.h>
#include<stdlib.h>
static const char *host = "localhost";
static const char *user = "root";
static const char *password = "961203";
static const char *database = "db";
static void finish_with_error(MYSQL *con)
{
   fprintf(stderr,"Mysql 执行错误:%s\n",mysql_error(con));
   if(con){
       mysql_close(con);
   }
   exit(EXIT_FAILURE);
}
int main(int argc,char* argv[])
{
   if(argc < 2){
      fprintf(stderr,"必须指定姓名\n");
      return EXIT_FAILURE;
   }
   MYSQL *con = mysql_init(NULL);
   //连接数据库
   if(con == NULL){
      finish_with_error(con);
   }
   //连接数据库
   if(mysql_real_connect(con,host,user,password,database,0,NULL,0) == NULL){
      finish_with_error(con);
   }
   //设置客户端编码为utf8
   if(mysql_set_character_set(con,"utf8") != 0){
      finish_with_error(con);
   }
   //拼接查询query,这样拼接可能导致sql注入，需要调用mysql_escape_string系列
   char query[1000];
   sprintf(query,"select * from student where name = '%s'",argv[1]);
   printf("拼接出的SQL：%s\n",query);
   //执行SQL	
   if(mysql_query(con,query)){
     finish_with_error(con);
   }
   //获取查询结果，select相关类操作必须将结果用掉
   MYSQL_RES *result = mysql_store_result(con);
   if(result == NULL){
      finish_with_error(con);
   }
   
   int num_fields = mysql_num_fields(result);
   printf("列数：%d\n",num_fields);
   //分别打印每一行
   MYSQL_ROW row;
   while((row = mysql_fetch_row(result))){
     unsigned long *lengths;
     lengths = mysql_fetch_lengths(result);
     for(int i = 0;i < num_fields;++i){
         printf("[%.*s]",(int)lengths[i],row[i] ? row[i] : "NULL");
     }
     printf("\n");
   }
   mysql_free_result(result);
   mysql_close(con);
   return 0;
}
