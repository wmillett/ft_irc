#ifndef SIGHANDLER_HPP
# define SIGHANDLER_HPP

# include <csignal>
# include "utils.h"


class SignalHandler {
	public:
    	SignalHandler();
    	static void handleSignal(int signal);
	};

#endif
