/*
#  MODULE DESCRIPTION:
#  datetime.h
#  <enter module description here>
#
#  AUTHORS:
#  Author Name		Raffaele Ficcadenti
#  Author email		raffaele.ficcadenti@asdc.asi.it
#
#
#  HISTORY:
#  -[Date]- -[Who]------------- -[What]---------------------------------------
#  00.00.00 Author Name         Creation date
#--
#
*/

#include <iostream>
using namespace std;

class DateTime 
{

public:
	DateTime();
	~DateTime();
	void showTime(const char *msg);
	
	void splitTicks(time_t time);
	
private:
   	int seconds;
   	int minutes;
   	int hours;
   	int year;
   	int month;
   	int day;
   
   	bool isLeap(int year);
	int daysPerMonth (int year,int month);
	int daysInYear (int year);
	int reduceDaysToYear(time_t &days);
	int reduceDaysToMonths(time_t &days,int year);

};
