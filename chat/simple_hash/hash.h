string hash(string message)
{
    char buffer[3];
    int sum = 0;
    for(int i=0; i<message.size(); i++)
    {
        sum += (int)message[i];
    }
    sum = sum % 1000;
    sprintf(buffer,"%03d",(unsigned int)sum);
    return buffer;
}