#ifndef A_DBEXCEPTION_H
#define A_DBEXCEPTION_H

#include <Qt/qstring.h>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlDatabase>
#include <exception>

class A_DBException : public std::exception
{
public:
	A_DBException ( const QString& meth, QSqlQuery& queryError ) throw() 
	{
		e_method = meth;
		e_error_explanation = queryError.lastError().text();
	}

	A_DBException ( const QString& meth, QSqlDatabase& dbError ) throw() 
	{
		e_method = meth;
		e_error_explanation = dbError.lastError().text();
	}

	A_DBException ( QSqlQuery & queryError ) throw() 
	{
		e_error_explanation = queryError.lastError().text();
	}

	A_DBException ( QSqlDatabase & dbError ) throw() 
	{
		e_error_explanation = dbError.lastError().text();
	}

	A_DBException ( const QString& meth ) throw() 
	{
		e_method = meth;
	}

	~A_DBException() throw() {};

	const char * what() throw() 
	{
		return "Database Operation Error";
	}

	const QString & explain() throw() 
	{
		return e_error_explanation;
	}

	const QString preface() throw() 
	{
		QString m = "DB Error - " + e_method + ":";
		e_method.clear();
		return m;
	}

	void set_method ( const QString& meth ) throw() {
		e_method = meth;
	}

private:
	QString e_method;
	QString e_error_explanation;
};

#endif // A_DBEXCEPTION_H
