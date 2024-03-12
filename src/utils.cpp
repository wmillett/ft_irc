#include "../inc/Command.hpp"
#include "Server.hpp"

std::vector<string> Server::buildStrings(string arg, char delimiter, std::vector<string> vec)
{
	size_t last = 0, next = 0;
	string str;
	while ((next = arg.find(delimiter, last)) != std::string::npos)
	{
		str = arg.substr(last, next - last);
		vec.push_back(str);
		last = next + 1;
	}
	str = arg.substr(last);
	vec.push_back(str);

	std::vector<string> rtn;
	rtn.swap(vec);
	return (rtn);
}

void errorMessage(int errnum)
{
	
}


// std::list<string> initStringList(string content[]){
//     for(int i = 0; i < )


// }

