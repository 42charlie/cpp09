#include <map>
#ifndef BEXCH_
#define BEXCH_

class BitcoinExchange{
	static std::map<int, int> data;
	public:
		static int getDB(void);
		static int gettm(std::string date);
};

#endif