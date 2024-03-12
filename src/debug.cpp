#include "Server.hpp"

void Server::dprint(string message) const{
    if(debug)
        this->print(message);
}
