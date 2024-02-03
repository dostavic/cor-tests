#ifndef TIMESTAMP_HPP
#define TIMESTAMP_HPP
#include <string>
#include <iostream>
#include <chrono>
#include "date.h"


/**
 * @class Printable
 * @author developer
 * @date 11/09/19
 * @file OutfilData.hpp
 * @brief Interface that signifies that class member can be printed out.
 */
struct Printable
{
	virtual void print() = 0;
};
class Timestamp : public Printable
{
private:
	void stringToTimestamp(const std::string& strDateTime);
	Timestamp();
	struct MyTimepoint
	{
		int hoursSinceEpoch;
		MyTimepoint() : hoursSinceEpoch(0) {}
		MyTimepoint(date::year_month_day ymd, int hours)
		{
			hoursSinceEpoch = date::sys_days{ymd}.time_since_epoch().count() * 24 + hours;
			hoursSinceEpoch += (hoursSinceEpoch < 0) ? -23 : 0;
		}
		MyTimepoint(int hours)
		{
			hoursSinceEpoch = date::sys_days(date::year_month_day{date::year(1),date::month(1), date::day(1)}).time_since_epoch().count() * 24 + hours;
			hoursSinceEpoch += (hoursSinceEpoch < 0) ? -23 : 0;
		}
		MyTimepoint(int year, int month, int day, int hours)
		{
			hoursSinceEpoch = date::sys_days(date::year_month_day{date::year(year),date::month(month), date::day(day)}).time_since_epoch().count() * 24 + hours;
			hoursSinceEpoch += (hoursSinceEpoch < 0) ? -23 : 0;
		}
		MyTimepoint(int year, int doy, int hours)
		{
			auto ymd = date::year_month_day(date::year(year), date::month(1), date::day(1));
			ymd = date::sys_days{date::sys_days{ymd} + date::days{doy - 1}};
			hoursSinceEpoch = date::sys_days{ymd}.time_since_epoch().count() * 24 + hours;
			hoursSinceEpoch += (hoursSinceEpoch < 0) ? -23 : 0;
		}
		date::year_month_day getYmd()
		{
			return date::sys_days(date::days{hoursSinceEpoch/(int)24});
		}
		unsigned int getDoy()
		{
			return std::abs((date::sys_days{getYmd()} - date::sys_days{date::year_month_day{getYmd().year(),date::month(1), date::day(1)}}).count()) + 1;
		}
		int getHourTime()
		{
			return hoursSinceEpoch % 24;
		}
		int getHourTimeAbs()
		{
			return (hoursSinceEpoch < 0) ? 23 - std::abs(getHourTime()) : std::abs(getHourTime());
		}
		
		bool isLeap(int year_)
		{
			return (((year_ % 4 == 0) && (year_ % 100 != 0)) || (year_ % 400 == 0));
		}
		void addHours(const int hours);/*
		{
			auto zeroYear = date::sys_days(date::year_month_day{date::year(0),date::month(1), date::day(1)});
			auto hourYear = date::sys_days(date::days{hours/(int)24});
			auto years = date::year_month_day{ date::sys_days( zeroYear - hourYear ) }.year();
			int yearBeforeAdding = (int)getYmd().year() ;
			int addedYearsInHours = addYears( std::abs((int) years) );
			int hoursRemainder = (hours%24)*2 + (addedYearsInHours - hours);
			if(hours == 24)
			{
				hoursRemainder = 24;
			}
			if(addedYearsInHours > 0 && (isLeap( yearBeforeAdding ) || (876600 == addedYearsInHours) ) )
			{
				hoursRemainder -= 24 ;
			}
			bool wasNegative = (hoursSinceEpoch < 0);
			hoursSinceEpoch += hoursRemainder;
			bool isPositive = (hoursSinceEpoch >= 0);
			if(wasNegative && isPositive)
			{
				hoursSinceEpoch += 23;
			}
		}*/
	private:
		int addYears(const int years)
		{
			auto t = getYmd() + date::years(years);
			auto t2 = std::abs(date::sys_days{getYmd()}.time_since_epoch().count() - date::sys_days{t}.time_since_epoch().count());
			bool wasNegative = (hoursSinceEpoch < 0);
			hoursSinceEpoch += t2 * 24;
			bool isPositive = (hoursSinceEpoch >= 0);
			if(wasNegative && isPositive)
			{
				hoursSinceEpoch += 23;
			}
			return t2 * 24;
		}
	};
	MyTimepoint internalTime;
public:
	Timestamp(const Timestamp &obj);
	Timestamp(unsigned int hoursFromZero);
	Timestamp(unsigned int year,unsigned short doy,unsigned short hour);
	Timestamp(const std::string& strDateTime);
	unsigned int calculateHourDiff(Timestamp *another);
	static bool isLeap(int year);
	void print()  override;
	void hoursToTimestamp(unsigned int hoursFromZero);
	void addHours(unsigned int hours);
	~Timestamp();
	int getYear();
	unsigned int getMonth();
	unsigned int getDay();
	unsigned int getHourOfYear();
	void fromYDH(unsigned int year,unsigned short doy,unsigned short hour);
	uint16_t getDoy();
	uint16_t getHour();
	std::string getAsString();
	inline bool operator==(const Timestamp& rhs) const { return (internalTime.hoursSinceEpoch == rhs.internalTime.hoursSinceEpoch); }
	inline bool operator!=(const Timestamp& rhs) const { return (internalTime.hoursSinceEpoch != rhs.internalTime.hoursSinceEpoch); }
	inline bool operator< (const Timestamp& rhs) const { return (internalTime.hoursSinceEpoch < rhs.internalTime.hoursSinceEpoch); }
	inline bool operator> (const Timestamp& rhs) const { return (internalTime.hoursSinceEpoch > rhs.internalTime.hoursSinceEpoch); }
	inline bool operator<=(const Timestamp& rhs) const { return (internalTime.hoursSinceEpoch <= rhs.internalTime.hoursSinceEpoch); }
	inline bool operator>=(const Timestamp& rhs) const { return (internalTime.hoursSinceEpoch >= rhs.internalTime.hoursSinceEpoch); }
};
#endif // TIMESTAMP_HPP
