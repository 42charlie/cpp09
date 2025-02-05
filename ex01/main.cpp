#include "RPN.hpp"

int main(int arc, char **arg)
{
	if (arc != 2)
		return std::cerr << "Error: Invalid number of arguments. Expected 1 argument" << "\n", 1;
	try {
		std::cout << RPN::processRPNLine(arg[1]);
		std::cout << "\n";
	} catch (std::exception &e)
	{
		std::cerr << e.what() << "\n";
		return (1);
	}
	return (0);
}