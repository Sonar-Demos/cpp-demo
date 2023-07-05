#include "pch.h"
#include "serverMain.h"
#include <fcntl.h>


int main()
{

    Server mainControlServer;
    mainControlServer.Init();
    mainControlServer.Runtime();

    char *clientRequest = (char*)malloc(256);
    read(0, clientRequest, 1024);
    return 0;
}
