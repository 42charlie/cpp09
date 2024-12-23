#include <iostream>
#include "BitcoinExchange.hpp"

int main(int arc, char **arg)
{
	BitcoinExchange::getDB();
	if (arc < 2)
		std::cout << "Error: could not open file.\n";
	else
		return (BitcoinExchange::Exchange(arg[1]));
	return (1);
	// BitcoinExchange::showMap();
}