#pragma once
#include "utils.h"


using std::string;

class Client
{
	private:
           int _sockfd;
	
	public:
        Client(int sockfd);
        ~Client();
};
