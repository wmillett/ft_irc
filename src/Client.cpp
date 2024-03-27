#include "Client.hpp"

Client::Client(int sockfd) : _sockfd(sockfd), _registration(AUTHENTICATION), _inLimechat(true), clientInput("") {

}

Client::~Client()
{
	dprint(DEBUG_VALUE("deleting ", _sockfd));
}

int Client::getSocket(void) const
{
	return (this->_sockfd);
}

Registration Client::getState(void) const{
	return _registration;
}

bool Client::getLimeState(void) const
{
	return _inLimechat;
}

void Client::setLimeState(bool toSet){
	_inLimechat = toSet;
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


void Client::addChannel(Channel* channel) // adds the channel to _channels
{
	this->_channels.push_back(channel);
}

void Client::removeChannel(Channel* channel) // removes the channel from _channels,
{
	for (chIt it = _channels.begin(); it < _channels.end(); it++)
	{
		if ((*it) == channel)
		{
			_channels.erase(it);
			return ;
		}
	}
}

void Client::leaveAllChannels(Server* server)
{
	for (chIt it = _channels.begin(); it != _channels.end(); it++)
	{
		(*it)->removeUser(server, this);
		_channels.erase(it);
		it--;
	}
}