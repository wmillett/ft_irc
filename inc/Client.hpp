#pragma once
#include "utils.h"
#include "Channel.hpp"


using std::string;
class Channel;

class Client
{
	private:
		int _sockfd;
		string _username;
		string _nickname;
		Channel* _channelJoined;
	
	public:
		Client(int sockfd);
		~Client();
};
