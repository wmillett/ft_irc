#ifndef _ERRORMESSAGE_H_
# define _ERRORMESSAGE_H_

// Replies 001-004
# define RPL_WELCOME "<client> :Welcome to the <networkname> Network, <nick>[!<user>@<host>]"
# define RPL_YOURHOST "<client> :Your host is <servername>, running version <version>"
# define RPL_CREATED "<client> :This server was created <datetime>"
# define RPL_MYINFO "<client> <servername> <version> <available user modes> <available channel modes> [<channel modes with a parameter>]"
# define RPL_INVITING(sender, nick, channel) sender + " " + nick + " " + channel
# define RPL_LEFTCHANNEL(user, channel) user + " has left " + channel
# define RPL_JOINCHANNEL(user, channel) user + " has joined " + channel
# define RPL_TOPIC(client, channel, topic) client + " " + channel + " : " + topic
# define RPL_NEWTOPIC(client, channel, topic) client + " " + channel + " : Topic has been changed to " + topic
# define RPL_KICK(client, channel, reason) client + " " + channel + " : You have been kicked from channel for" + reason
# define RPL_CREATECHANNEL(user, channel) user + " " + channel + ": channel has been created"

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
# define ALREADY_NICK "Error: Nickname exists already!!!!"

//For MODE command
# define INVALID_MODE "Error: invalid mode: usage: MODE <channel> [{[+ | -] | i | t | k | o | l} [<mode arguments>...]]"
//# define INVALID_MODE "Error: invalid mode: usage: MODE <channel> {[+ | -] | i | t | k | o | l}"
# define NO_CHANNEL "Error: channel does not exist"
# define ERR_UMODEUNKNOWNFLAG(client) client + " :Unknown MODE flag"//official message
# define ERR_UNKNOWNMODE(client, modechar) client + modechar + " :is unknown mode char to me"//official message
//For MODE, successful option commands executed (broadcast)
# define ADD_INVITE(client) (std::string(client) + " has set the channel to invite only")
# define RM_INVITE(client) (std::string(client) + " has removed the invite only requirement for this channel")
# define ADD_TOPIC(client) (std::string(client) + " has restricted the topic to channel operators")
# define RM_TOPIC(client) (std::string(client) + " has disabled the restriction on the channel topic")
# define ADD_OP(client, target) (std::string(target) + " has been promoted to channel operator by " + std::string(client))
# define RM_OP(client, target) (std::string(client) + " has removed channel operator privileges for: " + std::string(target))
# define ADD_UL(client, limit) (std::string(client) + " has set the channel user limit to " + (std::string(limit)))
# define RM_UL(client) (std::string(client) + " has removed the channel user limit")

# define MISSING_ORIENTATION(client, modechar) client + modechar + " :Missing orientation for modechar"
# define MISSING_ARGUMENT(client, modechar) client + modechar + " :Missing argument for modechar"

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
# define ERR_TOPICTOOLONG(client) client + " :Topic too long"

// for JOIN command
#define ERR_NEEDMOREPARAMS(client, command) client + " " + command + " :Not enough parameters"
#define ERR_NOSUCHCHANNEL(client, channel) client + " " + channel + " :No such channel"
#define ERR_TOOMANYCHANNELS(client) client+ " :Channel limit reached"
#define ERR_BADCHANNELKEY "<client> <channel> :Cannot join channel (+k)"
#define ERR_CHANNELISFULL(client, channel) client + " " + channel + " :Cannot join channel, channel full"
#define ERR_CANNOTSENDTOCHAN "<client> <channel> :Cannot send to channel"
#define ERR_INVITEONLYCHAN "<client> <channel> :Cannot join channel, invite-only channel"
#define ERR_BADCHANMASK(channel) " :Bad Channel Name: " + channel
#define ERR_CANTJOINCHAN(client, channel) client + " " + channel + " : Cannot join channel"

// for INVITE command
#define ERR_NOSUCHNICK(client, user) client + " " + user + " :No such nick"
#define ERR_CHANOPRIVSNEEDED(client, channel) client + " " + channel + " :Not a channel operator"
#define ERR_USERONCHANNEL(client, nick, channel) client + " " + nick + " " + channel + " :Already on channel"
#define ERR_CHANNELISFULLINV(client, channel) client + " " + channel + " :Cannot invite to channel, channel full"
#define ERR_USERNOTONCHANNEL(client, channel) client + " " + channel + " :Not on that channel"

#endif