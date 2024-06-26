#include "Server.hpp"
#include "CustomException.hpp"

//debug

Server::Server(const string& port_str,  const string& password) : _serverName(SERVER_NAME), _password(password)
{
    //Parsing for empty and invalid port/password
    if (port_str.empty() || password.empty() || !digitsCheck(port_str))
        throw CustomException::InvalidInputException();
    _port = std::atoi(port_str.c_str());
    if(_port > 65535 || _port < 0)
        throw CustomException::OutOfRangeException();
	_startTime = convertTimeToDateString(getTime());
}

Server::~Server() 
{
	std::map<int,Client*>::iterator it;
	for(it = _clients.begin(); it != _clients.end(); it++)
	{
		delete it->second;
	}	

	for (chIt it = _channels.begin(); it != _channels.end(); it++)
	{
		delete *it;
	}

	_clients.clear();
	_channels.clear();

	close(_sockfd);

}

bool Server::digitsCheck(const std::string &arg) const
{
    for(size_t i = 0; i < arg.size(); i++)
    {
        if(!isdigit(arg[i]))
            return false;
    }
    return true;
}

bool Server::nameCheck(const std::string &arg) const
{
    for(size_t i = 0; i < arg.size(); i++)
    {
        if(!isalpha(arg[i]) && !isdigit(arg[i]) && arg[i] != '[' && arg[i] != ']' 
			 && arg[i] != '{' && arg[i] != '}' && arg[i] != '\\' && arg[i] != '|')
			return false;
    }
    return true;
}


string Server::inputParsing(string s, Client *client)
{
	size_t i = s.find("\r");
	// printf("here %i %i %i %i\n", s[0],s[1],s[2],s[4]);
	if(i != string::npos)
	{
	//	printf("before %i %i\n",client->clientInput[0],client->clientInput[1]);
		string input = client->clientInput + s.substr(0, i);
		// printf("here %i %i\n", input[0],input[1]);
		//client->clientInput.clear();
		client->clientInput = s.substr(i + 1);
		client->clientInput = client->clientInput.substr(0,client->clientInput.size() - 1 );
		//printf("after %d  / %i %i\n",s.size(),client->clientInput[0],client->clientInput[1]);
		return input;
	}
	else
	{
		client->clientInput += s.substr(0, s.size());
		return "";
	}
}

void Server::newConnection(void)
{
	struct sockaddr_in clientSockInfo;
	memset(&clientSockInfo, 0, sizeof(clientSockInfo)); //fill with 0s to avoid undefined behaviors
	socklen_t len = sizeof(clientSockInfo);


	//struct addrinfo hint, *result, *res;
	int clientSocket = accept(_sockfd, (struct sockaddr *)&clientSockInfo, &len);
	if(clientSocket == -1)
		return ; //TODO: replace with error
	else
	{
		//TODO: parse for max users allowed
		if(getNbClients() >= MAX_USERS)
			return ; //TODO: add error message

		print("New client connected !");

		struct pollfd clientfd;
		clientfd.fd = clientSocket; 
		clientfd.events = POLLIN;

		_pollfd.push_back(clientfd);
		_clients.insert(std::make_pair(clientSocket, new Client(clientSocket)));
	}
}

void Server::ReadData(std::map<int,Client*>::iterator clientIt, string newInput)
{
	string input = inputParsing(newInput, clientIt->second);
	std::cout << input << std::endl;
	while(input.size())
	{
		//For skipping password, user and nick entry in debug mode
		if(skipPass){
			skipPassDebug(clientIt->second);
			skipPass = false;
			clientIt->second->setLimeState(false);
			return ;
		}
		//Check input with debug
		// dprint(DEBUG_STR("input: ", input));
		// dprint(DEBUG_STR("client buffer: ", clientIt->second->clientInput));

		//parse input for commands
		if(commandCalled.validCommand(input))
		{
			std::map<string, int(Server::*)(Client*, std::vector<string>)>::iterator it;//Th
			for(it = _commandsMap.begin(); it != _commandsMap.end(); it++)
			{
				if(commandCalled.getCommand() == it->first)
				{
					if(commandCalled.allowedCommand(clientIt->second->getState())){//clientIt->second->isAdmin() TODO: change isAdmin to check if client is operator in the channel called
						try{
							commandCalled.setReturn((this->*it->second)(clientIt->second, commandCalled.getArgs()));
						}
						catch(const std::exception& e){
							std::cerr << e.what() << std::endl;
						
						}
					}
					else
						sendMessage(clientIt->second, _serverName, clientIt->second->getUsername(), NOT_ALLOWED);
					commandCalled.commandReset();
					break;
				}	
			}
		}
		else if(!commandCalled.validCommand(input))
			sendMessage(clientIt->second, _serverName, clientIt->second->getUsername(), INVALID_CMD);
		// send(clientIt->second->getSocket(), INVALID_CMD, strlen(INVALID_CMD), 0);
		input.clear();
		// input = containsAdditionnal(clientIt->second); //TODO: fix to implement if the client buffer contains multiple commands that can be called
	}
}

void Server::IncomingData(int i)
{
	char buffer[MAX_BUFFER];
	int bytesRead = recv(_pollfd[i].fd, buffer, sizeof(buffer), 0);
	std::map<int,Client*>::iterator clientIt = _clients.find(_pollfd[i].fd);
	if(bytesRead == 0)
	{
		disconnectUser(clientIt->second, _pollfd);
		return ;
	}
	else if(bytesRead > 0)
	{
		ReadData(clientIt,string(buffer, bytesRead));
		
	}
}

int Server::Run()
{

	initCommandMap();
	initOptionMap();
	//Add server socket to the pollfd struct and push it in the vector container
	struct pollfd serverfd;
	memset(&serverfd, 0 , sizeof(serverfd)); // set memory to 0
	serverfd.fd = _sockfd;
	serverfd.events = POLLIN; //monitor for data available for reading

	_pollfd.push_back(serverfd);
	// dprint(DEBUG_MESS(_serverName, " is ready"));
	while(true)
	{
		if(poll(_pollfd.data(), _pollfd.size(), 0) == -1)
			throw CustomException::PollFailed();
			
		//Check if the server socket has incoming connection requests
		if(_pollfd[0].revents & POLLIN)
		{
			newConnection();
        }
		for (size_t i = 1; i < _pollfd.size(); i++)
		{
			if(_pollfd[i].revents & POLLIN)
			{
				IncomingData(i);
			}
		}
	}
	return 0;
}

void Server::SetupServer()
{
	//Creating a socket
	_sockfd = socket(AF_INET, SOCK_STREAM, 0); // ipv4 / TCP
	if (_sockfd == - 1) 
		throw CustomException::CouldNotCreatePort();

	int reuse = 1;
    if (setsockopt(_sockfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) < 0) 
    	throw std::runtime_error("Error with setsockopt");

	//Sets the socket to non blocking mode
	if (fcntl(_sockfd, F_SETFL, O_NONBLOCK) == -1) 
		throw CustomException::ErrorFcntl();

	//Define the server's address structure
	struct sockaddr_in address;
	memset(&address, 0, sizeof(address)); //fill with 0s to avoid undefined behaviors
	address.sin_family = AF_INET; //ipv4
	address.sin_addr.s_addr = INADDR_ANY;  // Listen on all interfaces
	address.sin_port = htons(_port); // from host byte order to network byte order

	//Bind the socket to a port and address
	if (bind(_sockfd, (struct sockaddr*)&address, sizeof(address)) == -1) 
		throw CustomException::ErrorBind();

	// Listen for incoming connections
	if (listen(_sockfd, SOMAXCONN) == -1) 
		throw CustomException::ErrorListen();

	std::cout << "Server listening ..." << std::endl;
}

double Server::getTime(void)
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	
	return tv.tv_sec + (tv.tv_usec / 1000000.0);
}

string Server::convertTimeToDateString(double timestamp) {
    time_t time = static_cast<time_t>(timestamp);
    struct tm* tm_info = localtime(&time);
    char buffer[80];

    strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", tm_info); 
    return std::string(buffer);
}

void::Server::authenticationMessage(Client*client) const{

	sendMessage(client, _serverName, client->getNickname(), AUTH_MESS);
	// send(sockfd, "For access, please enter the server password using the PASS command\n", 68, 0);
}

void Server::identificationMessage(Client*client) const{
	sendMessage(client, _serverName, client->getNickname(), IDENT_MESS);

	// send(sockfd, "password verified\n", 18, 0);
	// send(sockfd, "Please provide a username and a nickname using the USER and NICK command\n", 73, 0);
}

void Server::welcomeMessage(Client*client) const{
	std::stringstream ss;

	ss << _clients.size();
	std::string str;
	ss >> str;
	sendMessage(client, _serverName, client->getNickname(), "001 " + client->getNickname() + " :Welcome to the Minou Network, " + client->getNickname() + " " + client->getUsername() + "@Localhost");
	sendMessage(client, _serverName, client->getNickname(), "002 " + client->getNickname() + " :Your host is Minou.IRC running version Beta 1.1");
	sendMessage(client, _serverName, client->getNickname(), "003 " + client->getNickname() + " :This server was created " + _startTime);
	sendMessage(client, _serverName, client->getNickname(), "004 " + client->getNickname() + " :" + _serverName + " " + IRC_VERSION + " - " + MODE_NO_PARAM + " " + MODE_PARAM);
	sendMessage(client, _serverName, client->getNickname(), "005 " + client->getNickname() + " :PREFIX=(itkol)@+ CHANTYPES=# CHANLIMIT=#:0 MAXCHANNELS=200 NICKLEN=10 TOPICLEN=512 MAXTARGETS=200 :are supported by this server");
	sendMessage(client, _serverName, client->getNickname(), "251 " + client->getNickname() + " :There are " + str.c_str() + " users and 0 services on 1 server\r\n");
	//authenticationMessage(client);
}

void Server::sendMessage(Client*client, string source, string target, string message) const{

	if(client->getLimeState()){
		string limechatMessage = ":" + source +  PVM + target + " :" + message + "\r\n"; //<---- format
		send(client->getSocket(), limechatMessage.c_str(), limechatMessage.length(), 0);
	}
	else{
		string ncMessage = source + ": " + message + "\n";
		send(client->getSocket(), ncMessage.c_str(), ncMessage.length(), 0);
	}
}

void Server::sendMessage(Client*client, string source, string target, std::vector<string>& arg) const{

	string message;

	for (size_t i = 0; i < arg.size(); i++)
	{
		if (i + 1 != arg.size())
			message += arg[i] + " ";
		else
			message += arg[i];
	}

	if(client->getLimeState()){
		string limechatMessage = ":" + source +  PVM + target + " :" + message + "\r\n"; //<---- format
		send(client->getSocket(), limechatMessage.c_str(), limechatMessage.length(), 0);
	}
	else{
		string ncMessage = source + ": " + message + "\n";
		send(client->getSocket(), ncMessage.c_str(), ncMessage.length(), 0);
	}
}

void Server::checkIdentified(Client*client){
	if(client->getState() == IDENTIFICATION){
		if(!client->getUsername().empty() && !client->getNickname().empty()){
			client->setState(REGISTERED);
	
			sendMessage(client, SERVER_NAME, client->getUsername(), SUCCESS_REGISTER);
			welcomeMessage(client);
			// string ircMessage = ":" + _nickname +  PVM + _nickname + " :" + SUCCESS_REGISTER + "\r\n"; //<---- format
			// send(client->getSocket(), ircMessage.c_str(), ircMessage.length(), 0); 
		}
	}
}

string Server::getName(void)
{
	return (this->_serverName);
}

size_t Server::getNbClients(void){
	std::map<int,Client*>::iterator it;
	size_t i = 0;
	for(it = _clients.begin(); it != _clients.end(); it++)
		i++;
	return i;
}

void Server::skipPassDebug(Client* client){
	if(debug){
		std::vector<string> tmp;
		tmp.push_back(DEBUG_PASSWORD);
		pass(client, tmp);
		tmp.clear();
		tmp.push_back("tester");
		user(client, tmp);
		nick(client, tmp);
	}
}
