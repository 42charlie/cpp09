#include "PmergeMe.hpp"
#include <iostream>
#include <cstdlib>

int main(int argc, char **argv) {
    double vectorSortTime;
    double dequeSortTime;

    if (argc < 2) {
        std::cerr << "Error: Please provide a sequence of positive integers\n";
        return 1;
    }

    try {
        //deque
        dequeSortTime = PmergeMe<std::deque<int> >::mergeSort(argv);
        //vector
        vectorSortTime = PmergeMe<std::vector<int> >::mergeSort(argv);
        PmergeMe<std::deque<int> >::showStats(vectorSortTime, dequeSortTime);
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << "\n";
        return 1;
    }

    return 0;
}