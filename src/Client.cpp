#include "Client.hpp"

Client::Client(int sockfd) : _sockfd(sockfd), _registration(AUTHENTICATION), _admin(false), clientInput("") {

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

void Client::setState(Registration newState){
	_registration = newState;
}
void Client::checkIdentified(void){
	if(getState() == IDENTIFICATION){
		if(!getUsername().empty() && !getNickname().empty()){
			setState(REGISTERED);
			
			string ircMessage = ":" + _nickname +  PVM + _nickname + " :" + SUCCESS_REGISTER + "\r\n"; //<---- format
			send(getSocket(), ircMessage.c_str(), ircMessage.length(), 0); 

		}
	}
}