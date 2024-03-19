#include "Server.hpp"

bool Server::validOptions(const string mode) const{
    const char options[] = MODE_OPTIONS;
    //const string mode = _args[0];
    size_t i = 0;

    while(i < mode.size() && mode[i] == ' ')
        i++;
    if (mode[i] != '+' && mode[i] != '-')
        return false;
    i++;
    while(mode[i] && mode[i] != ' '){
        for(int j = 0; j < NB_OPTIONS; j++){
            if(mode[i] == options[j])
                break;
            if(j == NB_OPTIONS - 1)
                return false;
        }
        i++;
    }
    while(++i < mode.size() && mode[i] == ' ')
        ;
    if(mode[i])
        return false;
    return true;
}

int Server::mode(Client*client, std::vector<string>arg)
{
	(void)client;
	(void)arg;

	if (arg[0].empty() || arg[1].empty())
	{
		sendMessage(client, _serverName, client->getNickname(), MODE_USAGE);
		return false;
	}
	//TODO: check if channel exists (arg[0])
	if (!validOptions(arg[1])){
		sendMessage(client, _serverName, client->getNickname(), INVALID_MODE);
		return false;
	}
	std::cout << "mode" << std::endl;
	return 0;
}
