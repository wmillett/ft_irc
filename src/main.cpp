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


int main(int argc, char *argv[])
{
   // parse_args(argc, argv);

    if (argc != 3){
        std::cerr << USAGE_MESS << std::endl;
        return 1;
    }
    try
    {
        Server irc(argv[1],argv[2]);
        ///irc.run();
    }
    catch(std::exception & e)
    {
        std::cout << e.what() << std::endl;
    }
    return 0; 
}