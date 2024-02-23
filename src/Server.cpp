#include "Server.hpp"
#include "CustomException.hpp"

Server::Server(const string& port_str,  const string& password) : _password(password)
{
    //Parsing for empty and invalid port/password
    if (port_str.empty() || password.empty() || !digitsCheck(port_str))
        throw CustomException::InvalidInputException();
    _port = std::atoi(port_str.c_str());
    if(_port > 65535 || _port < 0)
        throw CustomException::OutOfRangeException();

    //Creating a socket
    int sockfd;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
       throw CustomException::CouldNotCreatePort();
}

Server::~Server() {}

bool Server::digitsCheck(const std::string &arg) const
{
    for(size_t i = 0; i < arg.size(); i++)
    {
        if(!isdigit(arg[i]))
            return false;
    }
    return true;
}

int Server::launchServer(){
    
};