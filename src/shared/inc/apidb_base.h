/*
#  MODULE DESCRIPTION:
#  apidb_base.h
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

#ifndef APIDB_BASE_H
#define APIDB_BASE_H

#include <a_dbexception.h>
#include <Qt/qstring.h>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlDatabase>

class APIDB_Base
{
public:
	APIDB_Base() {}
	~APIDB_Base() {}

	void query_exec ( QSqlQuery & query, const QString & q_string ) throw ( A_DBException ) 
	{
		if ( ! query.exec ( q_string ) ) 
		{
			if (! e_method.isEmpty())
				throw A_DBException ( e_method, query );
			else
				throw A_DBException ( query );
		}
	}

	void query_exec ( QSqlQuery & query ) throw ( A_DBException ) 
	{
		if ( ! query.exec () ) 
		{
			if (! e_method.isEmpty())
				throw A_DBException ( e_method, query );
			else
				throw A_DBException ( query );
		}
	}

	void db_open ( QSqlDatabase & dbase ) throw ( A_DBException ) 
	{
		if ( ! dbase.open() ) 
		{
			if (! e_method.isEmpty())
				throw A_DBException ( e_method, dbase );
			else
				throw A_DBException ( dbase );
		}
	}

	void method ( const QString & m ) 
	{
		e_method = m;
	}

	const QString & method() 
	{
		return e_method;
	};

protected:
	QString e_method;
};

#endif // APIDB_BASE_H

