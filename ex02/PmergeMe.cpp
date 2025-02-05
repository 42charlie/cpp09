#include "PmergeMe.hpp"

double PmergeMe::timeVectorSort;
timeval PmergeMe::start;
std::vector<int> PmergeMe::unsortedSequence;
std::vector<int> PmergeMe::sortedSequence;
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

	gettimeofday(&start, NULL);
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

bool compPairs(const std::pair<int, int> &firstPair, const std::pair<int, int> &secondPair)
{
	if ( firstPair.second < secondPair.second )
		return true;
	return false;
}

/**
 * @brief convert the unsortedSequence to pairs
 */
void PmergeMe::pairElements()
{
	int					tmpSecond;
	std::pair<int, int>	tmpPair;

	for ( unsigned int i = 0; i < unsortedSequence.size(); i+=2 )
	{
		if ( i + 1 < unsortedSequence.size() )
			tmpSecond = unsortedSequence[i + 1];
		else
			tmpSecond = -1;
		tmpPair.first = std::min(unsortedSequence[i], tmpSecond);
		tmpPair.second = std::max(unsortedSequence[i], tmpSecond);
		pairs.push_back(tmpPair);
	}
	std::sort(pairs.begin(), pairs.end(), compPairs);
}

/**
 * @brief create the main chain "sortedSequence" and insert the samller elements
 */
void PmergeMe::createAndInsertMainChain()
{
	timeval	end;

	for ( std::vector<std::pair<int, int> >::iterator it = pairs.begin(); it != pairs.end(); it++ )
	{
		sortedSequence.push_back(it->second);
	}

	for ( std::vector<std::pair<int, int> >::iterator it = pairs.begin(); it != pairs.end(); it++ )
	{
		if ( it->first == -1 )
			continue ;
		binaryInsertion(it->first);
	}
	gettimeofday(&end, NULL);
	timeVectorSort = end.tv_usec - start.tv_usec;
}

/**
 * @brief insert a number in a sorted container using binary insertion
 * @param number number to insert
 */
void PmergeMe::binaryInsertion(int number)
{
	unsigned int left = 0;
	unsigned int right = sortedSequence.size();
	unsigned int mid;

	while ( left < right )
	{
		mid = left + (right - left) / 2;
		if ( sortedSequence[mid] < number )
			left++;
		else if ( sortedSequence[mid] > number )
			right--;
		else
			break;
	}
	sortedSequence.insert(sortedSequence.begin() + left, number);
}

void PmergeMe::printContainer(std::vector<int>::iterator begin, std::vector<int>::iterator end)
{
	while (begin != end)
	{
		std::cout << *begin << " ";
		begin++;
	}
}

void PmergeMe::showStats()
{
	std::cout << "before:\t";
	printContainer(unsortedSequence.begin(), unsortedSequence.end());
	std::cout << "\n";
	std::cout << "after:\t";
	printContainer(sortedSequence.begin(), sortedSequence.end());
	std::cout << "\n";
	std::cout << "Time to process a range of " << unsortedSequence.size() << " elements with std::vector : " << timeVectorSort << " us\n";
	std::cout << "Time to process a range of " << unsortedSequence.size() << " elements with std::vector : " << timeVectorSort << " us\n";
}