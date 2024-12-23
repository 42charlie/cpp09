#include <iostream>
#include "BitcoinExchange.hpp"

int main(int arc, char **arg)
{
	BitcoinExchange::getDB();
	if (arc > 1)
		BitcoinExchange::Exchange(arg[1]);
	// BitcoinExchange::showMap();
}