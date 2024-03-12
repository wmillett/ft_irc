#include "Server.hpp"

void Server::disconnectUser(Client* client, std::vector<pollfd> fds, size_t i) {


	// std::cout << "Client disconnected" << std::endl;
					// if(clientIt != _clients.end()){
					// 	delete clientIt->second;
					// 	_clients.erase(clientIt);
					// }
    std::cout << "Client disconnected: " << client->getUsername() << std::endl;
    _clients.erase(client->getSocket());
	close(fds[i].fd);	
	fds.erase(fds.begin() + i);

    // close(client->getSocket());
    // for (auto it = fds.begin(); it != fds.end(); ++it) {
    //     if (it->fd == client->getSocket()) {
    //         fds.erase(it);
    //         break;
    //     }
    // }
    delete client;
}
