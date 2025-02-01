#include "RPN.hpp"

int main(int arc, char **arg)
{
	if (arc != 2)
		return (1);
	try {
		RPN::calculate(arg[1]);
	} catch (std::exception &e)
	{
		std::cerr << e.what() << "\n";
		return (1);
	}
	return (0);
}