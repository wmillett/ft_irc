#pragma once
#include "utils.h"
#include "Client.hpp"
#include <map>

using std::string;

class Channel
{
	public:
	Channel(string name);
	~Channel(void);

	private:
	string _name;
	//std::map<bool, Client>* _connectedClients;
	/* bool indicates whether the connected 
	client is an operator or not */
		
};