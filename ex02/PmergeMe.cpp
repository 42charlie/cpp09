#include "PmergeMe.hpp"

timeval				PmergeMe::start;
double				PmergeMe::timeVectorSort;
std::vector<int>	PmergeMe::unsortedSequence;
std::vector<int>	PmergeMe::smallerElements;
std::vector<int>	PmergeMe::largerElements;
int					PmergeMe::unpaired;

void PmergeMe::getSequence(char **args)
{

	int		number;
	char	*delimiter;

	gettimeofday(&start, NULL);
	if ( *(++args) == NULL )
		throw std::invalid_argument("Error : Invalid argument !");

	for ( int i = 0; args[i] != NULL; i++ )
	{
		number = std::strtod(args[i], &delimiter);
		if ( args[i][0] == '\0' || *delimiter != '\0' || number < 0 || std::strchr(args[i], '.') != NULL )
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

void PmergeMe::pairElements()
{
	std::pair<int, int>	Pair;
	
	unpaired = -1;
	for ( unsigned int i = 0; i < unsortedSequence.size(); i+=2 )
	{
		if (i + 1 >= unsortedSequence.size()) {
			unpaired = unsortedSequence[i];
			return ;
		}
		Pair.first = unsortedSequence[i];
		Pair.second = unsortedSequence[i + 1];
		if ( Pair.first > Pair.second )
			std::swap(Pair.first, Pair.second);

		smallerElements.push_back(Pair.first);
		largerElements.push_back(Pair.second);
	}

}

std::vector<int> PmergeMe::fordjohnsonsort(std::vector<int> largerSequence)
{
	int					_unpaired = -1;
	std::vector<int>	smaller_elements;
	std::vector<int>	larger_elements;

	//Base case.
	if ( largerSequence.size() == 2 && largerSequence[0] > largerSequence[1] )
		std::swap(largerSequence[0], largerSequence[1]);
	if ( largerSequence.size() <= 2 )
		return largerSequence;
	
	//split larger and smaller elements.
	for ( unsigned int i = 0; i < largerSequence.size(); i+=2 )
	{
		if ( i + 1 >= largerSequence.size() ) {
			_unpaired = largerSequence[i];
			break;
		}
		smaller_elements.push_back(std::min(largerSequence[i], largerSequence[i + 1]));
		larger_elements.push_back(std::max(largerSequence[i], largerSequence[i + 1]));
	}
	
	//recursively call the func on larger elements.
	larger_elements = fordjohnsonsort(larger_elements);
	
	//inserting the smaller elements and the unpaired element.
	insertUnpaired(_unpaired, larger_elements);
	insertSequence(smaller_elements, larger_elements);
	return larger_elements;
}

void PmergeMe::insertUnpaired(int &_unpaired, std::vector<int> &largerSequence)
{
	if (_unpaired != -1)
	{
		std::vector<int>::iterator position = std::lower_bound(largerSequence.begin(), largerSequence.end(), _unpaired);
		largerSequence.insert(position, _unpaired);
		_unpaired = -1;
	}
}


void PmergeMe::insertSequence(std::vector<int> &smallerSequence, std::vector<int> &largerSequence)
{
	std::vector<int> jacob = genJacobSeq(smallerSequence.size());
	std::vector<bool> inserted(smallerSequence.size(), false);

	// Insert Jacobsthal-indexed elements
	for (std::vector<int>::iterator it = jacob.begin(); it != jacob.end(); ++it)
	{
		int index = *it;
		if (index >= (int)smallerSequence.size())
			continue;
		int element = smallerSequence[index];
		std::vector<int>::iterator pos = std::lower_bound(largerSequence.begin(), largerSequence.end(), element);
		largerSequence.insert(pos, element);
		inserted[index] = true;
	}

	// Insert remaining elements
	for (size_t i = 0; i < smallerSequence.size(); ++i)
	{
		if (inserted[i])
			continue;
		int element = smallerSequence[i];
		std::vector<int>::iterator pos = std::lower_bound(largerSequence.begin(), largerSequence.end(), element);
		largerSequence.insert(pos, element);
	}
}



std::vector<int> PmergeMe::genJacobSeq(int n)
{
    std::vector<int> sequence;
    int j0 = 0;
    int j1 = 1;
    if (n <= 0)
        return sequence;
    sequence.push_back(j1);
    while (true) {
        int next = j1 + 2 * j0;
        if (next >= n)
            break;
		if( std::find(sequence.begin(), sequence.end(), next) == sequence.end())
        	sequence.push_back(next);
        j0 = j1;
        j1 = next;
    }
    return sequence;
}

void PmergeMe::stopChrono()
{
	struct timeval end;

	gettimeofday(&end, NULL);
	timeVectorSort = (end.tv_sec - start.tv_sec) * 1000000.0 + end.tv_usec - start.tv_usec;
}

void PmergeMe::printContainer(std::vector<int> v)
{
	std::vector<int>::iterator begin = v.begin();
	std::vector<int>::iterator end = v.end();

	while (begin != end)
	{
		std::cout << *begin << " ";
		begin++;
	}
}

void PmergeMe::showStats()
{
	std::cout << "\n";
	std::cout << "before:\t";
	printContainer(unsortedSequence);
	std::cout << "\n";
	std::cout << "after:\t";
	printContainer(largerElements);
	std::cout << "\n";
	std::cout << "Time to process a range of " << unsortedSequence.size() << " elements with std::vector : " << timeVectorSort << " us\n";
	std::cout << "Time to process a range of " << unsortedSequence.size() << " elements with std::vector : " << timeVectorSort << " us\n";
}