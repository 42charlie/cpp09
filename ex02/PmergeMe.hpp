#ifndef _PMERGE_
#define _PMERGE_

#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>
#include <utility>
#include <cstdlib> //for strtod
#include <cstring> //for strchr
#include <ctime> //for clock

template <typename T>
class PmergeMe{
	private :
		static clock_t	start;
		static T		unsortedSequence;
	public :
		static int		unpaired;
		static T		largerElements;
		static T		smallerElements;
		static double	mergeSort(char **argv);
		static void		getSequence(char **args);
		static void		pairElements();
		static T		fordjohnsonsort(T unsorted);
		static T		genJacobSeq(int n);
		static void		insertSequence(T &smallerSequence, T &largerSequence);
		static void		insertUnpaired(int &unpaired, T &largerSequence);
		static double	stopChrono();
		static void		showStats(double timeVectorSort, double timeDequeSort);
		static void		printContainer(T v);
};

#include "PmergeMe.tpp"

#endif