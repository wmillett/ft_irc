#pragma once
#include "utils.h"

class CustomException
{
	public:

		class InvalidInputException: public std::exception
		{
			public:
				virtual const char* what() const throw() { return (INVALID_INPUT); };
		};

		class OutOfRangeException: public std::exception
		{
			public:
				virtual const char* what() const throw() { return (PORT_OUT_RANGE); };
		};

		class CouldNotCreatePort: public std::exception
		{
			public:
				virtual const char* what() const throw() { return (NCREATE_PORT); };
		};

		class ErrorBind: public std::exception
		{
			public:
				virtual const char* what() const throw() { return (ERROR_BIND); };
		};

		class ErrorListen: public std::exception
		{
			public:
				virtual const char* what() const throw() { return (ERROR_BIND); };
		};

		class ErrorFcntl: public std::exception
		{
			public:
				virtual const char* what() const throw() { return (ERROR_BLOCK); };
		};

		class PollFailed: public std::exception
		{
			public:
				virtual const char* what() const throw() { return (""); };
		};
		class TooManyArgs: public std::exception
		{
			public:
				virtual const char* what() const throw() { return (TOO_MANY_ARGS); }
		};
};