#ifndef _ERRORMESSAGE_H_
#define _ERRORMESSAGE_H_

// Replies 001-004
#define RPL_WELCOME "<client> :Welcome to the <networkname> Network, <nick>[!<user>@<host>]"
#define RPL_YOURHOST "<client> :Your host is <servername>, running version <version>"
#define RPL_CREATED "<client> :This server was created <datetime>"
#define RPL_MYINFO "<client> <servername> <version> <available user modes> <available channel modes> [<channel modes with a parameter>]"

#define RPL_INVITING "<client> <nick> <channel>"

// Errors
#define NO_PORT "Error: no port provided"
#define NO_PASSWORD "Error: no password provided"
#define PORT_TOO_LARGE "Error: port provided is above the max limit"
#define PORT_TOO_SMALL "Error: port provided is under the min limit"
#define INVALID_INPUT  "Error: invalid input"
#define PORT_OUT_RANGE "Error: port provided is out of the range"
#define MISSING_ARGS "Error: missing 2 arguments"
#define USAGE_MESS "Error: Usage: ./ircserv <port> <password>"
#define NCREATE_PORT "Error: could not create port"
#define ERROR_BIND "Error: Failed to bind socket"
#define ERROR_LISTEN "Error: Failed to listen for connections"
#define ERROR_BLOCK "Error setting socket to non-blocking mode"
#define ERROR_POLL "Error: poll() failed"

#define ERR_NEEDMOREPARAMS "<client> <command> :Not enough parameters"
#define ERR_ALREADYREGISTERED "<client> :You may not reregister"
#define ERR_PASSWDMISMATCH "<client> :Password incorrect"
#define ERR_NONICKNAMEGIVEN "<client> :No nickname given"
#define ERR_ERRONEUSNICKNAME "<client> <nick> :Erroneus nickname"
#define ERR_NICKNAMEINUSE "<client> <nick> :Nickname is already in use"
#define ERR_NICKCOLLISION "<client> <nick> :Nickname collision KILL from <user>@<host>"
#define ERR_NOSUCHCHANNEL "<client> <channel> :No such channel"
#define ERR_CANNOTSENDTOCHAN "<client> <channel> :Cannot send to channel"
#define ERR_TOOMANYCHANNELS "<client> <channel> :You have joined too many channels"
#define ERR_BADCHANNELKEY "<client> <channel> :Cannot join channel (+k)"
#define ERR_CHANNELISFULL "<client> <channel> :Cannot join channel (+l)"
#define ERR_INVITEONLYCHAN "<client> <channel> :Cannot join channel (+i)"
#define ERR_BADCHANMASK "<channel> :Bad Channel Mask"
#define ERR_NOTONCHANNEL "<client> <channel> :You're not on that channel"
#define ERR_CHANOPRIVSNEEDED "<client> <channel> :You're not channel operator"
#define ERR_USERONCHANNEL "<client> <nick> <channel> :is already on channel"
#define ERR_USERNOTINCHANNEL "<client> <nick> <channel> :They aren't on that channel"
#define ERR_NOSUCHNICK "<client> <nickname> :No such nick/channel"
#define ERR_NOSUCHSERVER "<client> <server name> :No such server"
#define ERR_CANNOTSENDTOCHAN "<client> <channel> :Cannot send to channel" //PRIVMSG unknown channel
#define ERR_NORECIPIENT "<client> :No recipient given (<command>)"
#define ERR_NOTEXTTOSEND "<client> :No text to send"


#endif