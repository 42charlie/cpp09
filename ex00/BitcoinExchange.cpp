#include "BitcoinExchange.hpp"

std::map<DateKey, float> BitcoinExchange::data;

DateKey BitcoinExchange::getDateKey(std::string dateLine)
{
	struct tm tm;

	if (!strptime(dateLine.c_str(), "%Y-%m-%d", &tm))
		throw std::invalid_argument("Error: bad input => " + dateLine);

	return DateKey(tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, dateLine);
}

float BitcoinExchange::getValue(std::string valueLine)
{
	std::stringstream	ss;
	float				value;

	ss.str(valueLine);
	ss >> value;
	return (value);
}

float	BitcoinExchange::parseLine(std::string line, char delimiter, DateKey *date)
{
	std::stringstream	ss;
	float				value;

	//throw exception if there is more or less that one delimiter in the line.
	if (std::count(line.begin(), line.end(), delimiter) != 1)
		throw std::invalid_argument("Error: bad input => " + line);

	//get the timestamp(set) : value(return) pair from database or input file.
	ss.str(line);
	getline(ss, line, delimiter);
	*date = getDateKey(line);
	getline(ss, line);
	value = getValue(line);

	//throw exception if there is any errors.
	if ( delimiter == '|' )
	{
		if ( date->getIsValidYear() == false )
			throw std::invalid_argument("Error: bad input => " + date->getFullDate());
		if ( value < 0 )
			throw std::out_of_range("Error: not a positive number.");
		if ( value > 1000 )
			throw std::out_of_range("Error: too large a number.");
	}
	return ( value );
}

void BitcoinExchange::getDB(void)
{
	DateKey			date;
	std::string		line;
	float			value;
	std::ifstream	inFile;

	inFile.open("data.csv");
	if (inFile.is_open() == false)
		throw std::runtime_error("Error: cannot open database file.");
	getline(inFile, line);
	while (inFile.eof() == false)
	{
		getline(inFile, line);
		if (line.empty() == true)
			continue;
		value = BitcoinExchange::parseLine(line, ',', &date);
		data[date] = value;
	}
}

std::map<DateKey, float>::iterator BitcoinExchange::getbound(DateKey date)
{
	std::map<DateKey, float>::iterator bound;
	std::map<DateKey, float>::iterator lower_bound;

	//Returns the exact bound if it exists
	bound = data.find(date);
	if (bound != data.end())
		return (bound);

	//search the closest date contained in the DB
	//--insert the date in the map
	data[date] = 0;
	bound = data.find(date);
	if (bound == data.begin()) // if the inserted date is the first the bound is the next
		lower_bound = ++bound;
	else // if the inserted date is at the end the bound is the previous
		lower_bound = --bound;
	data.erase(date); // erase the inserted timestamp from map.
	return (bound);
}

void BitcoinExchange::Exchange(const char *inFileName)
{
	std::string							line;
	DateKey 							date;
	std::map<DateKey, float>::iterator	bound;
	float								value;
	std::ifstream						inFile;

	inFile.open(inFileName);
	if (inFile.is_open() == false)
		throw std::runtime_error("Error: cannot open infile.");
	getline(inFile, line);
	while (inFile.eof() == false)
	{
		getline(inFile, line);
		if (line.empty() == true)
			continue;
		try{
			value = BitcoinExchange::parseLine(line, '|', &date);
			bound = getbound(date);
			std::cout << date.getFullDate() << " => " << value << " = " << bound->second * value << "\n";
		} catch (std::exception &e)
		{
			std::cout << e.what() << "\n";
		}
	}
}

//orthodox cononical form
BitcoinExchange::BitcoinExchange(void) {}
BitcoinExchange::BitcoinExchange(const BitcoinExchange &copy)
{
	(void)copy;
}
BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &copy)
{
	(void)copy;
	return (*this);
}
BitcoinExchange::~BitcoinExchange(void) {}