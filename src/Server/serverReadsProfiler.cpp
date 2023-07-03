#include "pch.h"
#include "serverMain.h"
#include <fcntl.h>


int main()
{
    Server mainControlServer;
    mainControlServer.Init();
    mainControlServer.Runtime();
    return 0;
}