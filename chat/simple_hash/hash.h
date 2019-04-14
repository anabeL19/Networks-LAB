#include <string.h>

using namespace std;
//simple hash
string s_hash(string message)
{
    char buffer[4];
    int sum = 0;
    for(int i=0; i<message.size(); i++)
    {
        sum += message[i];
    }
    sum = sum % 1000;
    sprintf(buffer,"%04d",(unsigned int)sum);
    return buffer;
}