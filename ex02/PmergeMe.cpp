#include "PmergeMe.hpp"

std::vector<int> PmergeMe::unsortedSequence;

/**
 * @brief Get the int sequence from the args and store it in PmergeMe::unsortedSequence
 * @param args(char**) arguments list passed to program
 * @return None, it set the unsortedSequence vector instead.
 */
void PmergeMe::getSequence(char **args)
{
	int		number;
	char	*delimiter;

	if ( *(++args) == NULL || **args == '\0')
		throw std::invalid_argument("Error : Invalid argument !");

	for ( int i = 0; args[i] != NULL; i++ )
	{
		number = std::strtod(args[i], &delimiter);
		if ( *delimiter != '\0' || number < 0 || std::string(args[i]).find('.') != std::string::npos)
			throw std::invalid_argument("Error : Invalid argument !");
		unsortedSequence.push_back(number);
	}
}