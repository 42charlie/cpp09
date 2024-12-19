#include "BitcoinExchange.hpp"
#include <algorithm>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <ctime>

int BitcoinExchange::gettm(std::string date)
{
	std::tm tm;
	std::string tmp;
	std::stringstream ss(date);
	std::stringstream s2f;

	if (std::count(date.begin(), date.end(), '-') != 2)
		return (-1);
	getline(ss, tmp, '-');
	s2f.str(tmp);
	s2f >> tm.tm_year;
	std::cout << tm.tm_year;
	return (1);
}
int BitcoinExchange::getDB(void)
{
	int ln = 0;
	int key;
	int value;
	std::string line;
	std::stringstream ss;
	const char *filename = "data.csv";
	std::ifstream infile;

	infile.open(filename);
	if (infile.is_open() == false)
	{
		std::cout << "Error opening file.\n";
		return (-1);
	}
	while (infile.eof() == false)
	{
		getline(infile, line);
		if (line.empty() == true)
			
		if (line.find(',') != line.rfind(','))
			return (-1);
		ss.str(line);
		getline(ss, line, ',');
		key = getdate(line);
		getline(ss, line);
		value = getvalue(line);
		if (key == -1 || value == -1)
			return (-1);
		data[key] = value;
		ln++;
	}
	return (ln);
}