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

int Server::Run()
{
    SetupServer();

    return 0;
}

void Server::SetupServer()
{
    //Creating a socket
    _sockfd = socket(AF_INET, SOCK_STREAM, 0); // ipv4 / TCP
    if (_sockfd == - 1) 
       throw CustomException::CouldNotCreatePort();

    //Sets the socket to non blocking mode
    if (fcntl(_sockfd, F_SETFL, fcntl(_sockfd, F_GETFL, 0) | O_NONBLOCK) == -1) 
        throw CustomException::ErrorFcntl();

    //Define the server's address structure
    struct sockaddr_in address;
    memset(&address, 0, sizeof(address)); //fill with 0s to avoid undefined behaviors
    address.sin_family = AF_INET; //ipv4
    address.sin_addr.s_addr = INADDR_ANY;  // Listen on all interfaces
    address.sin_port = htons(_port); // from host byte order to network byte order

    //Bind the socket to a port and address
    if (bind(_sockfd, (struct sockaddr*)&address, sizeof(address)) == -1) 
        throw CustomException::ErrorBind();

    // Listen for incoming connections
    if (listen(_sockfd, SOMAXCONN) == -1) 
        throw CustomException::ErrorListen();
}



