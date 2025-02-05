#include "PmergeMe.hpp"

int main(int arc, char **args)
{
	(void) arc;
	try {
		PmergeMe::getSequence(args);
		PmergeMe::pairElements();
		PmergeMe::createAndInsertMainChain();
		PmergeMe::showStats();
	} catch (std::exception & e)
	{
		std::cerr << e.what() << "\n";
		return 1;
	}
	return (0);
}