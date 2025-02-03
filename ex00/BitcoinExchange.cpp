#include "BitcoinExchange.hpp"

std::map<long, float> BitcoinExchange::data;

/**
 * @brief get the timestamp(time_t) from the date(string) given
 * @param date date to get timestamp from
 * @return given date converted to timestamp
 */
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

/**
 * @brief convert timestamp to date and return it.
 * @param timestamp the timestamp to convert
 * @return the date [Year-Month-Day] as char*
 */
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
/**
 * @brief set the timestamp and return value from the line given
 * @param line line that contain the timestamp and the value
 * @param delimter ',' or '|' the delimiter that separate timestamp and value.
 * @param timestamp pointer to the timestamp to set
 * @return return the value correspondant to the timestamp
 */
float	BitcoinExchange::parseLine(std::string line, char delimiter, time_t *timestamp)
{
	float				value;
	std::stringstream	ss;

	//throw exception if there is more or less that one delimiter in the line.
	if (std::count(line.begin(), line.end(), delimiter) != 1)
		throw std::invalid_argument("Error: bad input => " + line);

	//get the timestamp(set) : value(return) pair from database or input file.
	ss.str(line);
	getline(ss, line, delimiter);
	*timestamp = gettm(line);
	getline(ss, line);
	value = getValue(line);

	//throw exception if there is any errors.
	if (delimiter == '|' &&*timestamp == -1)
		throw std::invalid_argument("Error: bad input => " + line);
	if (delimiter == '|' && value < 0)
		throw std::out_of_range("Error: not a positive number.");
	if (delimiter == '|' && value > 1000)
		throw std::out_of_range("Error: too large a number.");
	return (value);
}

/**
 * @brief load the .csv database to data map
 * @return 1 is success -1 if not
 */
void BitcoinExchange::getDB(void)
{
	time_t timestamp;
	float value;
	std::string line;
	std::ifstream inFile;

	inFile.open("data.csv");
	if (inFile.is_open() == false)
		throw std::runtime_error("Error: cannot open database file.");
	getline(inFile, line);
	while (inFile.eof() == false)
	{
		getline(inFile, line);
		if (line.empty() == true)
			continue;
		value = BitcoinExchange::parseLine(line, ',', &timestamp);
		data[timestamp] = value;
	}
}
/**
 * @brief get the pair timestamp:value of the given timestamp
 * @param timestamp the timestamp to search for
 * @return iterator the pair timestamp:value
 */
std::map<time_t, float>::iterator BitcoinExchange::getbound(time_t timestamp)
{
	std::map<time_t, float>::iterator lower_bound;
	std::map<time_t, float>::iterator bound;

	//Returns the exact bound if it exists
	bound = data.find(timestamp);
	if (bound != data.end())
		return (bound);

	//search the closest date contained in the DB
	//--insert the timestamp in the map
	data[timestamp] = 0;
	bound = data.find(timestamp);
	if (bound == data.begin()) // if the inserted timestamp is the first the bound is the next
		lower_bound = ++bound;
	else // if the inserted timestamp is at the end the bound is the previous
		lower_bound = --bound;
	data.erase(timestamp); // erase the inserted timestamp from map.
	return (bound);
}

/**
 * @brief outputs the value of a certain amount of bitcoin on a certain date.
 * @inFileName the filename contain some amount of bitcoin
 * @return 1 on error 0 otherwise
 */
void BitcoinExchange::Exchange(const char *inFileName)
{
	float								value;
	time_t								timestamp;
	std::string							line;
	std::ifstream						inFile;
	std::map<time_t, float>::iterator	bound;

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
			value = BitcoinExchange::parseLine(line, '|', &timestamp);
		}
		catch (std::exception &e)
		{
			std::cout << e.what() << "\n";
			continue;
		}
		bound = getbound(timestamp);
		std::cout << tmTodate(timestamp) << " => " << value << " = " << bound->second * value << "\n";
	}
}

//orthodox cononical form
BitcoinExchange::BitcoinExchange(void)
{
	;
}
BitcoinExchange::BitcoinExchange(const BitcoinExchange &copy)
{
	(void)copy;
}
BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &copy)
{
	(void)copy;
	return (*this);
}
BitcoinExchange::~BitcoinExchange(void)
{
	;
}