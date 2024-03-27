#ifndef SERVER_HPP
# define SERVER_HPP

//Librairies
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <unistd.h>
# include <sys/poll.h>
# include <fcntl.h>
# include <sys/time.h>
# include <time.h>

//Own dependencies
# include "Client.hpp"
# include "Command.hpp"
# include "utils.h"

# define SERVER_NAME "\033[35;1mMinou.IRC\033[0m"
# define SERVER_COLOR(x) x + "Minou.IRC"
# define SERVER_CSEND(x) x + "Minou.IRC: \033[0m"
# define SERVER_SEND "\033[35;1mMinou.IRC: \033[0m"
# define MAX_BUFFER 1024
# define IRC_VERSION "1.1"

//Limits
# define USERLEN 31
# define NICKLEN 10
# define MAX_USERS 20
# define MIN_USERS 1

//Debug
# define DEBUG_PASSWORD std::string("1234")


//Class dependencies
class Command;
class Client;
class Channel;


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
		string _startTime;
		std::map<int, Client*> _clients;
		std::vector<struct pollfd> _pollfd;
		std::vector<Channel*> _channels;
		std::map<string, int (Server::*)(Client*, std::vector<string>)> _commandsMap;
		std::map<string, void(Server::*)(Client *client, Channel &channel, bool orientation, string *arg)> _optionsMap;
		Command commandCalled; //tmp, pourrait le mettre dans les objets clients

		// sockaddr_in serverAddr;

		bool digitsCheck(const std::string &arg) const;
		bool nameCheck(const std::string &arg) const;
		double getTime();
		string convertTimeToDateString(double timestamp);

		// void authenticate();
		void authenticationMessage(Client*client) const;
		void identificationMessage(Client*client) const;
		void welcomeMessage(Client*client) const;
		// void sendPrivateError(int sockfd, string message) const;

		//Error handling
		void disconnectUser(Client*client, std::vector<pollfd> fds);

		// Join methods
		void createChannel(Client* client, string& name, string *key); // never fails
		int joinWithKeys(Client* client, std::vector<string> arg);
		int isChannelNameValid(string& name);
		std::vector<string> buildStrings(string arg, char delimiter, std::vector<string> vec);

		// PRIVMSG methods
		Client* isTargetAUser(string& target);
		Channel* isTargetAChannel(string& target);

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
	int privmsg(Client*client, std::vector<string>);

	//Mode commands
	// typedef void (*ModeFunction)(Client*, Channel&, bool, std::string*);
	void mode_i(Client *client, Channel &channel, bool orientation, string *arg);
	void mode_t(Client *client, Channel &channel, bool orientation, string *arg);
	void mode_k(Client *client, Channel &channel, bool orientation, string *arg);
	void mode_o(Client *client, Channel &channel, bool orientation, string *arg);
	void mode_l(Client *client, Channel &channel, bool orientation, string *arg);

	bool executeOption(Client *client, Channel &channel, char option, char orientation, string *arg);
	bool validOptions(Client*client, Channel &channel, std::vector<string>arg);
	
	//Debug
	void skipPassDebug(Client* client);

	//Utils commands
	void initCommandMap(void);
	void initOptionMap(void);
	void newConnection(void);
	void IncomingData(int index); 
	void ReadData(std::map<int,Client*>::iterator clientIt, string newInput);
	//parsing
	string inputParsing(string s, Client *client);
	string containsAdditionnal(Client*client);
	void checkIdentified(Client*client);
	public:
		Server(const string& port_str,  const string& password);
		~Server();

		void sendMessage(Client*client, string source, string target, string message) const;
		void sendMessage(Client*client, string source, string target, std::vector<string>& arg) const;
		string getName(void);
		// void dprint(string message) const; //Only to use with make debug
		int Run();
		void SetupServer();
};

#endif 