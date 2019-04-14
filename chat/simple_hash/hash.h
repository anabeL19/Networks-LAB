#include <string.h>

using namespace std;
//simple hash
string s_hash(string message)
{
//     int hash = 0;
// 	for(unsigned int i=0; i<message.size(); i++){
// 		hash += message[i];
// 	}
// // 
// 	hash = hash%10;
// 	string shash = to_string(hash);
// 	for(unsigned int i=shash.size(); i<2; i++)
// 		shash = '0'+shash;
// // 
// return shash;
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