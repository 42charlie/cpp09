#include "BitcoinExchange.hpp"
#include <algorithm>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <ctime>

std::map<long, float> BitcoinExchange::data;

time_t BitcoinExchange::gettm(std::string date)
{
	std::tm tm;
	std::string tmp;
	std::stringstream ss(date);
	std::stringstream s2f;
	// std::time_t timestamp;

	if (std::count(date.begin(), date.end(), '-') != 2)
		return (-1);
	//get year
	getline(ss, tmp, '-');
	s2f.clear();
	s2f.str(tmp);
	s2f >> tm.tm_year;
	if (tm.tm_year < 1900 || tm.tm_year > 9999)
		throw std::out_of_range("Error: Year is out of range => " + date);
	tm.tm_year -= 1900;
	//get month
	getline(ss, tmp, '-');
	s2f.clear();
	s2f.str(tmp);
	s2f >> tm.tm_mon;
	if (tm.tm_mon == 0 || tm.tm_mon > 12)
		throw std::out_of_range("Error: month is out of range => " + date);
	tm.tm_mon -= 1;
	//get day
	getline(ss, tmp);
	s2f.clear();
	s2f.str(tmp);
	s2f >> tm.tm_mday;
	if (tm.tm_mday == 0 || tm.tm_mday > 31)
		throw std::out_of_range("Error: day is out of range => " + date);

	tm.tm_hour = 0;
	tm.tm_min = 0;
	tm.tm_sec = 0;
	tm.tm_isdst = -1;
	return (std::mktime(&tm));
}

std::string BitcoinExchange::tmTodate(time_t timestamp)
{
	char date[25];
	std::tm *tm;

	tm = localtime(&timestamp);
	if (tm != NULL)
		strftime(date, sizeof(date), "%Y-%m-%d", tm);
	return (date);
}

float BitcoinExchange::getValue(std::string value)
{
	float _value;
	std::stringstream ss;

	ss.str(value);
	ss >> _value;
	return (_value);
}

float	BitcoinExchange::parseLine(std::string line, char delimiter, time_t *timestamp)
{
	float		value;

	std::stringstream ss;
	if (std::count(line.begin(), line.end(), delimiter) != 1)
		throw std::invalid_argument("Error: bad input => " + line);
	ss.str(line);
	getline(ss, line, delimiter);
	*timestamp = gettm(line);
	getline(ss, line);
	value = getValue(line);
	if (*timestamp == -1)
		throw std::invalid_argument("Error: bad input => " + line);
	return (value);
}
int BitcoinExchange::getDB(void)
{
	time_t timestamp;
	float value;
	std::string line;
	std::ifstream infile;

	infile.open("data.csv");
	if (infile.is_open() == false)
	{
		std::cout << "Error opening file.\n";
		return (-1);
	}
	getline(infile, line);
	while (infile.eof() == false)
	{
		getline(infile, line);
		if (line.empty() == true)
			continue;
		value = BitcoinExchange::parseLine(line, ',', &timestamp);
		data[timestamp] = value;
	}
	return (1);
}

std::map<time_t, float>::iterator BitcoinExchange::getbound(time_t timestamp)
{
	std::map<time_t, float>::iterator lower_bound;
	std::map<time_t, float>::iterator upper_bound;
	std::map<time_t, float>::iterator bound;

	bound = data.find(timestamp);
	if (bound != data.end())
		return (bound);
	data[timestamp] = 0;
	bound = data.find(timestamp);
	if (bound == data.begin())
		bound = ++bound;
	else if (bound == --data.end())
		bound = --bound;
	else
	{
		lower_bound = --bound;
		upper_bound = ++(++bound);
		if (timestamp - lower_bound->first < upper_bound->first - timestamp)
			bound = lower_bound;
		else
			bound = upper_bound;
	}
	data.erase(timestamp);
	return (bound);
}


int BitcoinExchange::Exchange(const char *infilename)
{
	std::map<time_t, float>::iterator bound;
	float			value;
	std::string		line;
	std::ifstream	infile;
	time_t			timestamp;

	infile.open(infilename);
	if (infile.is_open() == false)
	{
		std::cout << "Error: could not open file.\n";
		return (1);
	}
	getline(infile, line);
	while (infile.eof() == false)
	{
		getline(infile, line);
		if (line.empty() == true)
			continue;
		try{
			value = BitcoinExchange::parseLine(line, '|', &timestamp);
		}
		catch (std::exception &e)
		{
			std::cout << e.what() << "\n";
			continue;
		}
		try{
			if (value < 0)
				throw std::out_of_range("Error: not a positive number.");
			if (value > 1000)
				throw std::out_of_range("Error: too large a number.");
		}
		catch (std::exception &e)
		{
			std::cout << e.what() << "\n";
			continue;
		}
		bound = getbound(timestamp);
		std::cout << tmTodate(timestamp) << " => " << value << " = " << bound->second * value << "\n";
	}
	return (0);
}
