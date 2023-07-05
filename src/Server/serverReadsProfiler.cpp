#include "pch.h"
#include "serverMain.h"
#include <fcntl.h>
#include <json-c/json.h>

void readFromFile(const char* fname, void* b, size_t size) {
    int fd = open(fname, O_CREAT);
    read(fd, b, size);
    close(fd);
}

void initFromConfig(Server *server) {
    auto buffer = server->makeATempBuf();
    readFromFile("config.json", buffer, server->getMaxEntries());
    auto config = json_tokener_parse(buffer);
    json_object *nUsers;
    json_object_object_get_ex(config, "nUsers", &nUsers);
    json_object_get_int(nUsers);
    free(buffer);
}

int main()
{
    Server mainControlServer;
    mainControlServer.Init(1024);
    initFromConfig(&mainControlServer);
    mainControlServer.Runtime();

    return 0;
}
