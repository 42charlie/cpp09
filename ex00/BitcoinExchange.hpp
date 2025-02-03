#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>
#include <map>

#ifndef BEXCH_
#define BEXCH_

class BitcoinExchange{
	private :
		static std::map<time_t, float>				data;
		BitcoinExchange(void);
		BitcoinExchange(const BitcoinExchange &copy);
		BitcoinExchange &operator=(const BitcoinExchange &copy);
		~BitcoinExchange(void);
	public :
		static void									getDB(void);
		static void									Exchange(const char *infilname);
		static float								parseLine(std::string line, char delimiter, time_t *key);
		static time_t								gettm(std::string date);
		static float								getValue(std::string value);
		static std::map<time_t, float>::iterator	getbound(time_t timestamp);
		static std::string							tmTodate(time_t timestamp);
		// static void			showMap(){
		// 	std::cout << "===== Map =====\n";
		// 	for (std::map<time_t, float>::iterator it = BitcoinExchange::data.begin(); it != BitcoinExchange::data.end(); it++)
		// 		std::cout << it->first << " : " << it->second << "\n";
		// 	std::cout << "=====  =====\n";
		// }

};

#endif