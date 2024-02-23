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
};