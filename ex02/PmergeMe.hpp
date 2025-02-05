#ifndef _PMERGE_
#define _PMERGE_

#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>
#include <cstdlib> //for strtod
#include <cstring> //for strchr

class PmergeMe{
	private :
		static std::vector<int>						unsortedSequence;
		static std::vector<std::pair<int, int> >	pairs;
		static std::vector<int>						sortedSequence;
		static double								timeVectorSort;
	public :
		static void getSequence(char **args);
		static void pairElements();
		static void show_pair()						{ for (std::vector<std::pair<int, int> >::iterator it = pairs.begin(); it != pairs.end(); it++) { std::cout << "[ " << it->first << ", " << it->second << " ]" << "\n";}; };
		static void show_seq()						{ for (std::vector<int>::iterator it = unsortedSequence.begin(); it != unsortedSequence.end(); it++) { std::cout << *it << "\n" ;}; };
};

#endif