/*
#  MODULE DESCRIPTION:
#  apploggercpp
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

#include "applogger.h"
#include <unistd.h>
#include <iostream>

using namespace std;

static QString ___app_lStreamName = "/dev/null";
static QString ___app_lStreamNameAPPO = "";
static QTextStream __logstream;
static int __aplo_pid;
static QString strDate,strDateOLD;
static QFile * file = NULL;
static QString ___app_lPathLog = "";

AppLogger::AppLogger()
{
	__aplo_pid = ::getpid();

	QDateTime dt = QDateTime::currentDateTime();
	strDate=dt.toString("yyyyMMdd");
	strDateOLD=strDate;

	___app_lStreamNameAPPO=___app_lPathLog+""+strDate+"_"+___app_lStreamName;
	file = new QFile( ___app_lStreamNameAPPO );
	if ( file->open( QIODevice::WriteOnly | QIODevice::Append ) ) {
 		cout << "Opened log file: [" << ___app_lStreamNameAPPO.toStdString().c_str() << "]" << endl;
		__logstream.setDevice( file );
	}
	else
	{
 		cout << "Cant't open log file: [" << ___app_lStreamNameAPPO.toStdString().c_str() << "]" << endl;
	}

}

int AppLogger::aploPid()
{
	return __aplo_pid;
}


AppLogger::~AppLogger()
{
	logStream()->device()->close();
}


void AppLogger::setLogFileName(const QString & lname)
{
	___app_lStreamName = lname;
}

void AppLogger::setLogPath(const QString & lname)
{
	___app_lPathLog = lname;
}

const QString & AppLogger::getLogFileName()
{
	return ___app_lStreamName;
}

QTextStream * AppLogger::logStream()
{
	QDateTime dt = QDateTime::currentDateTime();
	strDate=dt.toString("yyyyMMdd");

	if(strDate!=strDateOLD)
	{

		if(file!=NULL) file->close(); // Chiudo il vecchi file.
		__logstream.device()->close(); // chiudo lo stream del giorno precedentestream

		
		/* apro il nuovo strem per il nuovo giorno */
		___app_lStreamNameAPPO=___app_lPathLog+""+strDate+"_"+___app_lStreamName;
		file = new QFile( ___app_lStreamNameAPPO );
		if ( file->open( QIODevice::WriteOnly | QIODevice::Append ) ) {
			cout << "Change log file: [" << ___app_lStreamNameAPPO.toStdString().c_str() << "]" << endl;	
			__logstream.setDevice( file );
		}
		else
		{
			cout << "Cant't open log file: [" << ___app_lStreamNameAPPO.toStdString().c_str() << "]" << endl;
		}

		dt = QDateTime::currentDateTime();
		strDateOLD=dt.toString("yyyyMMdd");
	}
	return &__logstream;
}
