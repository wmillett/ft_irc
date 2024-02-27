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

class Server
{
	private:
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
