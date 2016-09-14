#include "datetime.h"
#include "applogger.h"
#include <QtCore/qstring.h>

DateTime::DateTime(void)
{}

DateTime::~DateTime(void)
{}
	
void DateTime::showTime(const char *msg)
{
	QString strDate;
	strDate.sprintf("%s %4d-%02d-%02d %02d:%02d:%02d\n",msg,year,month,day,hours,minutes,seconds);
	lout << strDate;
}

bool DateTime::isLeap(int year) 
{
    return (((year % 4) == 0) && (((year % 100) != 0) || ((year % 400) == 0)));
}

int DateTime::daysPerMonth (int year,int month) 
{
	int _daysPerMonth[] = {31, (isLeap(year) ? 29 : 28), 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	return 	_daysPerMonth[month];
}

int DateTime::daysInYear (int year) 
{
	int _daysPerMonth[] = {31, (isLeap(year) ? 29 : 28), 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	int nDay=0;
	for(int i=0;i<12;i++)
	{
		nDay +=_daysPerMonth[i];
	}	
	return nDay;
}

int DateTime::reduceDaysToYear(time_t &days) {
    int year;
    for (year=1970;days>daysInYear(year);year++) 
    {
        days -= daysInYear(year);
    }
    return year;
}

int DateTime::reduceDaysToMonths(time_t &days,int year) 
{
    int month;
    for (month=0;days>daysPerMonth(year,month);month++)
        days -= daysPerMonth(year,month);
    return month;
}

void DateTime::splitTicks(time_t time) 
{
    seconds = time % 60;
    time /= 60;
    minutes = time % 60;
    time /= 60;
    hours = time % 24;
    time /= 24;

    year = reduceDaysToYear(time);
    month = reduceDaysToMonths(time,year);
    day = int(time);
}
