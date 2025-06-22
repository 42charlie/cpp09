#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>
#include <map>
#include "DateKey.hpp"

#ifndef BEXCH_
#define BEXCH_

class BitcoinExchange{
	private :
		static std::map<DateKey, float>				data;
		BitcoinExchange(void);
		BitcoinExchange(const BitcoinExchange &copy);
		BitcoinExchange &operator=(const BitcoinExchange &copy);
		~BitcoinExchange(void);
	public :
		static void									getDB(void);
		static void									Exchange(const char *infilname);
		static float								parseLine(std::string line, char delimiter, DateKey *key);
		static DateKey									getDateKey(std::string date);
		static float								getValue(std::string value);
		static std::map<DateKey, float>::iterator		getbound(DateKey date);
		// static void			showMap(){
		// 	std::cout << "===== Map =====\n";
		// 	for (std::map<time_t, float>::iterator it = BitcoinExchange::data.begin(); it != BitcoinExchange::data.end(); it++)
		// 		std::cout << it->first << " : " << it->second << "\n";
		// 	std::cout << "=====  =====\n";
		// }

};

#endif