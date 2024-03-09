#include "Client.hpp"

Client::Client(int sockfd) : _sockfd(sockfd), _state(AUTHENTICATION), _operator(false) {}

Client::~Client() 
{
	std::cout << "deleting " << _sockfd << std::endl;
}

int Client::getSocket(void) const
{
	return (this->_sockfd);
}