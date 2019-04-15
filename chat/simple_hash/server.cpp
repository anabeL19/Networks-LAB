// g++ server.cpp -o s -std=c++11
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <thread>
#include <iostream>
#include "hash.h"

using namespace std;

int main(void)
{
    //sockaddr_in > basic structures for all syscalls and functions that deal with internet addresses
    struct sockaddr_in stSockAddr;
    int SocketFD = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

    if(-1 == SocketFD)
    {
        perror("can not create socket");
        exit(EXIT_FAILURE);
    }

    memset(&stSockAddr, 0, sizeof(struct sockaddr_in));

    stSockAddr.sin_family = AF_INET;
    stSockAddr.sin_port = htons(1100);
    stSockAddr.sin_addr.s_addr = INADDR_ANY; // aqui indica una sola tarjeta de red

    if(-1 == bind(SocketFD,(const struct sockaddr *)&stSockAddr, sizeof(struct sockaddr_in))){
        perror("error bin failed");
        close(SocketFD);
        exit(EXIT_FAILURE);
    }
    if(-1 == listen(SocketFD, 10)){
        perror("error listen failed");
        close(SocketFD);
        exit(EXIT_FAILURE);
    }

    //when client connect with accept and this socket designate the connection socket server
    int ConnectFD = accept(SocketFD, NULL, NULL);

    if(0 > ConnectFD){
      perror("error accept failed");
      close(SocketFD);
      exit(EXIT_FAILURE);
    }
    
    int b_size = 1000;//buffer size
    char buffer[b_size];
    int n;
    string txt;
    string msg;
    // for(;;){ 
    bzero(buffer, b_size); 
    n = read(ConnectFD, buffer, b_size);
    cout<<"----> "<<buffer<<endl;
    
    msg = s_hash(buffer);
    n = write(ConnectFD, msg.c_str(), msg.size());
    cout<<"send hash server-> "<<msg<<endl;
//    } 
    close(SocketFD);
    return 0;
}