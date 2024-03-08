#include "Client.hpp"

Client::Client(int sockfd) : _sockfd(sockfd) {}

Client::~Client() 
{
	std::cout << "deleting " << _sockfd << std::endl;
}

int Client::getSocket(void) const
{
	return (this->_sockfd);
}

string Client::getNickname(void) const
{
	return _nickname;
}

void Client::setNickname(string nickname) 
{
 	_nickname = nickname;
}

string Client::getUsername(void) const
{
	return _username;
}

void Client::setUsername(string username) 
{
 	_username = username;
}