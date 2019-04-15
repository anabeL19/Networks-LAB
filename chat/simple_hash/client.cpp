// g++ client.cpp -o c -std=c++11
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fstream> //ifstream
#include <thread>
#include <iostream>
#include "hash.h"

using namespace std;

string readFile(string name)
{
  string txt;
	ifstream file(name, ios::binary | ios::ate);
  file.seekg(0, file.end);
  ios::pos_type pos = file.tellg();
  file.seekg(0, file.beg);

  char *buffer_txt = new char[pos];
  file.read(buffer_txt, pos);
  txt = buffer_txt;

  // cout<<buffer_txt<<endl;
	delete[] buffer_txt;
	file.close();
  return txt;
}

int main(int argc, char *argv[])
{
  struct sockaddr_in stSockAddr;
  int Res;
  int SocketFD = socket(AF_INET, SOCK_STREAM, 0); //IPPROTO_TCP

  if (-1 == SocketFD){
    perror("cannot create socket");
    exit(EXIT_FAILURE);
  }
 
  memset(&stSockAddr, 0, sizeof(struct sockaddr_in));
 
  stSockAddr.sin_family = AF_INET;
  stSockAddr.sin_port = htons(1100);
  Res = inet_pton(AF_INET, "127.0.0.1", &stSockAddr.sin_addr);
 
  if (0 > Res){
    perror("error: first parameter is not a valid address family");
    close(SocketFD);
    exit(EXIT_FAILURE);
  }
  else if (0 == Res){
    perror("char string (second parameter does not contain valid ipaddress");
    close(SocketFD);
    exit(EXIT_FAILURE);
  }
  if (-1 == connect(SocketFD, (const struct sockaddr *)&stSockAddr, sizeof(struct sockaddr_in))){
    perror("connect failed");
    close(SocketFD);
    exit(EXIT_FAILURE);
  }
  int buffer_size = 1000;
  string txt_plane;
  txt_plane = readFile("text.file");
  // cout<<"txt_plane "<<txt_plane<<endl;
  char buffer[4];
  string htxt;
  int n;
  string t;
  htxt = s_hash(txt_plane);
  n = write(SocketFD, txt_plane.c_str(), txt_plane.size());
	cout<<"hash client ---"<<htxt<<endl;
  n = read(SocketFD, buffer, 4);
  cout<<"recieve server"<<string(buffer)<<" - "<<buffer<<endl;
	if(n < 0) perror("Error writting to socket");
  if(string(buffer) == htxt)cout<<"ready "<<endl;
  else cout<<"error "<<endl;
 
  shutdown(SocketFD, SHUT_RDWR);
 
  close(SocketFD);
  return 0;
}
