#ifndef _DATE_H
#define _DATE_H

#include <iostream>

class DateKey{
	private:
		int			year;
		int			month;
		int			day;
		bool		isValidDateKey;
		bool		isLeapYear;
		std::string	fullDate;
		static int	daysInMonth[12];
	public:
		DateKey();
		DateKey(DateKey const &copy);
		DateKey &operator=(DateKey const &copy);
		DateKey(int year, int month, int day, std::string fulldate);
		bool operator>(DateKey const &date) const ;
		bool operator<(DateKey const &date) const ;
		bool operator==(DateKey const &date) const ;
		~DateKey();

		bool		getIsValidYear();
		std::string	getFullDate();
	};

#endif