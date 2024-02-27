#include "Server.hpp"
#include "CustomException.hpp"

Server::Server(const string& port_str,  const string& password) : _password(password), _clientCount(0)
{
    //Parsing for empty and invalid port/password
    if (port_str.empty() || password.empty() || !digitsCheck(port_str))
        throw CustomException::InvalidInputException();
    _port = std::atoi(port_str.c_str());
    if(_port > 65535 || _port < 0)
        throw CustomException::OutOfRangeException();
}
  

Server::~Server() {}

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
	SetupServer();

	std::vector<pollfd> fds;

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
			int clientSocket = accept(_sockfd, NULL, NULL);
			if(clientSocket == -1)
				break; //replace with error
			else
			{
				std::cout << "New client connected!" << std::endl;

				struct pollfd clientfd;
				clientfd.fd = clientSocket;
				clientfd.events = POLLIN;

                fds.push_back(clientfd);
                
                _clients.insert(std::make_pair(clientSocket, new Client(clientSocket)));
				
            }
           
        }

		for (size_t i = 1; i < fds.size(); i++)
		{
			if(fds[i].revents & POLLIN)
			{
				char buffer[1024];
				int bytesRead = recv(fds[i].fd, buffer, sizeof(buffer), 0);
				if(bytesRead > 0)
				{
					std::cout << string(buffer, bytesRead) << std::endl;
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
	CAP stuff is NOT required
	1. CAP LS 302
	2. PASS
	3. NICK and USER
	4. Capability Negotiation
	5. SASL (if negotiated)
	6. CAP END

	Structure of a message:
	1. Prefix starting with ':', has to be followed by "nick!username" of said client (optional)
	2. Command name or 3 digit number in ASCII
	3. Parameters
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
}

void Server::increaseCount(void)
{
	if (_clientCount < std::numeric_limits<unsigned long int>::max())
		_clientCount++;
}

void Server::decreaseCount(void)
{
	if (_clientCount > std::numeric_limits<unsigned long int>::min())
		_clientCount--;
}

size_t Server::getCount(void)
{
	return (_clientCount);
}