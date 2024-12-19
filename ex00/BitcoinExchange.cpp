#include "BitcoinExchange.hpp"
#include <algorithm>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <ctime>

time_t BitcoinExchange::gettm(std::string date)
{
	std::tm tm;
	std::string tmp;
	std::stringstream ss(date);
	std::stringstream s2f;
	std::time_t timestamp;

	if (std::count(date.begin(), date.end(), '-') != 2)
		return (-1);

	getline(ss, tmp, '-');
	s2f.clear();
	s2f.str(tmp);
	s2f >> tm.tm_year;

	getline(ss, tmp, '-');
	s2f.clear();
	s2f.str(tmp);
	s2f >> tm.tm_mon;
	// tm.tm_mon+=1;

	getline(ss, tmp);
	s2f.clear();
	s2f.str(tmp);
	s2f >> tm.tm_mday;

	timestamp = std::mktime(&tm);
	return (timestamp);
}
int BitcoinExchange::getDB(void)
{
	int ln = 0;
	time_t key;
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
	getline(infile, line);
	while (infile.eof() == false)
	{
		ss.clear();
		getline(infile, line);
		if (line.empty() == true)
			continue;
		if (std::count(line.begin(), line.end(), ',') != 1)
			return (-1);
		ss.str(line);
		getline(ss, line, ',');
		key = gettm(line);
		std::cout << "key is :" << key << "\n";
		getline(ss, line);
		// value = getvalue(line);
		key = 0;
		value = 0;
		if (key == -1 || value == -1)
			return (-1);
		// data[key] = value;
		ln++;
		if (ln == 2)
			exit(1);
	}
	return (ln);
}