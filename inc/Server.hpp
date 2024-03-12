#ifndef SERVER_HPP
# define SERVER_HPP

//Librairies
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <unistd.h>
# include <sys/poll.h>
# include <map>
# include <fcntl.h>
# include <sys/time.h>
# include <time.h>

//Own dependencies
# include "Client.hpp"
# include "Command.hpp"
# include "utils.h"


//Debug
# include "debug.h"

#define SERVER_NAME "Minou.IRC"


#define USERLEN 31
#define NICKLEN 10

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
	const string _serverName;
	int _port;
	int _sockfd;
	string _password;
	std::map<int, Client*> _clients;
	std::vector<struct pollfd> _pollfd;
	std::vector<Channel> _channels;
	std::map<string, int (Server::*)(Client*, std::vector<string>)> _commandsMap;
	Command commandCalled; //tmp, pourrait le mettre dans les objets clients

	// sockaddr_in serverAddr;

	bool digitsCheck(const std::string &arg) const;
	bool nameCheck(const std::string &arg) const;
	void SetupServer();
	double getTime();

	// void authenticate();
	void authenticationMessage(Client*client) const;
	void identificationMessage(Client*client) const;
	void welcomeMessage(Client*client) const;
	void print(string message) const;
	void sendPrivateError(int sockfd, string message) const;
	void sendMessage(int sockfd, string target, string message) const;
	
	//Error handling
	void disconnectUser(Client*client, std::vector<pollfd> fds, size_t i);

	// Join command methods
	Channel* isChannelValid(string channel); // returns 0 if channel already exists, 1 otherwise
	void createChannel(Client* client, string name, string *key); // never fails
	int joinWithKeys(Client* client, std::vector<string> arg);

	//Commands
	int nick(Client*client, std::vector<string>);
	int user(Client*client, std::vector<string>);
	int pass(Client*client, std::vector<string>);
	int quit(Client*client, std::vector<string>);
	int join(Client*client, std::vector<string>);
	int topic(Client*client, std::vector<string>);
	int names(Client*client, std::vector<string>);
	int invite(Client*client, std::vector<string>);
	int kick(Client*client, std::vector<string>);
	int mode(Client*client, std::vector<string>);

	//Server utils
	void buildStrings(string arg, char delimiter, std::vector<string> vec);

	void init(void);

	public:
	Server(const string& port_str,  const string& password);
	~Server();


	void dprint(string message) const; //Only to use with make debug
	int Run();
};

#endif