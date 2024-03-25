#include "Server.hpp"

void Server::disconnectUser(Client* client, std::vector<pollfd> fds) {


	// std::cout << "Client disconnected" << std::endl;
					// if(clientIt != _clients.end()){
					// 	delete clientIt->second;
					// 	_clients.erase(clientIt);
					// }
    //std::cout << "Client disconnected: " << client->getUsername() << std::endl;
	client->leaveAllChannels(this);
    _clients.erase(client->getSocket());
	close(client->getSocket());
    std::vector<pollfd>::iterator it;
	for(it = fds.begin(); it != fds.end(); it++){
		if(it->fd == client->getSocket()){
        fds.erase(it);
        break ;
        }
    }
	// fds.erase(fds.begin() + i);

    // close(client->getSocket());
    // for (auto it = fds.begin(); it != fds.end(); ++it) {
    //     if (it->fd == client->getSocket()) {
    //         fds.erase(it);
    //         break;
    //     }
    // }
    delete client;
}
