#pragma once
#include "utils.h"


using std::string;

class Client
{
	private:
	int _socket;
	char _buffer[1024];

	public:
        Client(void);
        ~Client();
};
