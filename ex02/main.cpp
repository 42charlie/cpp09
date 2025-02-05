#include "PmergeMe.hpp"

int main(int arc, char **args)
{
	(void) arc;
	try {
		PmergeMe::getSequence(args);
		PmergeMe::show_seq();
	} catch (std::exception & e)
	{
		std::cerr << e.what() << "\n";
		return 1;
	}
		return (0);
}