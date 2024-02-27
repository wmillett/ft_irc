#include "Client.hpp"

Client::Client(int sockfd) : _sockfd(sockfd) {}

Client::~Client() 
{
	std::cout << "deleting " << _sockfd << std::endl;
}
