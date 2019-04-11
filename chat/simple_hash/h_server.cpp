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

void r_ead(int SocketFD)
{
  int n=0;
  char *msg_buffer, *all_msg;
  msg_buffer = new char[1];
    n = read(SocketFD, msg_buffer,1);
  msg_buffer = new char[6];
    n = read(SocketFD, msg_buffer, 6);
  msg_buffer = new char[6];
    n = read(SocketFD, msg_buffer, 6);
  int msg_size = atoi(SocketFD);
  all_msg = new char[msg_size];
    n = read(SocketFD, all_msg,msg_size);
    cout<<"mensaje--->"<<all_msg<<endl;
}

int main(void)
{
    //sockaddr_in > basic structures for all syscalls and functions that deal with internet addresses
    struct sockaddr_in stSockAddr;
    int SocketFD = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    char buffer[256];
    int n;

    if(-1 == SocketFD)
    {
        perror("can not create socket");
        exit(EXIT_FAILURE);
    }

    memset(&stSockAddr, 0, sizeof(struct sockaddr_in));

    stSockAddr.sin_family = AF_INET;
    stSockAddr.sin_port = htons(1200);
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

    for(;;){
        //cuando el cliente se conecta se cnecta con el accept y el socket descriptor que me va a indicar la conexion, 
        //socket del servidor
        int ConnectFD = accept(SocketFD, NULL, NULL);

        if(0 > ConnectFD){
            perror("error accept failed");
            close(SocketFD);
            exit(EXIT_FAILURE);
        }

    char msg[256];
    thread tr(r_ead, SocketFD);
    tr.join();

    close(SocketFD);
    return 0;
}