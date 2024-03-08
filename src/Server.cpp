#include "Server.hpp"
#include "Command.hpp"
#include "CustomException.hpp"
#include "utils.h"

Server::Server(const string& port_str,  const string& password) : _password(password), _serverName(SERVER_NAME)
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

int Server::Run()
{
	time_t startTime = getTime();
	SetupServer();

	std::vector<pollfd> fds;
	init();
	//Add server socket to the pollfd struct and push it in the vector container
	struct pollfd serverfd;
	memset(&serverfd, 0 , sizeof(serverfd)); // set memory to 0
	serverfd.fd = _sockfd;
	serverfd.events = POLLIN; //monitor for data available for reading

	fds.push_back(serverfd);

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
				std::cout << "New client connected!" << std::endl;
				//std::cout << "Time elapsed " << getTime() - startTime  << std::endl; //to test

				struct pollfd clientfd;
				clientfd.fd = clientSocket;
				clientfd.events = POLLIN;

                fds.push_back(clientfd);
                _clients.insert(std::make_pair(clientSocket, new Client(clientSocket)));
				send(clientSocket, "Welcome to ", 11, 0);
				send(clientSocket, &this->_serverName, this->_serverName.size() + 1, 0);
				send(clientSocket, " .\r\n", 4, 0);
			
            }

        }
		for (size_t i = 1; i < fds.size(); i++)
		{
			if(fds[i].revents & POLLIN)
			{
				char buffer[1024];
				int bytesRead = recv(fds[i].fd, buffer, sizeof(buffer), 0);
				if(bytesRead == 0)
				{
					std::cout << "Client disconnected" << std::endl;
					std::map<int,Client*>::iterator it = _clients.find(fds[i].fd);
					if(it != _clients.end()){
						delete it->second;
						_clients.erase(it);
					}

					close(fds[i].fd);
					fds.erase(fds.begin() + i);
					break ;
				}
				else if(bytesRead > 0)
				{
					string input = string(buffer, bytesRead - 1);
					std::cout << input << std::endl;

					if(commandCalled.validCommand(input))
					{
						std::map<string, int(Server::*)(Client*, std::vector<string>)>::iterator it;
						for(it = _commandsMap.begin(); it != _commandsMap.end(); it++)
						{
							if(commandCalled.getCommand() == it->first)
							{
       							(this->*it->second)(NULL, commandCalled.getArgs());
								commandCalled.commandReset();
								break;
							}	

						}
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