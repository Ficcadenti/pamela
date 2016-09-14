/*
#  MODULE DESCRIPTION:
#  apidb_dispatcher.h
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

#ifndef APIDB_DISPATCHER_H
#define APIDB_DISPATCHER_H

#include <stdlib.h>
#include <iostream>
#include <unistd.h>


#include <QtCore/qstring.h>
#include <QtCore/qdatetime.h>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QtCore/qvariant.h>
#include <QtCore/qlist.h>
#include <QtCore/qstringlist.h>

#include "apidb_define.h"
#include "apidb_base.h"
#include "cnfglobals.h"
#include "pipeline.h"
#include "user.h"

#define DEBUG_APIDB_DISPATCHER				1
// #define DEBUG_APIDB_DISPATCHER_SELECT			1
// #define DEBUG_APIDB_DISPATCHER_SANITY_CHECK_TIME	1
// #define DEBUG_APIDB_DISPATCHER_SANITY_CHECK_USER	1
// #define DEBUG_APIDB_DISPATCHER_SANITY_CHECK_PIPELINE	1
// #define DEBUG_APIDB_DISPATCHER_DELETE			1
// #define DEBUG_APIDB_DISPATCHER_DEBUG			1

typedef QMap<int,QString>::iterator statusList_it;
typedef QMap<int,QString>::iterator errorList_it;
	
class ApiDB_Dispatcher: public APIDB_Base, QObject
{
public:
	ApiDB_Dispatcher();
	~ApiDB_Dispatcher();
	
	bool openDB ( QString strHOSTNAME, QString strPORT, QString hstrDBNAME, QString hstrUSER, QString hstrPSWD );
	void closeDB();
	bool isConnect();
	void setDBNameConnection (QString str);
	void load();
	bool testSelect();
	void debug();
	void releasePipeLine();
	void releaseUsers();
	
	/* Manage global */
	void setPathExe(QString str);
	QString getStatus(int status);
	QString getError(int id_error);
	bool sanityCheck();
	
	
	/* Manage User*/
	QString getUserNAME(int id_user);
	QString getUserLOGIN(int id_user);
	QString getUserDESC(int id_user);
	
	
	/* Manage PipeLine*/
	pipeLineList *getPipeLineList();
	int getPipeLineSize();
	int getPipeLineID(int i);
	QString getPipeLineDESC(int i);
	int getPipeLineID_USER(int i);
	
	/* Manage Task */
	int getTaskSize(int id_pipeline);
	int getTaskID(int id_pipeline,int i);
	QString getTaskDESC(int id_pipeline,int i);
	QString getTaskEXE(int id_pipeline,int i);
	int getTaskSTATUS(int id_pipeline,int i);
	int getTaskERROR(int id_pipeline,int i);
	int getTaskPID(int id_pipeline,int i);
	
	bool setTaskSTATUS(int id_user,int id_pipeline,int id_task,int status);
	bool setTaskPID(int id_user,int id_pipeline,int id_task,int pid);
	bool setTaskLASTSTART(int id_user,int id_pipeline,int id_task,QDateTime last_start);    
	bool startTask(int id_user,int id_pipeline,int id_task,int *newPid);
    
    
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
	
	bool getPipeLine();
	bool getStatusLib();
	bool getErrorLib();
	bool getUsers();
	bool sanityCheckTime();
	bool sanityCheckUser();
	bool sanityCheckPipeLine();
	bool deleteRecordInTable ( QList<QString> listTable, const QString strDelete );
	bool setTaskERROR(int id_user,int id_pipeline,int id_task,int id_error);
	
	QSqlDatabase 	db;
	QString 	m_connection;
	int 		last_result_db;
	bool 		enablePSWD;
	
	QString 	path_exe;
	
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
	
	
	/* PipeLine*/
	pipeLineList ListPipeLine;
	
	/* Users */
	userList UserList;
	
	/* Librerie STATUS,ERROR*/
	QMap<int,QString>   StatusList;
	QMap<int,QString>   ErrorList;
    
};

#endif // APIDB_DISPATCHER_H