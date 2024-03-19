#ifndef _ERRORMESSAGE_H_
# define _ERRORMESSAGE_H_

// Replies 001-004
# define RPL_WELCOME "<client> :Welcome to the <networkname> Network, <nick>[!<user>@<host>]"
# define RPL_YOURHOST "<client> :Your host is <servername>, running version <version>"
# define RPL_CREATED "<client> :This server was created <datetime>"
# define RPL_MYINFO "<client> <servername> <version> <available user modes> <available channel modes> [<channel modes with a parameter>]"

# define RPL_INVITING "<client> <nick> <channel>"

// Errors
# define NO_PORT "Error: no port provided"
# define NO_PASSWORD "Error: no password provided"
# define PORT_TOO_LARGE "Error: port provided is above the max limit"
# define PORT_TOO_SMALL "Error: port provided is under the min limit"
# define INVALID_INPUT  "Error: invalid input"
# define PORT_OUT_RANGE "Error: port provided is out of the range"
# define MISSING_ARGS "Error: missing 2 arguments"
# define USAGE_MESS "Error: Usage: ./ircserv <port> <password>"
# define NCREATE_PORT "Error: could not create port"
# define ERROR_BIND "Error: Failed to bind socket"
# define ERROR_LISTEN "Error: Failed to listen for connections"
# define ERROR_BLOCK "Error setting socket to non-blocking mode"
# define ERROR_POLL "Error: poll() failed"


# define ERROR_PASSWORD "Error: Invalid password"
//Parsing errors
# define TOO_MANY_ARGS "Error: Too many parameters"
# define INVALID_CMD "Error: Invalid command"
# define NOT_ALLOWED "Error: forbidden function"


//Authentification messages
# define AUTH_MESS "For access, please enter the server password using the PASS command"
# define IDENT_MESS "Password verified\r\nPlease provide a username and a nickname using the USER and NICK command"
# define WELCOME_MESS "Welcome to Minou.IRC !"


//Formating for Limechat
# define PVM " PRIVMSG "


//For PASS command
# define ALREADY_IN "Error: you have already entered the password"

//For USER command
# define ALREADY_USER "Error: Username already registered"
# define NOT_ALPHA "Error: your username does not respect the character constraints"
# define USER_SUCCESS(x) "You have successfully set your username to: " + x
//For NICK Command
# define NICK_SUCCESS(x) "You have successfully set your nickname to: " + x
# define NICK_CHANGE(x) "You have successfully changed your nickname to: " + x
# define ALREADY_NICK "Error: You already have this nickname"

//For MODE command
# define INVALID_MODE "Error: invalid mode: usage: MODE <channel> {[+ | -] | i | t | k | o | l}"

//For QUIT command
# define QUIT_MESS(x, y) x + " has been disconnected from the server for: " + y
# define DEFAULT_REASON "not wanting to be here"

# define ERR_ALREADYREGISTERED "<client> :You may not reregister"
# define ERR_PASSWDMISMATCH "<client> :Password incorrect"
# define ERR_NONICKNAMEGIVEN "<client> :No nickname given"
# define ERR_ERRONEUSNICKNAME "<client> <nick> :Erroneus nickname"
# define ERR_NICKNAMEINUSE "<client> <nick> :Nickname is already in use"
# define ERR_NICKCOLLISION "<client> <nick> :Nickname collision KILL from <user>@<host>"
# define ERR_NOTONCHANNEL "<client> <channel> :You're not on that channel"
# define ERR_USERNOTINCHANNEL "<client> <nick> <channel> :They aren't on that channel"
# define ERR_NOSUCHSERVER "<client> <server name> :No such server"
# define ERR_CANNOTSENDTOCHAN "<client> <channel> :Cannot send to channel" //PRIVMSG unknown channel
# define ERR_NORECIPIENT "<client> :No recipient given (<command>)"
# define ERR_NOTEXTTOSEND "<client> :No text to send"

// for JOIN command
#define RPL_TOPIC(client, channel) client + " " + channel + " :<topic>"
#define ERR_NEEDMOREPARAMS(client, command) client + " " + command + " :Not enough parameters"
#define ERR_NOSUCHCHANNEL(client, channel) client + " " + channel + " :No such channel"
#define ERR_TOOMANYCHANNELS "<client> <channel> :You have joined too many channels"
#define ERR_BADCHANNELKEY "<client> <channel> :Cannot join channel (+k)"
#define ERR_CHANNELISFULL(client, channel) client + " " + channel + " :Cannot join channel, channel full"
#define ERR_CANNOTSENDTOCHAN "<client> <channel> :Cannot send to channel"
#define ERR_INVITEONLYCHAN "<client> <channel> :Cannot join channel, invite-only channel"
#define ERR_BADCHANMASK(channel) channel + " :Bad Channel Name"
#define ERR_CANTJOINCHAN(client, channel, reason) client + " " + channel + " :Cannot join channel " + reason

// for INVITE command
#define ERR_NOSUCHNICK(client, user) client + " " + user + " :No such nick"
#define ERR_CHANOPRIVSNEEDED(client, channel) client + " " + channel + " :Not a channel operator"
#define ERR_USERONCHANNEL(client, nick, channel) client + " " + nick + " " + channel + " :Already on channel"
#define ERR_CHANNELISFULLINV(client, channel) client + " " + channel + " :Cannot invite to channel, channel full"
#define ERR_USERNOTONCHANNEL(client, channel) client + " " + channel + " :Not on that channel"

#endif