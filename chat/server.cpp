#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <iostream>
using namespace std;

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
    do{
            bzero(buffer, 256); //pone ceros en el buffer, el tamaño es para saber cuanto va a leer
            n = read(ConnectFD, buffer, 256); //lee el socket descriptor, devuelve un n que es el tamaño de lo que recibe
            if(n < 0) perror("ERROR reading from socket");
            cout <<"client: "<<buffer<<endl;

            cout << "Servidor writting: ";
            cin.getline(msg, 256);
            n = write(ConnectFD, msg, 256);
            if(n < 0) perror("ERROR writting from socket");
        }while(strncmp("END", buffer,3)!=0);
        shutdown(ConnectFD, SHUT_RDWR);
        close(ConnectFD);
    }

    close(SocketFD);
    return 0;
}