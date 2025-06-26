#include "PmergeMe.hpp"
#include <iostream>
#include <cstdlib>

int main(int argc, char **argv) {
    if (argc < 2) {
        std::cerr << "Error: Please provide a sequence of positive integers\n";
        return 1;
    }

    try {
        PmergeMe::getSequence(argv);
        PmergeMe::pairElements();
        PmergeMe::largerElements = PmergeMe::fordjohnsonsort(PmergeMe::largerElements);
        PmergeMe::insertUnpaired(PmergeMe::unpaired, PmergeMe::largerElements);
        PmergeMe::insertSequence(PmergeMe::smallerElements, PmergeMe::largerElements);
        PmergeMe::stopChrono();
        PmergeMe::showStats();
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << "\n";
        return 1;
    }

    return 0;
}