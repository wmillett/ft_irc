#include "Server.hpp"



Server::Server(const string& port_str,  const string& password) : _password(password)
{

    if (port_str.empty() || password.empty() || !digitsCheck(port_str))
        throw Server::InvalidInputException();

    _port = std::atoi(port_str.c_str());
    if(_port > 65535 || _port < 0)
        throw Server::PortOffRangeException();

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


const char* Server::InvalidInputException::what() const throw()
{
    return INVALID_INPUT;
}

const char* Server::PortOffRangeException::what() const throw()
{
    return PORT_OUT_RANE;
}