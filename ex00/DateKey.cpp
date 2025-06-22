#include "DateKey.hpp"

int DateKey::daysInMonth[] = {
    31, // Jan
    28, // Feb (will adjust for leap year)
    31, // Mar
    30, // Apr
    31, // May
    30, // Jun
    31, // Jul
    31, // Aug
    30, // Sep
    31, // Oct
    30, // Nov
    31  // Dec
};

DateKey::DateKey()
{
	this->year = 0;
	this->month = 0;
	this->day = 0;
	this->isLeapYear = false;
	this->isValidDateKey = false;
}

DateKey::DateKey(DateKey const &copy)
{
	*this = copy;
}

DateKey &DateKey::operator=(DateKey const &copy)
{
	this->year = copy.year;
	this->month = copy.month;
	this->day = copy.day;
	this->isLeapYear = copy.isLeapYear;
	this->isValidDateKey = copy.isValidDateKey;
	this->fullDate = copy.fullDate;
	return (*this);
}

bool DateKey::operator>(DateKey const &date) const
{
	if (this->year != date.year)
		return this->year > date.year;
	if (this->month != date.month)
		return this->month > date.month;
	return this->day > date.day;
}

bool DateKey::operator<(DateKey const &date) const
{
	if (this->year != date.year)
		return this->year < date.year;
	if (this->month != date.month)
		return this->month < date.month;
	return this->day < date.day;
}

bool DateKey::operator==(DateKey const &date) const
{
	if (this->year != date.year)
		return false;
	if (this->month != date.month)
		return false;
	return this->day == date.day;
}

DateKey::DateKey(int _year, int _month, int _day, std::string _fulldate) :
	year(_year), month(_month), day(_day), fullDate(_fulldate)
{
	isValidDateKey = true;

	//check year
	if (year < 0 || year > 9999)
		isValidDateKey = false;
	
	//check if it's a leap year
	if (year % 400 == 0 || (year % 4 == 0 && year % 100 == 1))
		isLeapYear = true;
	else
		isLeapYear = false;
	
	//check month
	if (month < 0 || month > 12)
		isValidDateKey = false;
	
	//check day
	if (day < 0 || day > daysInMonth[month - 1] + (isLeapYear && month == 1))
		isValidDateKey = false;

}

bool DateKey::getIsValidYear()
{
	return this->isValidDateKey;
}

std::string DateKey::getFullDate()
{
	return this->fullDate;
}

DateKey::~DateKey() {}