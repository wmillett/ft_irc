#include "Server.hpp"

static bool checkNeedStr(char option, char orientation){

    if(orientation == '+'){
        return(option == 'k' || option == 'l' || option == 'o');
    }
    return (option == 'o');
};





// bool Server::executeOption(Client *client, Channel &channel, bool orientation, string *arg){

//     // void mode_i(Client *client, Channel &channel, bool orientation, string *arg);
//     // void mode_t(Client *client, Channel &channel, bool orientation, string *arg);
//     // void mode_k(Client *client, Channel &channel, bool orientation, string *arg);
//     // void mode_o(Client *client, Channel &channel, bool orientation, string *arg);
//     // void mode_l(Client *client, Channel &channel, bool orientation, string *arg);

// };








//Notes: will need to add a verification for every string argument encountered by validOptions
bool Server::validOptions(Client*client, std::vector<string>arg) const{
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
            }
        }
        if(orientation){
            if(currentOption){
                if(validCommand){
                    if(checkNeedStr(currentOption, orientation)){
                        if(countArgs < sizeArg){
                            //execute fct here
                            countArgs++;
                        }
                        else
                            sendMessage(client, _serverName, client->getNickname(), MISSING_ARGUMENT(client->getNickname(), currentOption));
                    }
                    else{
                        //execute fct
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
		return false;
	}
	if (arg.size() > 1  && (arg[0].empty() || arg[1].empty()))
	{
		sendMessage(client, _serverName, client->getNickname(), MODE_USAGE);
		return false;
	}
    if(isTargetAChannel(arg[0]) == nullptr){
        sendMessage(client, _serverName, client->getNickname(), ERR_NOSUCHCHANNEL(client->getNickname(), arg[0]));
        return false;
    }
	if(!validOptions(client, arg)){//TODO: see note above validOptions fct
	    sendMessage(client, _serverName, client->getNickname(), INVALID_MODE);
	    return false;
    }
	std::cout << "mode" << std::endl;
	return 0;
}














// int Server::validOptions(const string mode) const{
//     const char options[] = MODE_OPTIONS;
//     size_t i = 0;
//     char currentOption = 0;
//     char plusMinus = 0;

//     while(i < mode.size() && mode[i] == ' ')
//         i++;
//     if (mode[i] != '+' && mode[i] != '-')
//         return false;
//     plusMinus = mode[i];
//     i++;
//     while(mode[i] && mode[i] != ' '){
//         for(int j = 0; j < NB_OPTIONS; j++){
//             if(mode[i] == options[j]){
//                 currentOption = mode[i];
//                 break;
//             }
//             if(j == NB_OPTIONS - 1)
//                 return false;
//         }
//         i++;
//     }
//     while(++i < mode.size() && mode[i] == ' ')
//         ;
//     if(mode[i])
//         return false;
//     if(currentOption == 'o' || (currentOption == 'k' && plusMinus == '+') || (currentOption == 'l' && plusMinus == '+'))
//         return 2;//to take into account to check another parameter after
//     return true;
// }