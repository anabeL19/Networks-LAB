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
    /*Structures for handling internet addresses*/
    struct sockaddr_in stSockAddr;
    int Res;
    /*the socket() call decide the type of socket: PF_INET just means it uses IP (which you always will); SOCK_STREAM and IPPROTO_TCP go together for a TCP socket.*/
    int SocketFD= socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    int n;

    if(-1 == SocketFD)
    {
        perror("cannot create socket");
        exit(EXIT_FAILURE);
    }

    /*copies the character c (an unsigned char) to the first n characters of the string pointed to, by the argument str.*/
    memset(&stSockAddr, 0, sizeof(struct sockaddr_in));

    stSockAddr.sin_family = AF_INET;
    stSockAddr.sin_port = htons(1200);
    /*function converts an Internet address in its standard text format into its numeric binary form. The argument af specifies the family of the address.*/
    Res = inet_pton(AF_INET, "127.0.0.1", &stSockAddr.sin_addr);

    if(0 > Res){
        perror("error: first parameter is not valid address family");
        close(SocketFD);
        exit(EXIT_FAILURE);
    }
    else if (0 == Res){
        perror("chat string (second parameter does not contain valid ipaddress)");
        close(SocketFD);
        exit(EXIT_FAILURE);
    }

    //conectarme con el servidor
    if(-1 == connect(SocketFD, (const struct sockaddr *)&stSockAddr, sizeof(struct sockaddr_in))){ 
        perror("connected failed");
        close(SocketFD);
        exit(EXIT_FAILURE);
    }

    char buffer[256];
    char msg[256];
    do{
        cout<< "Client Writting: ";
        cin.getline(msg, 256);
        n = write(SocketFD, msg, 256); // si hay la validacion se va a escribir en el socketFD, es como una variable donde guardo

        n = read(SocketFD, buffer, 256);
        cout << "Servigggddor: "<<buffer<<endl;
    }while(strncmp("END", buffer, 3)!=0);

    shutdown(SocketFD, SHUT_RDWR);

    close(SocketFD);
    return 0;
}