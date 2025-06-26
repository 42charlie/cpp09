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
		static timeval								start;
		static double								timeVectorSort;
		static std::vector<int>						unsortedSequence;
	public :
		static int									unpaired;
		static std::vector<int>						largerElements;
		static std::vector<int>						smallerElements;
		static void				getSequence(char **args);
		static void 			pairElements();
		static std::vector<int>	fordjohnsonsort(std::vector<int> unsorted);
		static std::vector<int> genJacobSeq(int n);
		static void				insertSequence(std::vector<int> &smallerSequence, std::vector<int> &largerSequence);
		static void 			insertUnpaired(int &unpaired, std::vector<int> &largerSequence);
		static void				stopChrono();
		static void				showStats();
		static void				printContainer(std::vector<int> v);
};

#endif