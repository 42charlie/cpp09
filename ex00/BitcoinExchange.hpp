#include <iostream>
#include <string>
#include <map>
#ifndef BEXCH_
#define BEXCH_

class BitcoinExchange{
	static std::map<time_t, float> data;
	public:
		static int		getDB(void);
		static float	parseLine(std::string line, char delimiter, time_t *key);
		static time_t	gettm(std::string date);
		static std::string tmTodate(time_t timestamp);
		static float	getValue(std::string value);
		static void		showMap(){
			std::cout << "===== Map =====\n";
			for (std::map<time_t, float>::iterator it = BitcoinExchange::data.begin(); it != BitcoinExchange::data.end(); it++)
				std::cout << it->first << " : " << it->second << "\n";
			std::cout << "=====  =====\n";
		}
		static int		Exchange(const char *infilname);
		static std::map<time_t, float>::iterator getbound(time_t timestamp);

};

#endif