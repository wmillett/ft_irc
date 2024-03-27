// messages end with /r/n. A CR-LF pair. no null terminator
#include <iostream>
#include <cstring>
#include <vector>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "../inc/utils.h"
#include "Server.hpp"

#include "../inc/Command.hpp"

#ifndef DEBUG
# define DEBUG 0
#endif

bool debug = false;
bool skipPass = false;

int main(int argc, char *argv[])
{
    if (argc != 3){
        std::cerr << USAGE_MESS << std::endl;
        return 1;
    }
    if(DEBUG == 1){
        debug = true;
        skipPass = true;
        print("\033[32;1mNow in debug mode\033[0m");
    }
    try
    {
        Server irc(argv[1],argv[2]);
		irc.SetupServer();
        irc.Run();
    }
    catch(std::exception & e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;  
}
