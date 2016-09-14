/*
#  MODULE DESCRIPTION:
#  appologger.h
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

#ifndef APPLOGGER_H
#define APPLOGGER_H

#include <QtCore/qfile.h>
#include <QtCore/qdatetime.h>
#include <QtCore/qtextstream.h>

#define rlout	(*(AppLogger::logStream()))
#define lout	(*(AppLogger::logStream())) << "[" << AppLogger::aploPid() << "]:"
#define dout	(*(AppLogger::logStream())) << "[" << QDateTime::currentDateTime ().toString() << "]:"


/**
 * Questa classe implementa uno stream per la produzione del output di log dell'applicazione.
 * Viene utilizzata quando l'applicazione non ha accesso diretto allo standard output.
 */
class AppLogger{
public:
	AppLogger();

	~AppLogger();

		/** Questo metodo statico definisce il nome (path) del file di log. Deve essere richiamato PRIMA
			di istanziare la class @ref AppLogger.
		*/
	static void setLogFileName(const QString & lname);
	static void setLogPath(const QString & lname);
	static const QString & getLogFileName();
	static QTextStream * logStream();
	static int aploPid();
};

#endif
