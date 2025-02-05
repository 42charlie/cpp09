#ifndef _PMERGE_
#define _PMERGE_

#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdlib> //for strtod
#include <cstring> //for strchr

class PmergeMe{
	private :
		static std::vector<int>		unsortedSequence;
		static double				timeVectorSort;
		static double				timelistSort;
	public :
		static void getSequence(char **args);
		static void show_seq() { for (std::vector<int>::iterator it = unsortedSequence.begin(); it != unsortedSequence.end(); it++) { std::cout << *it << "\n" ;}; };
};

#endif