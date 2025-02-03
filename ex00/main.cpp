#include <iostream>
#include "BitcoinExchange.hpp"

int main(int arc, char **arg)
{
	try {
		if (arc < 2)
			throw std::invalid_argument("Error: invalid argument");
		BitcoinExchange::getDB();
		BitcoinExchange::Exchange(arg[1]);
	} catch (std::exception & e)
	{
		std::cout << e.what() << "\n";
		return (1);
	}
	return (0);
	// BitcoinExchange::showMap();
}