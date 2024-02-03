#include "Timestamp.hpp"
#include <cmath>
#include <mutex>
#include <sstream>
#include <iomanip>
#include <locale>

Timestamp::Timestamp() : internalTime() {}

Timestamp::Timestamp(const Timestamp &obj) : internalTime(obj.internalTime) {}

Timestamp::Timestamp(unsigned int year,unsigned short doy,unsigned short hour) : internalTime(year, doy, hour) {}
Timestamp::Timestamp(unsigned int hoursFromZero)
{
	hoursToTimestamp(hoursFromZero);
}
void Timestamp::hoursToTimestamp(unsigned int hoursFromZero)
{
	internalTime = MyTimepoint(hoursFromZero);
}
void Timestamp::fromYDH(unsigned int year,unsigned short doy,unsigned short hour)
{
	internalTime = MyTimepoint(year, doy, hour);
}

void Timestamp::addHours(unsigned int hours)
{
	internalTime.addHours(hours);
}
Timestamp::~Timestamp()
{
}
Timestamp::Timestamp(const std::string& strDateTime)
{
	stringToTimestamp(strDateTime);
}

int Timestamp::getYear()
{
	return (int)this->internalTime.getYmd().year();
}
unsigned int Timestamp::getHourOfYear()
{
	return this->getHour() + this->getDoy() * 24;
}
unsigned int Timestamp::getMonth()
{
	return (unsigned int)this->internalTime.getYmd().month();
}
unsigned int Timestamp::getDay()
{
	return (unsigned int)this->internalTime.getYmd().day();
}
uint16_t Timestamp::getDoy()
{
	return this->internalTime.getDoy();
}
uint16_t Timestamp::getHour()
{
	return this->internalTime.getHourTimeAbs();
}
unsigned int Timestamp::calculateHourDiff(Timestamp *another)
{
	unsigned int result = internalTime.hoursSinceEpoch - another->internalTime.hoursSinceEpoch;
	if(another->internalTime.hoursSinceEpoch > internalTime.hoursSinceEpoch)
	{
		result = another->internalTime.hoursSinceEpoch - internalTime.hoursSinceEpoch;
	}
	return result;
}
void Timestamp::stringToTimestamp(const std::string& strDateTime/*, const char *inputFormat*/)
{
	int year, month, day, hour;
	sscanf(strDateTime.c_str(), "%d-%d-%d %d",&year,&month, &day ,&hour);
	internalTime = MyTimepoint(year, month, day, hour);
}
std::string Timestamp::getAsString()
{
	std::ostringstream is;
	date::year_month_day ymd = internalTime.getYmd();
	std::stringstream monthSs;
	monthSs << std::setw(2) << std::setfill('0') << ((unsigned) ymd.month());
	std::stringstream hourSs;
	hourSs << std::setw(2) << std::setfill('0') << internalTime.getHourTimeAbs();
	
	is << ymd.year() << "-" << monthSs.str() << "-" << ymd.day() << " " << hourSs.str() << ":00:00";
	return is.str();
}
void Timestamp::print()
{
	using namespace date;
	std::cout << internalTime.getYmd() << " Doy: " << internalTime.getDoy() << " Hour: " << internalTime.getHourTimeAbs() << " || " << getAsString()  << "\n"; 
}
bool Timestamp::isLeap(int year_)
{
	return (((year_ % 4 == 0) && (year_ % 100 != 0)) || (year_ % 400 == 0));
}

void Timestamp::MyTimepoint::addHours(int hours)
{
	auto zeroYear = date::sys_days(date::year_month_day{date::year(0),date::month(1), date::day(1)});
	auto hourYear = date::sys_days(date::days{hours/(int)24});
	auto years = date::year_month_day{ date::sys_days( zeroYear - hourYear ) }.year();
	int yearBeforeAdding = (int)getYmd().year() ;
	if(hours >= 24 && hours < 8760 )//special case for days, no longer than a year
	{
		years = date::year(0);
	}
	int addedYearsInHours = addYears( std::abs((int) years) );
	int hoursRemainder = (hours%24)*2 + (addedYearsInHours - hours);
	if(hours >= 24 && hours < 8760 )//special case 2
	{
		hoursRemainder = hours;
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
	
	//exit(-1);
}