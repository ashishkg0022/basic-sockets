
#include<stdio.h> //header file
#include<string.h>    //header file
#include<string>  
#include<sys/socket.h>    
#include<arpa/inet.h> 
#include<netdb.h>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <vector> 
using namespace std ;
 
int main(int argc , char *argv[])
{
    int socket_desc; int readData ;
    char sorted [2000];
   
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
     
    if (socket_desc == -1)//for negative value
    {
        printf("Could not create socket");
    }
 struct sockaddr_in server;

 server.sin_addr.s_addr = inet_addr("127.0.0.1");
 server.sin_family = AF_INET;    server.sin_port = htons(8989);
  if (connect(socket_desc,(struct sockaddr*)&server,sizeof(server)) < 0)//to connect 
    {
       cout <<"connect error";
        return 1;
    }
       string s;
    cout << "Connected";
    int flag=0;
    ifstream fin("data.txt");
    while(getline(fin,s)){
         char data[100];
         memset(data, ' ', 100);
        for(int i=0;i<s.length(); i++)
        	{data[i]=s.at(i); if(data[i]=='#') flag =1;}
        if(flag==1)
        	break;
     if( send(socket_desc , data , s.length() , 0) < 0)
    {
        perror("Send failed : ");
        return false;
    }
    cout<<"Data send\n";
    memset(sorted, ' ', 100);
    readData =recv( socket_desc ,sorted, 1024 , 0);
    printf("sorted data : ");
    printf("%s\n",sorted );
     }
    return 0;
}
