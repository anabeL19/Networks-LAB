#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <vector>
#include <curses.h>
#include <unistd.h>
#include <ncurses.h>     // std::cout
#include <thread>         // std::thread, std::this_thread::sleep_for
#include <utility> //pair<>
#include <chrono> 
#include "worm.h"
//compila asi g++ mio.cpp -lncurses -o a
#define worm_HEAD 'O'
int TAM = 4;
using namespace std;

typedef struct _win_border_struct 
{
        chtype  ls, rs, ts, bs, tl, tr, bl, br;
}
WIN_BORDER;

typedef struct _WIN_struct 
{
        int height, width;
        WIN_BORDER border;
}
WIN;


vector< vector<char> > matrix;
vector< pair<int, int>> worm_body;
pair< int, int> worm_head; 
int dimL=80;
int dimA=80;
vector <char> naves;
// int key=0;
char direction=' ';
char space= ' ';
char avatar=' ';

int mod (int a,int b )
{
    if(a<0)
        return a+b;
    return a%b;
}

//llena la matriz
void start(int dimL, int dimA)
{
     vector<char> linea;
     matrix.clear();
     for(int i =0; i<dimA; i++)
     {
        linea.push_back(space);
     }
     for(int i =0; i<dimL; i++)
     {
        matrix.push_back(linea);
     }
}

void print()
{   
    clear();
    for(int i =0; i<dimL; i++){  
        for(int j =0; j<dimA; j++)
            printw ("%c", matrix[i][j]);
         printw("\n");
     }
     cbreak();
     refresh();   
}
//only start worm draw
// void init_worm(){
//     worm_body.push_back(make_pair(x , y+1));
//     worm_body.push_back(make_pair(x , y+2));
//     worm_body.push_back(make_pair(x , y+3));
// }

void worm_draw()//, char letra )
{   
  int x = worm_body[0].first;
  int y = worm_body[0].second;
  matrix[x][y] = '0';
 
//   worm_body.push_back(make_pair(x , y+1));
//   worm_body.push_back(make_pair(x , y+2));
//   worm_body.push_back(make_pair(x , y+3));
  for(int i=1; i<worm_body.size(); i++){
    matrix[worm_body[i].first][worm_body[i].second] = '#';
  }
}

int a =20;
int b =20;    
int key = 0;
int keys_move()
{
    key = getch ();
    if(key==115){
        a=(a+1)%(dimL-1);//S
        pair<int,int> tmp = worm_body[0];
        worm_body[0].first = (worm_body[0].first+1) % (dimL-1);

        for(int i=1; i<worm_body.size(); i++){
          pair<int,int> tmp2 = worm_body[i];
          worm_body[i] = tmp;
          tmp = tmp2;
        }
        direction='D';
    }
    if(key==97 ){
        b=(b-1)%(dimL-1);//A
        pair<int,int> tmp = worm_body[0];
        worm_body[0].second = (worm_body[0].second-1) % (dimL-1);

        for(int i=1; i<worm_body.size(); i++){
            pair<int,int> tmp2 = worm_body[i];
            worm_body[i] = tmp;
            tmp = tmp2;
        }
        direction='L';
    }
    if(key==119)
    {   
        a=(a-1)%(dimL-1);//W
        pair<int,int> tmp = worm_body[0];
        worm_body[0].first = (worm_body[0].first-1) % (dimL-1);

        for(int i=1; i<worm_body.size(); i++){
          pair<int,int> tmp2 = worm_body[i];
          worm_body[i] = tmp;
          tmp = tmp2;
        }
        direction='T';
    }
    if(key==100){
        b=(b+1)%(dimL-1);//D
        pair<int,int> tmp = worm_body[0];
        worm_body[0].second = (worm_body[0].second+1) % (dimL-1);

        for(int i=1; i<worm_body.size(); i++){
          pair<int,int> tmp2 = worm_body[i];
          worm_body[i] = tmp;
          tmp = tmp2;
        }

        direction='R';
    }
    if(a<0)a=dimL;
    if(b<0)b=dimA;
}

void update(char dir, int x, int y)
{ 
    int _x, _y;
    if(dir == 'T'){  //top
      pair <int, int> aux = worm_body[worm_body.size()-1];
           matrix[aux.first+1][aux.second] = space;
    }
    if(dir=='D'){  //down
      pair <int, int> aux = worm_body[worm_body.size()-1];
           matrix[aux.first-1][aux.second] = space;
    }

    if(dir=='R'){ //right
      pair <int, int> aux = worm_body[worm_body.size()-1];
           matrix[aux.first][aux.second-1] = space;
    }
    if(dir=='L'){ //left
      pair <int, int> aux = worm_body[worm_body.size()-1];
           matrix[aux.first][aux.second+1] = space;
    }
}

void PutBuffer(char buffer[7])
{
    char integer_string[32];

    worm_body.push_back(make_pair(20,20));
    worm_body.push_back(make_pair(20,21));
    worm_body.push_back(make_pair(20,22));
    worm_body.push_back(make_pair(20,23));


    // worm_body.push_back(make_pair(a, b));
    // worm_body.push_back(make_pair(a, b+1));
    // worm_body.push_back(make_pair(a, b+2));
    // worm_body.push_back(make_pair(a, b+3));
    if(avatar!=' '){
        buffer[0]='A';
        sprintf(integer_string, "%c", avatar);
        strcat(buffer,integer_string);
    }
    else {buffer[0]='M';
        buffer[0]='M';
        if(a<=9) strcat(buffer,"0"); 
        sprintf(integer_string, "%d", a);  
        strcat(buffer,integer_string); 

        if(b<=9) strcat(buffer,"0"); 
        sprintf(integer_string, "%d", b);
        strcat(buffer,integer_string); 

        sprintf(integer_string, "%c", direction);
        strcat(buffer,integer_string); 
    }
}
