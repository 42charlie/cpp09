#include "PmergeMe.hpp"

std::vector<int> PmergeMe::unsortedSequence;
std::vector<std::pair<int, int> > PmergeMe::pairs;

/**
 * @brief Get the int sequence from the args and store it in PmergeMe::unsortedSequence
 * @param args(char**) arguments list passed to program
 * @return None, it set the unsortedSequence vector instead.
 */
void PmergeMe::getSequence(char **args)
{
	int		number;
	char	*delimiter;

	if ( *(++args) == NULL || **args == '\0' )
		throw std::invalid_argument("Error : Invalid argument !");

	for ( int i = 0; args[i] != NULL; i++ )
	{
		number = std::strtod(args[i], &delimiter);
		if ( *delimiter != '\0' || number < 0 || std::strchr(args[i], '.') != NULL )
			throw std::invalid_argument("Error : Invalid argument !");
		unsortedSequence.push_back(number);
	}
}

/**
 * @brief convert the unsortedSequence to pairs
 */
void PmergeMe::pairElements()
{
	std::pair<int, int>	tmpPair;

	for ( unsigned int i = 0; i < unsortedSequence.size(); i+=2 )
	{
		tmpPair.first = unsortedSequence[i];
		if ( i + 1 < unsortedSequence.size())
			tmpPair.second = unsortedSequence[i + 1];
		else
			tmpPair.second = -1;
		pairs.push_back(tmpPair);
	}
}