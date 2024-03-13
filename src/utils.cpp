#include "../inc/Command.hpp"
#include "Server.hpp"

void Server::buildStrings(string arg, char delimiter, std::vector<string> vec)
{
	size_t last = 0, next = 0;
	string str;
	std::vector<string> rtn;
	while ((next = arg.find(delimiter, last)) != std::string::npos)
	{
		str = arg.substr(last, next - last);
		rtn.push_back(str);
		last = next + 1;
	}
	str = arg.substr(last);
	rtn.push_back(str);

	rtn.swap(vec);
}

void errorMessage(int errnum)
{
	
}


// std::list<string> initStringList(string content[]){
//     for(int i = 0; i < )


// }

