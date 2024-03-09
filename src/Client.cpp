#include "Client.hpp"

Client::Client(int sockfd) : _sockfd(sockfd), _registration(AUTHENTICATION), _admin(false) {

}

Client::~Client() 
{
	std::cout << "deleting " << _sockfd << std::endl;
}

int Client::getSocket(void) const
{
	return (this->_sockfd);
}

Registration Client::getState(void) const{
	return _registration;
}

bool Client::isAdmin(void) const{
	return _admin;
}
