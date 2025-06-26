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
		static std::vector<int>						sortedSequence;
		static std::vector<std::pair<int, int> >	pairs;
		static double								timeVectorSort;
		static timeval								start;
	public :
		static int									unpaired;
		static std::vector<int>						largerElements;
		static std::vector<int>						smallerElements;
		static void				getSequence(char **args);
		static void 			pairElements();
		static std::vector<int>	fordjohnsonsort(std::vector<int> unsorted);
		static std::vector<int> genJacobSeq(int n);
		// static std::vector<int>	genJacobSeq(int upto);
		// static std::vector<int>	genInsertionOrder(int k);
		static void				insertSequence(std::vector<int> &smallerSequence, std::vector<int> &largerSequence);
		static void 			insertUnpaired(int &unpaired, std::vector<int> &largerSequence);
		// static std::vector<int> getLargerelements() { return largerElements; }
		// static std::vector<int> getSmallerelements() { return smallerElements; }
		// static std::vector<int> getUnsortedSequence() { return unsortedSequence; }
		static void				stopChrono();
		static void				showStats();
		static void				printContainer(std::vector<int> v);

		static void				show_pair()						{ for (std::vector<std::pair<int, int> >::iterator it = pairs.begin(); it != pairs.end(); it++) { std::cout << "[ " << it->first << ", " << it->second << " ]" << "\n";}; };
};

#endif