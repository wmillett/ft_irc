#include "Server.hpp"

static bool checkNeedStr(char option, char orientation){

    if(orientation == '+'){
        return(option == 'k' || option == 'l' || option == 'o');
    }
    return (option == 'o');
};

bool Server::executeOption(Client *client, Channel &channel, char option, bool orientation, string *arg){
    string optionStr(1, option);
    for (std::map<std::string, void(Server::*)(Client *client, Channel &channel, bool orientation, string *arg)>::const_iterator it = _optionsMap.begin(); it != _optionsMap.end(); ++it) {
        if(it->first == optionStr){
            (this->*it->second)(client, channel, orientation, arg);
            return false;
        }
    }
    return true;
}

//Notes: will need to add a verification for every string argument encountered by validOptions
bool Server::validOptions(Client*client, Channel &channel, std::vector<string>arg){
    const char options[] = MODE_OPTIONS;
    const string modeStr = arg[1];
    const int sizeArg = arg.size();
    char currentOption = 0;
    char orientation = 0;
    int countArgs = 2;
    bool validCommand = 0;

    //Goes through modeStr to verify if every input is valid
    for(size_t i = 0; modeStr[i]; i++){
        while(isspace(modeStr[i])){
            i++;
        }
        validCommand = false;
        currentOption = modeStr[i];
        if(modeStr[i] == '+' || modeStr[i] == '-'){
            orientation = modeStr[i];
            currentOption = 0;
        }
        else{
            for(int j = 0; j < NB_OPTIONS; j++){
                if(modeStr[i] == options[j]){
                    validCommand = true;
                    break;
                }
				// print(("i: " + std::to_string(i)));
				// print(DEBUG_VALUE("i: ", i));
            }
        }
        if(orientation){
            if(currentOption){
                if(validCommand){
                    if(checkNeedStr(currentOption, orientation)){
                        if(countArgs < sizeArg)
                            executeOption(client, channel, currentOption, orientation, &arg[countArgs++]);
                        else
                            sendMessage(client, _serverName, client->getNickname(), MISSING_ARGUMENT(client->getNickname(), currentOption));
                    }
                    else{
                        executeOption(client, channel, currentOption, orientation, nullptr);
                    }
                }
                else
                    sendMessage(client, _serverName, client->getNickname(), ERR_UNKNOWNMODE(client->getNickname(), currentOption));
            }
            else
                ;
        }
        else
            sendMessage(client, _serverName, client->getNickname(), MISSING_ORIENTATION(client->getNickname(), currentOption));
    }
    return false;//
};

int Server::mode(Client*client, std::vector<string>arg)
{
	if(arg.size() == 0)
	{
		sendMessage(client, _serverName, client->getNickname(), MODE_USAGE);//or nothing? not sure how this case is even supposed to happen
		return true;
	}
	if (arg.size() > 1  && (arg[0].empty() || arg[1].empty()))
	{
		sendMessage(client, _serverName, client->getNickname(), MODE_USAGE);
		return true;
	}
	Channel* channel = isTargetAChannel(arg[0]);
    if(channel == nullptr){
        sendMessage(client, _serverName, client->getNickname(), ERR_NOSUCHCHANNEL(client->getNickname(), arg[0]));
        return true;
    }
	validOptions(client, *channel, arg);
	return false;
}

void Server::mode_i(Client *client, Channel &channel, bool orientation, string *arg)
{
	(void)arg;
	if(channel.isInviteOnly() == 0 && orientation)
		sendMessage(client, _serverName, client->getNickname(), CLIENT_MESS(client->getNickname(), " :channel is already set to invite only")); return;
	if(!channel.isInviteOnly() && !orientation)
		sendMessage(client, _serverName, client->getNickname(), CLIENT_MESS(client->getNickname(), " :channel is already set to not invite only")); return;
	channel.setInviteOnly(orientation);
	if(orientation)
		channel.sendMessage(this, client, ADD_INVITE(client->getNickname()));
	else
		channel.sendMessage(this, client, RM_INVITE(client->getNickname()));
}

void Server::mode_t(Client *client, Channel &channel, bool orientation, string *arg)
{
	(void)arg;
	if(channel.getTopicChange() && orientation)
		sendMessage(client, _serverName, client->getNickname(), CLIENT_MESS(client->getNickname(), " :channel is already set to restricted topic")); return;
	if(!channel.getTopicChange() && !orientation)
		sendMessage(client, _serverName, client->getNickname(), CLIENT_MESS(client->getNickname(), " :channel is already set to not restricted topic")); return;
	channel.setTopicChange(orientation);
	if(orientation)
		channel.sendMessage(this, client, ADD_TOPIC(client->getNickname()));
	else
		channel.sendMessage(this, client, RM_TOPIC(client->getNickname()));
}

void Server::mode_k(Client *client, Channel &channel, bool orientation, string *arg)
{
	if(orientation == false)
	{
		if(channel.getKey() == nullptr){
			sendMessage(client, _serverName, client->getNickname(), CLIENT_MESS(client->getNickname(), " :channel already has no password")); return;
		}
	    channel.setKey(NULL); 
		channel.sendMessage(this, client, CLIENT_MESS(client->getNickname(), " has removed the channel password")); return;
	}
	if(arg->empty()){
		sendMessage(client, _serverName, client->getNickname(), CLIENT_MESS(client->getNickname(), " :Error :No password provided")); return;
	}
	if(arg == channel.getKey()){
		sendMessage(client, _serverName, client->getNickname(), CLIENT_MESS(client->getNickname(), " :Error :Channel already set to this password")); return;
	}
	channel.setKey(arg);
	// sendMessage(client, _serverName, client->getNickname(), CLIENT_MESS(client->getNickname(), " :New channel password has been set"));//Broadcast to other users?
	channel.sendMessage(this, client, CLIENT_MESS(client->getNickname(), " has set a new channel password"));//Broadcast here
}

void Server::mode_o(Client *client, Channel &channel, bool orientation, string *arg)
{
	if(arg->empty())
		sendMessage(client, _serverName, client->getNickname(), CLIENT_MESS(client->getNickname(), " :Error :No user provided")); return;
	if(client->getNickname() == *arg)
		sendMessage(client, _serverName, client->getNickname(), CLIENT_MESS(client->getNickname(), " :Error :Not allowed to remove your channel operator privileges")); return;

	Client *target = channel.getUserByString(*arg);
	if(!target)
		sendMessage(client, _serverName, client->getNickname(), CLIENT_MESS(client->getNickname(), " :Error :No user corresponds with input")); return;

	if(orientation == true)
	{
		if(channel.isUserAnOp(target)){
			sendMessage(client, _serverName, client->getNickname(), CLIENT_MESS(client->getNickname(), " :Error :User is already a channel operator")); return;
		}
		channel.addUserOp(target);
		channel.sendMessage(this, client, ADD_OP(client->getNickname(), target->getNickname())); return;
	}
	channel.removeUserOp(target);
	channel.sendMessage(this, client, RM_OP(client->getNickname(), target->getNickname()));
}

void Server::mode_l(Client *client, Channel &channel, bool orientation, string *arg)
{
	if(orientation == false)
	{
		if(!channel.getUserLimit())
			sendMessage(client, _serverName, client->getNickname(), CLIENT_MESS(client->getNickname(), " :Error :This channel already has no user limit")); return;
		channel.setUserLimit(0);
		channel.sendMessage(this, client, RM_UL(client->getNickname())); return;
	}
	if(arg->empty()){
		sendMessage(client, _serverName, client->getNickname(), CLIENT_MESS(client->getNickname(), " :Error :No user limit provided")); return;
	}
	if(!digitsCheck(*arg)){
		sendMessage(client, _serverName, client->getNickname(), CLIENT_MESS(client->getNickname(), " :Error :User limit has an invalid format")); return;
	}
	if(channel.getUserLimit() == (unsigned int)std::atoi(arg->c_str())){
	sendMessage(client, _serverName, client->getNickname(), CLIENT_MESS(client->getNickname(), " :Error :Channel user limit has already been set to this value")); return;
	}
	channel.setUserLimit(atoi(arg->c_str()));
	channel.sendMessage(this, client, ADD_UL(client->getNickname(), *arg));
}
