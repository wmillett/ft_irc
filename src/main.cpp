/* The port number is passed as an argument */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "../inc/utils.h"
#include "Server.hpp"


int main(int argc, char *argv[])
{
    if (argc != 3){
        std::cerr << USAGE_MESS << std::endl;
        return 1;
    }
    try
    {
        Server irc(argv[1],argv[2]);
        irc.Run();
    }
    catch(std::exception & e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0; 
}
