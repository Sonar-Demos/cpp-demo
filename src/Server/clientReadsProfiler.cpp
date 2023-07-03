#include "pch.h"
#include "clientMain.h"


int main(int argc, char ** argv)
{
    if(argc > 3)
    {
        printf("Incorrect program start!\nSyntax is as follows: ");
        printf("%s <server_IP> <server_PORT>\n", argv[0]);
        return 1;    
    }
    int noOfStrings = argc;
    Client prog(noOfStrings, argv);
    prog.Init();
    prog.LoginRequest();
    prog.Runtime();
    return 0;
}