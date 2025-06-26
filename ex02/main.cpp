#include "PmergeMe.hpp"
#include <iostream>
#include <cstdlib>

int main(int argc, char **argv) {
    if (argc < 2) {
        std::cerr << "Error: Please provide a sequence of positive integers\n";
        return 1;
    }

    try {
        // Step 1: Parse input
        PmergeMe::getSequence(argv);

        // Step 2: Sort and time the sequence
        PmergeMe::pairElements();
        PmergeMe::largerElements = PmergeMe::fordjohnsonsort(PmergeMe::largerElements);
        PmergeMe::insertUnpairred(PmergeMe::unpaired, PmergeMe::largerElements);
        PmergeMe::insert(PmergeMe::smallerElements, PmergeMe::largerElements);
        PmergeMe::stopChrono();

        // Step 3: Display results
        PmergeMe::showStats();
    } 
    catch (const std::exception& e) {
        std::cerr << e.what() << "\n";
        return 1;
    }

    return 0;
}