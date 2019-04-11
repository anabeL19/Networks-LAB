 /* Client code in C */
 //COMPILAR g++ client.cpp -std=c++11  -pthread -lncurses -o c
 #include <sys/types.h>
 #include <sys/socket.h>
 #include <netinet/in.h>
 #include <arpa/inet.h>
 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <unistd.h>
 #include <iostream>
 #include <thread>
 #include "lib.h"
 //#include "worm.h"
  
 using namespace std;

 struct sockaddr_in stSockAddr;
 int Res;
 int SocketFD = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
 int n;

 void w_rite()
 {
     for(;;){
       char buffer[8];
       keys_move();
       for (int i = 0; i < sizeof(buffer); i++)      
            buffer[i] = '\0';
       PutBuffer(buffer);
       n = write(SocketFD, buffer, sizeof(buffer));
     }

 }

void r_ead()
{
    for(;;)
    {
        char buffer[7];
        n = read(SocketFD,buffer,sizeof(buffer));
        if (n < 0) perror("ERROR reading from socket");
        if(buffer[0] == 'A'){
          avatar = buffer[1];
        }
        if(buffer[0] == 'M'){
          char lives;
          string ac ;
          string ab ;
          ac += buffer[2];  //posiccion x 
          ac += buffer[3];
          ab += buffer[4];  //posicion y 
          ab += buffer[5];
          lives += buffer[6];        
  //cout<<"ac: "<<ac<<" ab: "<<ab<<endl;
          int a = stoi(ac); //a                 //De char a entero
          int b = stoi(ab);//b
          //cout<<"a: "<<a<<" b: "<<b<<endl;
        
          // worm_body.push_back(make_pair(a , b));
          // worm_head = make_pair(a, b);
          // worm_body.push_back(worm_head);
          worm_draw();//'A'+ buffer[0]);
          update(buffer[6],a,b);
        }
 
    WIN win;
        WIN win2;
        int ch;
        initscr();                      /* Start curses mode            */
        start_color();                  /* Start the color functionality */
        cbreak();                       /* Line buffering disabled, Pass on
                                         * everty thing to me           */
        keypad(stdscr, TRUE);           /* I need that nifty F1         */
        noecho();
        init_pair(1, COLOR_CYAN, COLOR_BLACK);
        attron(COLOR_PAIR(1));
        refresh(); 
      print();
    }
 }

 int main(void)
 {

   initscr ();  
   start(dimL, dimA);


   if (-1 == SocketFD)
   {
     perror("cannot create socket");
     exit(EXIT_FAILURE);
   }

   memset(&stSockAddr, 0, sizeof(struct sockaddr_in));

   stSockAddr.sin_family = AF_INET;
   stSockAddr.sin_port = htons(1200);
   Res = inet_pton(AF_INET, "127.0.0.1", &stSockAddr.sin_addr);
  // Res = inet_pton(AF_INET, "192.168.164.37", &stSockAddr.sin_addr);

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


   //imprimir();
   thread t1 (r_ead); 
   thread t2 (w_rite); 
   t1.join();
   t2.join();
     /*t1.join();
     t2.join();
     t3.join();*/

   shutdown(SocketFD, SHUT_RDWR); 
   close(SocketFD);
   endwin ();
   return 0;
 }