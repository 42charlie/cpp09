#include "PmergeMe.hpp"

timeval				PmergeMe::start;
double				PmergeMe::timeVectorSort;
std::vector<int>	PmergeMe::unsortedSequence;
std::vector<int>	PmergeMe::smallerElements;
std::vector<int>	PmergeMe::largerElements;
int					PmergeMe::unpaired;
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

/**
 * @brief convert the unsortedSequence to pairs
 */
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
	// std::cout << "\n unsortedSequence : ";
	// printContainer(unsortedSequence);
	// std::cout << "\n smallerElements : ";
	// printContainer(smallerElements);
	// std::cout << "\n largerElements : ";
	// printContainer(largerElements);

}

std::vector<int> PmergeMe::fordjohnsonsort(std::vector<int> largerSequence)
{
	int _unpaired = -1;
	std::vector<int>	smaller_elements;
	std::vector<int>	larger_elements;

	//Base case
	if ( largerSequence.size() == 2 && largerSequence[0] > largerSequence[1] )
	std::swap(largerSequence[0], largerSequence[1]);
	
	if ( largerSequence.size() <= 2 ) {
		return largerSequence;
	}
 
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

	larger_elements = fordjohnsonsort(larger_elements);

	//inserting the unpair if it's exist
	insertUnpairred(_unpaired, larger_elements);

	insert(smaller_elements, larger_elements);
	return larger_elements;
}
void PmergeMe::insertUnpairred(int &_unpaired, std::vector<int> &largerSequence)
{
	if (_unpaired != -1)
	{
		std::cout << "the _unpaired number is :" << _unpaired << "\n";
		std::vector<int>::iterator position = std::lower_bound(largerSequence.begin(), largerSequence.end(), _unpaired);
		largerSequence.insert(position, _unpaired);
		_unpaired = -1;
	}
}


void PmergeMe::insert(std::vector<int> &smallerSequence, std::vector<int> &largerSequence)
{
	//inserting the smaller elements using jacob sequence
	// std::vector<int> insertionOrder = genInsertionOrder(smallerSequence.size());

	for (std::vector<int>::iterator it = smallerSequence.begin(); it != smallerSequence.end(); it++)
	{
		int element = *it;
		std::vector<int>::iterator index = std::lower_bound(largerSequence.begin(), largerSequence.end(), element);
		largerSequence.insert(index, element);
	}
}

// std::vector<int> PmergeMe::genJacobSeq(int upto)
// {
// 	std::vector<int> sequence;

// 	sequence.push_back(0);
// 	sequence.push_back(1);
//     while (sequence.back() <= upto)
// 	{
//         int next = sequence.back() + 2 * sequence[sequence.size()-2];
//         sequence.push_back(next);
//     }
// 	return sequence;
// }

// std::vector<int> PmergeMe::genInsertionOrder(int k)
// {
//     std::vector<int> order;
//     std::vector<int> jacobSeq = genJacobSeq(k);
    
//     // Start from largest Jacobsthal number ≤ k
//     int i = jacobSeq.size() - 1;
//     while (jacobSeq[i] > k) i--;
    
//     // Work backwards through gaps
//     while (i > 0) {
//         int gap = jacobSeq[i] - jacobSeq[i - 1];
//         if (gap > 0) {
//             for (int j = jacobSeq[i]; j > jacobSeq[i-1]; j--) {
//                 if (j <= k) order.push_back(j);
//             }
//         }
//         i--;
//     }
//     return order;
// }

void PmergeMe::stopChrono()
{
	struct timeval end;

	gettimeofday(&end, NULL);
	timeVectorSort = (end.tv_sec - start.tv_sec) * 1000000 + end.tv_usec - start.tv_usec;
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