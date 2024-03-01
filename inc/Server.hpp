#ifndef SERVER_HPP
# define SERVER_HPP

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/poll.h>
#include "utils.h"
#include <map>
#include <vector>
#include "Client.hpp"
#include <fcntl.h>

class Client;

using std::string;

/*
the server MUST keep track of the channel members, as
	well as the channel modes.

   When a client connection unexpectedly closes, a QUIT message is
   generated on behalf of the client by the server to which the client
   was connected.  No other message is to be generated or used.
*/

class Server
{
	private:
	string _serverName;
	int _port;
	int _sockfd;
	string _password;
	//std::vector<Client> _clients;
	std::map<int, Client*> _clients;
	std::vector<struct pollfd> _pollfd;
	size_t _clientCount; // for freeing the resources properly at the end and throughout
	// sockaddr_in serverAddr;

	bool digitsCheck(const std::string &arg) const;
	void SetupServer();
	void increaseCount();
	void decreaseCount();
	size_t getCount();

	public:
	Server(const string& port_str,  const string& password);
	~Server();

	int Run();
};

#endif
