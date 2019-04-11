 /* Client code in C */
 
  #include <sys/types.h>
  #include <sys/socket.h>
  #include <netinet/in.h>
  #include <arpa/inet.h>
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  #include <unistd.h>
#include <fstream>
#include <thread>
#include <iostream>
#include "hash.h"

using namespace std;
char buffer[1000];

void openFile(string name, int size, char * buffer)
{
	ofstream file(name+".file", ofstream::binary);
	file.write(buffer, size);
	delete[] buffer;
	file.close();
}
//A[message type]+ userID+ msg size+msg
void r_ead(int SockedFD){
  int n=0;
  char *msg_buffer, *all_msg;
  msg_buffer = new char[1];
    n = read(SockedFD, msg_buffer,1);
  msg_buffer = new char[6];
    n = read(SockedFD, msg_buffer, 6);
  msg_buffer = new char[6];
    n = read(SockedFD, msg_buffer, 6);
  int msg_size = atoi(SockedFD);
  all_msg = new char[msg_size];
    n = read(SockedFD, all_msg,msg_size);
    cout<<"mensaje--->"<<all_msg<<endl;
}

void w_rite(int SocketFD){
  ifstream ifile("h_text.file", ifstream::binary);
  file.seekg(0, file.end());
  long size = file.tellg();
  file.seekg(0);

  char *txt_plane = new char[size];
  ifile.read(txt_plane, size);
  cout<<"txt_plane "<<txt_plane<<endl;
	int n;
	n = write(SocketFD,txt_plane,size);
	cout<<"sending ---"<<endl;

	if(n < 0) perror("Error writting to socket");
}
//buffer[10000]
  int main(int argc, char *argv[])
  {
    struct sockaddr_in stSockAddr;
    int Res;
    int SocketFD = socket(AF_INET, SOCK_STREAM, 0); //IPPROTO_TCP
    int n;
    //char buffer[256];
 
    if (-1 == SocketFD)
    {
      perror("cannot create socket");
      exit(EXIT_FAILURE);
    }
 
    memset(&stSockAddr, 0, sizeof(struct sockaddr_in));
 
    stSockAddr.sin_family = AF_INET;
    stSockAddr.sin_port = htons(1100);
    Res = inet_pton(AF_INET, "127.0.0.1", &stSockAddr.sin_addr);
 
    if (0 > Res)
    {
      perror("error: first parameter is not a valid address family");
      close(SocketFD);
      exit(EXIT_FAILURE);
    }
    else if (0 == Res)
    {
      perror("char string (second parameter does not contain valid ipaddress");
      close(SocketFD);
      exit(EXIT_FAILURE);
    }
 
    if (-1 == connect(SocketFD, (const struct sockaddr *)&stSockAddr, sizeof(struct sockaddr_in)))
    {
      perror("connect failed");
      close(SocketFD);
      exit(EXIT_FAILURE);
    }

    // thread tr(r_ead, SockedFD);
    thread tw(write, SockedFD); 
    // tr.join();
    tw.join();
    shutdown(SocketFD, SHUT_RDWR);
 
    close(SocketFD);
    return 0;
  }
