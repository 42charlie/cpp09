template <typename T>
clock_t	PmergeMe<T>::start;

template <typename T>
T		PmergeMe<T>::unsortedSequence;

template <typename T>
T		PmergeMe<T>::smallerElements;

template <typename T>
T		PmergeMe<T>::largerElements;

template <typename T>
int		PmergeMe<T>::unpaired;

template <typename T>
T PmergeMe<T>::fordjohnsonsort(T largerSequence)
{
	T		larger_elements;
	T		smaller_elements;
	int		_unpaired = -1;
	size_t	largerSeqLen = largerSequence.size();
	
	//Base case.
	if ( largerSeqLen == 2 && largerSequence[0] > largerSequence[1] )
		std::swap(largerSequence[0], largerSequence[1]);

	if ( largerSeqLen <= 2 )
		return largerSequence;
	
	//split larger and smaller elements.
	for ( unsigned int i = 0; i < largerSeqLen; i+=2 )
	{
		if ( i + 1 >= largerSeqLen ) {
			_unpaired = largerSequence[i];
			break;
		}
		smaller_elements.push_back(std::min(largerSequence[i], largerSequence[i + 1]));
		larger_elements.push_back(std::max(largerSequence[i], largerSequence[i + 1]));
	}
	
	//recursively call the func on larger elements.
	larger_elements = fordjohnsonsort(larger_elements);
	
	//inserting the smaller elements and the unpaired element.
	if (_unpaired != -1)
		insertUnpaired(_unpaired, larger_elements);
	insertSequence(smaller_elements, larger_elements);
	return larger_elements;
}

template <typename T>
void PmergeMe<T>::insertUnpaired(int &_unpaired, T &largerSequence)
{
	typename T::iterator	position;
	
	position = std::lower_bound(largerSequence.begin(), largerSequence.end(), _unpaired);
	largerSequence.insert(position, _unpaired);
	_unpaired = -1;
}

template <typename T>
void PmergeMe<T>::insertSequence(T &smallerSequence, T &largerSequence)
{
	int						element;
	typename T::iterator	position;
	T						jacob = genJacobSeq(smallerSequence.size());
	T						inserted(smallerSequence.size(), 0);
	
	// Insert Jacobsthal-indexed elements
	for (typename T::iterator it = jacob.begin(); it != jacob.end(); ++it)
	{
		if (*it >= (int)smallerSequence.size())
			continue;
		element = smallerSequence[*it];
		position = std::lower_bound(largerSequence.begin(), largerSequence.end(), element);
		largerSequence.insert(position, element);
		inserted[*it] = 1;
	}

	// Insert remaining elements
	for (size_t i = 0; i < smallerSequence.size(); ++i)
	{
		if (inserted[i])
			continue;
		element = smallerSequence[i];
		position = std::lower_bound(largerSequence.begin(), largerSequence.end(), element);
		largerSequence.insert(position, element);
	}
}

template <typename T>
T PmergeMe<T>::genJacobSeq(int n)
{
	int	next;
	T	sequence;
    int	j0 = 0;
    int	j1 = 1;

    if (n <= 0)
		return sequence;
    sequence.push_back(j1);
    while (true) {
		next = j1 + 2 * j0; //j(n) = j(n - 1) + 2 * j(n - 2)
        if (next >= n)
			break;
		if( std::find(sequence.begin(), sequence.end(), next) == sequence.end())
			sequence.push_back(next);
        j0 = j1;
        j1 = next;
    }
    return sequence;
}

template <typename T>
void PmergeMe<T>::printContainer(T v)
{
	typename T::iterator begin = v.begin();
	typename T::iterator end = v.end();
	
	while (begin != end)
	{
		std::cout << *begin << " ";
		begin++;
	}
}

template <typename T>
double PmergeMe<T>::mergeSort(char **argv)
{
	double sortTime;

	start = clock();
	PmergeMe<T>::getSequence(argv);
    PmergeMe<T>::pairElements();
    PmergeMe<T>::largerElements = PmergeMe<T>::fordjohnsonsort(PmergeMe<T>::largerElements);
    PmergeMe<T>::insertUnpaired(PmergeMe<T>::unpaired, PmergeMe<T>::largerElements);
    PmergeMe<T>::insertSequence(PmergeMe<T>::smallerElements, PmergeMe<T>::largerElements);
    sortTime = PmergeMe<T>::stopChrono();
	return sortTime;
}

template <typename T>
void PmergeMe<T>::getSequence(char **args)
{
	int		number;
	char	*delimiter;
	
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

template <typename T>
void PmergeMe<T>::pairElements()
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

template <typename T>
double PmergeMe<T>::stopChrono()
{
	double	tmp;
	clock_t end;
	
	end = clock();
	tmp = static_cast<double>(end - start) * 1000000 / CLOCKS_PER_SEC ;
	return  tmp;
}

template <typename T>
void PmergeMe<T>::showStats(double timeVectorSort, double timeDequeSort)
{
	std::cout << "before:\t";
	printContainer(unsortedSequence);
	std::cout << "\n";
	std::cout << "after:\t";
	printContainer(largerElements);
	std::cout << "\n";
	std::cout << "Time to process a range of " << unsortedSequence.size() << " elements with std::vector : " << timeVectorSort << " us\n";
	std::cout << "Time to process a range of " << unsortedSequence.size() << " elements with std::deque : " << timeDequeSort << " us\n";
}