/*
#  MODULE DESCRIPTION:
#  apidb_pamelaroot.h
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

#ifndef APIDB_PAMELAROOT_H
#define APIDB_PAMELAROOT_H

// Standard Class Includes 
#include <stdlib.h>
#include <iostream>
#include <unistd.h>


// QT Class Includes 
#include <QtCore/qstring.h>
#include <QtCore/qdatetime.h>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QtCore/qvariant.h>
#include <QtCore/qlist.h>
#include <QtCore/qstringlist.h>

// My Class Includes 
#include "apidb_define.h"
#include "apidb_base.h"
#include "cnfglobals.h"
#include "task_param_query.h"

// #define DEBUG_APIDB_PAMELAROOT_DEBUG			1
#define DEBUG_APIDB_PAMELAROOT_SELECT			1

typedef QMap<int,QString>::iterator typeList_it;
typedef QMap<int,QString>::iterator paramList_it;
typedef QMap<int,QString>::iterator statusList_it;
typedef QMap<int,QString>::iterator errorList_it;
typedef QMap<int,QString>::iterator operatorList_it;

	
class ApiDB_PamelaRoot: public APIDB_Base, QObject
{
public:
	ApiDB_PamelaRoot();
	~ApiDB_PamelaRoot();
	
	bool openDB ( QString strHOSTNAME, QString strPORT, QString hstrDBNAME, QString hstrUSER, QString hstrPSWD );
	void closeDB();
	bool isConnect();
	void setDBNameConnection (QString str);
	void load();
	void debug();
	
	/* Manage global */
	QString getStatus(int status);
	QString getError(int id_error);
	QString getType(int id_type);
	QString getParam(int id_param);
	QString getOperator(int id_operator);
	
	/* Manage Task */
	void setPid(int pid);
	QString getTaskROOTFILE(int pid);
	QString getTaskPNGFILE(int pid);
	QString getTaskQUERYMONGO(int pid);
	taskParamQueryList *getParamList();
	void releaseTaskParam();
	
	
	bool setTaskSTATUS(int pid,int status);
	
    
private:
	void setError ( QSqlDatabase &dbError );
	inline int getExitStatusDB() {
		return last_result_db;
	}

	bool insertRecordInTable_BLOC();
	void insertPrepare ( int type );
	bool insertCreate ( int occurrenceNum );
	bool writeData ( int type );
	QString getTableName ( int t );
	QString formatValue ( int itType, QString value );
	
	bool getStatusLib();
	bool getErrorLib();
	bool getTypeLib();
	bool getParamLib();
	bool getOperatorLib();
	bool getParamQuery();
	bool deleteRecordInTable ( QList<QString> listTable, const QString strDelete );
	bool setTaskERROR(int id_user,int id_pipeline,int id_task,int id_error);
	
	QSqlDatabase 	db;
	QString 	m_connection;
	int 		last_result_db;
	bool 		enablePSWD;
	int 		myPid;
	
	QString 	strHOSTNAME;
	QString 	strPORT;
	QString		strDBNAME;
	QString 	strUSER;
	QString 	strPSWD;
	

	/* campi generici per costruzione insert */
	QString 	strTableName;
	QStringList 	strFields;
	QStringList 	strValues;
	QString     	strInsert;
	QString     	strSelect;
	QList<int>	strType;
	int 		fieldsNum;
	
	
	/* Task Param List */
	taskParamQueryList tpqList;
	
	/* Librerie STATUS,ERROR,TYPE,PARAM*/
	QMap<int,QString>   StatusList;
	QMap<int,QString>   TypeList;
	QMap<int,QString>   ParamList;
	QMap<int,QString>   ErrorList;
	QMap<int,QString>   OperatorList;
	
    
};

#endif // APIDB_PAMELAROOT_H