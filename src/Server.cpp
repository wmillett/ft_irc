#include "Server.hpp"
#include "CustomException.hpp"

Server::Server(const string& port_str,  const string& password) : _serverName(SERVER_NAME), _password(password)
{
    //Parsing for empty and invalid port/password
    if (port_str.empty() || password.empty() || !digitsCheck(port_str))
        throw CustomException::InvalidInputException();
    _port = std::atoi(port_str.c_str());
    if(_port > 65535 || _port < 0)
        throw CustomException::OutOfRangeException();
}

Server::~Server() 
{
	std::map<int,Client*>::iterator it;
	for(it = _clients.begin(); it != _clients.end(); it++)
		delete it->second; 

	_clients.clear();

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
		client->clientInput += s.substr(0, s.size() - 1);
		return "";
	}
}

// string Server::containsAdditionnal(Client*client){

// 	size_t i = client->clientInput.find("\r\n");
// 	if (i != string::npos)
// 	{
// 		string input = client->clientInput.substr(0,i);
// 		client->clientInput.erase(0, i + 2);
// 		return input;
// 	}
// 	else
// 		return "";
// }

int Server::Run()
{
	// time_t startTime = getTime();
	SetupServer();

	std::vector<pollfd> fds;
	init();
	//Add server socket to the pollfd struct and push it in the vector container
	struct pollfd serverfd;
	memset(&serverfd, 0 , sizeof(serverfd)); // set memory to 0
	serverfd.fd = _sockfd;
	serverfd.events = POLLIN; //monitor for data available for reading

	fds.push_back(serverfd);
	dprint(DEBUG_MESS(_serverName, " is ready"));
	while(true)
	{
		if(poll(fds.data(), fds.size(), 0) == -1)
			throw CustomException::PollFailed();
			
		//Check if the server socket has incoming connection requests
		if(fds[0].revents & POLLIN)
		{
			struct sockaddr_in clientSockInfo;
			memset(&clientSockInfo, 0, sizeof(clientSockInfo)); //fill with 0s to avoid undefined behaviors
			socklen_t len = sizeof(clientSockInfo);


			//struct addrinfo hint, *result, *res;
			int clientSocket = accept(_sockfd, (struct sockaddr *)&clientSockInfo, &len);
			if(clientSocket == -1)
				break; //TODO: replace with error
			else
			{
				print("New client connected !");

				//std::cout << "Time elapsed " << getTime() - startTime  << std::endl; //to test

				struct pollfd clientfd;
				clientfd.fd = clientSocket;
				clientfd.events = POLLIN;

                fds.push_back(clientfd);
                _clients.insert(std::make_pair(clientSocket, new Client(clientSocket)));
				// welcomeMessage(clientSocket);
            }
        }
		for (size_t i = 1; i < fds.size(); i++)
		{
			if(fds[i].revents & POLLIN)
			{
				char buffer[MAX_BUFFER];
				int bytesRead = recv(fds[i].fd, buffer, sizeof(buffer), 0);
				std::map<int,Client*>::iterator clientIt = _clients.find(fds[i].fd);
				if(bytesRead == 0)
				{
					disconnectUser(clientIt->second, fds);
					break ; // ?
				}
				else if(bytesRead > 0)
				{
					string newInput = string(buffer, bytesRead);
					dprint(DEBUG_MESS("New input: ", newInput));
					// printf("%i %i %i %i read: %d\n", newInput[0],newInput[1],newInput[2],newInput[4], bytesRead); //
				//	std::cout << std::endl; // 
					string input = inputParsing(newInput, clientIt->second);
					while(input.size())
					{
						dprint(DEBUG_MESS("input: ", input));
						dprint(DEBUG_MESS("client buffer: ", clientIt->second->clientInput));
						dprint(DEBUG_MESS("Message from client: ", input));

						if(commandCalled.validCommand(input))
						{
							std::map<string, int(Server::*)(Client*, std::vector<string>)>::iterator it;
							for(it = _commandsMap.begin(); it != _commandsMap.end(); it++)
							{
								if(commandCalled.getCommand() == it->first)
								{
									if(commandCalled.allowedCommand(clientIt->second->getState(), false)){//clientIt->second->isAdmin() TODO: change isAdmin to check if client is operator in the channel called
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
							send(clientIt->second->getSocket(), INVALID_CMD, strlen(INVALID_CMD), 0);
						input.clear();
						// input = containsAdditionnal(clientIt->second); //TODO: fix to implement if the client buffer contains multiple commands that can be called
					}
				}
			}
		}
	}
	return 0;
}
/*
	TODO:
	Order of operations for connecting a host: https://modern.ircdocs.horse/#irc-concepts

	The recommended order of commands during registration is as follows:
	2. PASS
	3. NICK and USER

	Structure of a message:
	2. Command name
	3. Parameters (maximum of 15 parameters) separated by one space character each
	4. /r/n (CR_LF)
*/

void Server::SetupServer()
{
	//Creating a socket
	_sockfd = socket(AF_INET, SOCK_STREAM, 0); // ipv4 / TCP
	if (_sockfd == - 1) 
		throw CustomException::CouldNotCreatePort();

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

void::Server::authenticationMessage(Client*client) const{

	sendMessage(client, _serverName, client->getNickname(), AUTH_MESS);
	// send(sockfd, "For access, please enter the server password using the PASS command\n", 68, 0);
}

void Server::identificationMessage(Client*client) const{
	sendMessage(client, _serverName, client->getNickname(), IDENT_MESS);

	// send(sockfd, "Password verified\n", 18, 0);
	// send(sockfd, "Please provide a username and a nickname using the USER and NICK command\n", 73, 0);
}

void Server::welcomeMessage(Client*client) const{
	sendMessage(client, _serverName, client->getNickname(), "Limechat :Welcome to the Minou Network");
	// send(sockfd, "Welcome to ", 11, 0);
	// send(sockfd, &this->_serverName, this->_serverName.size() + 1, 0);
	// send(sockfd, " !\r\n", 4, 0);
	authenticationMessage(client);
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

// void Server::createChannel(Client* client, string name, string *key) // cannot fail
// {
// 	// TODO: create channel with given name and key, may not work with just <Channel>
// 	Channel newChannel(client, name, key);

// 	if (_channels.size() == _channels.capacity()) //TODO: maybe change this
// 		return ;
// 	_channels.push_back(newChannel);
// }

// Channel* Server::isChannelValid(string channel) //cannot fail, returns a pointer to the right channel or NULL
// {
// 	for (chIt it = _channels.begin(); it != _channels.end(); it++)
// 	{
// 		string channelName = it->getName();
// 		if (channelName.compare(channel) == 0)
// 		{
// 			return &(*it);
// 		}
// 	}
// 	return (NULL);
// }

// int Server::joinWithKeys(Client* client, std::vector<string> arg)
// {
// 	//TODO: fill once Server::join() is done
// }

void Server::checkIdentified(Client*client){
	if(client->getState() == IDENTIFICATION){
		if(!client->getUsername().empty() && !client->getNickname().empty()){
			client->setState(REGISTERED);
			
			sendMessage(client, SERVER_NAME, client->getUsername(), SUCCESS_REGISTER);
			// string ircMessage = ":" + _nickname +  PVM + _nickname + " :" + SUCCESS_REGISTER + "\r\n"; //<---- format
			// send(client->getSocket(), ircMessage.c_str(), ircMessage.length(), 0); 
		}
	}
}
