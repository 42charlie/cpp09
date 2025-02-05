#ifndef _PMERGE_
#define _PMERGE_

#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>
#include <cstdlib> //for strtod
#include <cstring> //for strchr
#include <sys/time.h> // for gettimeofday

class PmergeMe{
	private :
		static std::vector<int>						unsortedSequence;
		static std::vector<std::pair<int, int> >	pairs;
		static std::vector<int>						sortedSequence;
		static double								timeVectorSort;
		static double								timeDequeSort;
		static timeval								start;
	public :
		static void getSequence(char **args);
		static void pairElements();
		static void createAndInsertMainChain();
		static void binaryInsertion(int number);
		static void showStats();
		static void printContainer(std::vector<int>::iterator begin, std::vector<int>::iterator end);

		static void show_pair()						{ for (std::vector<std::pair<int, int> >::iterator it = pairs.begin(); it != pairs.end(); it++) { std::cout << "[ " << it->first << ", " << it->second << " ]" << "\n";}; };
};

#endif