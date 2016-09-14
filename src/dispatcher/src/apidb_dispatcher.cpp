/*
#  MODULE DESCRIPTION:
#  apidb_dispatcher.cpp
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

#include "apidb_dispatcher.h"
#include "applogger.h"


using namespace std;

void ApiDB_Dispatcher::releasePipeLine()
{
	for ( pipeLineList_it it_pipeLineList = ListPipeLine.begin(); it_pipeLineList != ListPipeLine.end(); it_pipeLineList++ )
	{
		PipeLine *pl = *it_pipeLineList;
		if(pl!=NULL)
		{
			if(pl->data.tList!=NULL)
			{
			    pl->data.tList->clear();
			    delete(pl->data.tList);
			}
			delete (pl);
		}
	}
	ListPipeLine.clear();
} /* releasePipeLine */

void ApiDB_Dispatcher::releaseUsers()
{
	for ( userList_it it_userList = UserList.begin(); it_userList != UserList.end(); it_userList++ )
	{
		User *user = *it_userList;
		if(user!=NULL)
		{
			delete (user);
		}
	}
	UserList.clear();
} /* releaseUsers */



ApiDB_Dispatcher::ApiDB_Dispatcher() : m_connection ( "ApiDB_Dispatcher" )
{
  
} /* ApiDB_Dispatcher */

ApiDB_Dispatcher::~ApiDB_Dispatcher()
{
	if(isConnect()==true)
	{
		closeDB();
	}

	releasePipeLine();
	releaseUsers();
} /* ~ApiDB_Dispatcher */

void ApiDB_Dispatcher::closeDB()
{
	QString connection;
	connection = db.connectionName();
	db.close();
	db = QSqlDatabase();
	db.removeDatabase ( connection );
} /* closeDB */

bool ApiDB_Dispatcher::openDB ( QString hstrHOSTNAME, QString hstrPORT, QString hstrDBNAME, QString hstrUSER, QString hstrPSWD )
{
	bool noDbError = false;
	bool ok;
	
	method ( "openDB(ApiDB_Dispatcher): " );	

	strHOSTNAME 	= hstrHOSTNAME;
	strPORT 	= hstrPORT;
	strDBNAME 	= hstrDBNAME;
	strUSER 	= hstrUSER;
	strPSWD 	= hstrPSWD;
	
	if ( isConnect() == false )
	{   
		db = QSqlDatabase::addDatabase ( "QMYSQL" ,m_connection); // QMYSQL -> MySql Database
		db.setHostName(strHOSTNAME);
		db.setDatabaseName ( strDBNAME );
		db.setPort(strPORT.toInt(&ok,10));		
		db.setUserName ( strUSER );
		db.setPassword ( strPSWD );
		db.setConnectOptions("MYSQL_OPT_RECONNECT=1");
		
		
		try {
			db_open( db );
			//lout  << "Connected to DB APIDB_Pamela ."<< endl;
			noDbError=true;
		}
		catch ( A_DBException & de ) 
		{
			lout << de.preface().toLatin1() << de.explain().toLatin1() << endl;
			noDbError=false;
		}
	}
	else
	{
		lout << "Connected to DB is already open." << endl;	
		noDbError=true;
	}
	
	setError ( db );
			
	return noDbError;
} /* openDB */

void ApiDB_Dispatcher::setError ( QSqlDatabase &dbError )
{
	last_result_db = dbError.lastError().number();
} /* setError */

bool ApiDB_Dispatcher::isConnect()
{
	QSqlDatabase db_test = QSqlDatabase::database(m_connection);
// 	lout << "ApiDB_Dispatcher.isOpen("<< m_connection << ")=" << db_test.isOpen() << endl;	
	return db_test.isOpen();
} /* isConnect */

bool ApiDB_Dispatcher::testSelect()
{
	bool noDbError=false;
	
	QString strFieldName="";
	QString tableName="tab_operators_lib";
	QString fieldName[]={"id_opt","name_opt","desc_opt",""};
	QString strWhere="1";
	QString strOrderBy="id_opt asc";
	
	QMap<QString, int> fieldName_toPos;
	
	int i=0;
	while(fieldName[i]!="")
	{
		strFieldName+=fieldName[i];
		strFieldName+=",";
		fieldName_toPos.insert ( fieldName[i], i );
		++i;
	}
	
	strFieldName=strFieldName.mid(0,strFieldName.size()-1); // remove , at the end string
	
	strSelect="SELECT "+strFieldName;
	strSelect+=" FROM "+tableName;
	strSelect+=" WHERE "+strWhere;
	strSelect+=" ORDER BY "+strOrderBy;

#ifdef DEBUG_APIDB_DISPATCHER_SELECT	
	lout << strSelect << endl;
#endif
	
	try {
		
		QSqlQuery query(db);
		query.prepare( strSelect );
		query_exec( query );
		
		while ( query.next() ) 
		{	
			int id_opt;
			id_opt=query.value(fieldName_toPos.value("id_opt")).toInt();
			char name_opt[45],desc_opt[45];
			c_qstrncpy(name_opt,qPrintable(query.value(fieldName_toPos.value("name_opt")).toString()),45);
			c_qstrncpy(desc_opt,qPrintable(query.value(fieldName_toPos.value("desc_opt")).toString()),45);
			lout << "id_opt=" << id_opt << " name_opt="<<name_opt << " desc_opt=" << desc_opt << endl;
		}
		noDbError=true;
	}
	catch ( A_DBException & de ) 
	{
		noDbError=false;
		lout << de.preface().toLatin1()  << de.explain().toLatin1()  << endl;
	}
	
	return noDbError;  
} /* testSelect */

void ApiDB_Dispatcher::debug()
{		

	lout << "START PipeLine" << endl;
	for ( pipeLineList_it it_pipeLineList = ListPipeLine.begin(); it_pipeLineList != ListPipeLine.end(); it_pipeLineList++ )
	{
		
		lout << "id_pipeline   = " << it_pipeLineList.key() << endl; 	
		lout << "id_user       = " << it_pipeLineList.value()->data.id_user << endl;
		lout << "pipeline_desc = " << it_pipeLineList.value()->data.pipeline_desc << endl;
		
		for ( taskList_it it_taskList = it_pipeLineList.value()->data.tList->begin(); it_taskList != it_pipeLineList.value()->data.tList->end(); it_taskList++ )
		{
			lout << "  task_id     = " << it_taskList.key() << endl;
			lout << "  task_desc   = " << it_taskList.value()->data.task_desc << endl;
			lout << "  task_exe   = " << it_taskList.value()->data.task_exe << endl;
			lout << "  task_pid    = " << it_taskList.value()->data.task_pid << endl;
			lout << "  task_status = " << it_taskList.value()->data.status << endl;
			lout << "  task_error = " << it_taskList.value()->data.id_error << endl;
		}
	}
	lout << "END PipeLine " << endl;
	lout << endl;
	
	lout << "START Status Lib " << endl;
	for ( statusList_it it_statusList = StatusList.begin(); it_statusList != StatusList.end(); it_statusList++ )
	{
	      lout << "  " << it_statusList.key() << "=" << it_statusList.value() << endl; 
	}
	lout << "END Status Lib " << endl;
	
	lout << endl;
	
	lout << "START User " << endl;
	for ( userList_it it_userList = UserList.begin(); it_userList != UserList.end(); it_userList++ )
	{
	      lout << "  " << it_userList.key() << ": " 
		<< it_userList.value()->data.login 
		<< "," << it_userList.value()->data.name 
		<< "," << it_userList.value()->data.desc 
		<< endl; 
	}
	lout << "END User " << endl;
} /* debug */

QString ApiDB_Dispatcher::getStatus(int status)
{
	QString descr;
	int key=status;
	
	statusList_it it_statusList = StatusList.find(key);
			
	if(it_statusList == StatusList.end() ) // key not found!!!!
	{
		descr="Undefined";
	}
	else
	{
		descr=StatusList.value(key);
	}
	  
	return descr;
} /* getStatus */

QString ApiDB_Dispatcher::getError(int id_error)
{
	QString descr;
	int key=id_error;
	
	errorList_it it_errorList = ErrorList.find(key);
			
	if(it_errorList == ErrorList.end() ) // key not found!!!!
	{
		descr="Undefined";
	}
	else
	{
		descr=ErrorList.value(key);
	}
	  
	return descr;
} /* getError */

bool ApiDB_Dispatcher::getErrorLib()
{
	method ( "getErrorLib(ApiDB_Dispatcher): " );	
	
	bool noDbError=false;
	
	QString strFieldName="";
	QString tableName="tab_error_lib";
	QString fieldName[]={"id_error","error_desc",""};
	QString strWhere="1";
	QString strOrderBy="id_error";
	
	QMap<QString, int> fieldName_toPos;
	
	int i=0;
	while(fieldName[i]!="")
	{
		strFieldName+=fieldName[i];
		strFieldName+=",";
		fieldName_toPos.insert ( fieldName[i], i );
		++i;
	}
	
	strFieldName=strFieldName.mid(0,strFieldName.size()-1); // remove , at the end string
	
	strSelect="SELECT "+strFieldName;
	strSelect+=" FROM "+tableName;
	strSelect+=" WHERE "+strWhere;
	strSelect+=" ORDER BY "+strOrderBy;

#ifdef DEBUG_APIDB_DISPATCHER_SELECT	
	lout << strSelect << endl;
#endif
	
	try {
		
		QSqlQuery query(db);
		query.prepare( strSelect );
		query_exec( query );
		
		while ( query.next() ) 
		{	
			
			int key=query.value(fieldName_toPos.value("id_error")).toInt();
			QString value=query.value(fieldName_toPos.value("error_desc")).toString();
						
 			errorList_it it_errorList = ErrorList.find(key);
			
			if(it_errorList == ErrorList.end() ) // key not found!!!!
			{
				ErrorList.insert(key,value);
			}

		}
		noDbError=true;
	}
	catch ( A_DBException & de ) 
	{
		noDbError=false;
		lout << de.preface().toLatin1()  << de.explain().toLatin1()  << endl;
	}
	
	return noDbError;  
} /* getErrorLib */

bool ApiDB_Dispatcher::getStatusLib()
{
	method ( "getStatusLib(ApiDB_Dispatcher): " );	
	
	bool noDbError=false;
	
	QString strFieldName="";
	QString tableName="tab_status_lib";
	QString fieldName[]={"id_status","descr_status",""};
	QString strWhere="1";
	QString strOrderBy="id_status";
	
	QMap<QString, int> fieldName_toPos;
	
	int i=0;
	while(fieldName[i]!="")
	{
		strFieldName+=fieldName[i];
		strFieldName+=",";
		fieldName_toPos.insert ( fieldName[i], i );
		++i;
	}
	
	strFieldName=strFieldName.mid(0,strFieldName.size()-1); // remove , at the end string
	
	strSelect="SELECT "+strFieldName;
	strSelect+=" FROM "+tableName;
	strSelect+=" WHERE "+strWhere;
	strSelect+=" ORDER BY "+strOrderBy;

#ifdef DEBUG_APIDB_DISPATCHER_SELECT	
	lout << strSelect << endl;
#endif
	
	try {
		
		QSqlQuery query(db);
		query.prepare( strSelect );
		query_exec( query );
		
		while ( query.next() ) 
		{	
			
			int key=query.value(fieldName_toPos.value("id_status")).toInt();
			QString value=query.value(fieldName_toPos.value("descr_status")).toString();
						
 			statusList_it it_statusList = StatusList.find(key);
			
			if(it_statusList == StatusList.end() ) // key not found!!!!
			{
				StatusList.insert(key,value);
			}

		}
		noDbError=true;
	}
	catch ( A_DBException & de ) 
	{
		noDbError=false;
		lout << de.preface().toLatin1()  << de.explain().toLatin1()  << endl;
	}
	
	return noDbError;  
} /* getStatusLib */

bool ApiDB_Dispatcher::getUsers()
{
	method ( "getUsers(ApiDB_Dispatcher): " );	
	 
	bool noDbError=false;
	User *user;
	
	QString strFieldName="";
	QString tableName="tab_users";
	QString fieldName[]={"id_user","login","name","user_desc",""};
	QString strWhere="1";
	QString strOrderBy="id_user";
	
	QMap<QString, int> fieldName_toPos;
	
	int i=0;
	while(fieldName[i]!="")
	{
		strFieldName+=fieldName[i];
		strFieldName+=",";
		fieldName_toPos.insert ( fieldName[i], i );
		++i;
	}
	
	strFieldName=strFieldName.mid(0,strFieldName.size()-1); // remove , at the end string
	
	strSelect="SELECT "+strFieldName;
	strSelect+=" FROM "+tableName;
	strSelect+=" WHERE "+strWhere;
	strSelect+=" ORDER BY "+strOrderBy;

#ifdef DEBUG_APIDB_DISPATCHER_SELECT	
	lout << strSelect << endl;
#endif
	try {
		
		QSqlQuery query(db);
		query.prepare( strSelect );
		query_exec( query );
		
		while ( query.next() ) 
		{	
			int key=query.value(fieldName_toPos.value("id_user")).toInt();
			userList_it it_userList = UserList.find(key);
			
			if(it_userList != UserList.end() ) /* key found!!!! */
			{
				/* Do nothing */
			}
			else 	/* new key!!!! */
			{
				user = new User();
				
				c_qstrncpy(user->data.login,qPrintable(query.value(fieldName_toPos.value("login")).toString()),USER_LOGIN_LEN);
				c_qstrncpy(user->data.name,qPrintable(query.value(fieldName_toPos.value("name")).toString()),USER_NAME_LEN);
				c_qstrncpy(user->data.desc,qPrintable(query.value(fieldName_toPos.value("user_desc")).toString()),USER_DESC_LEN);
				
				UserList.insert(key,user);
				
			}
			
		}
		noDbError=true;
	}
	catch ( A_DBException & de ) 
	{
		noDbError=false;
		lout << de.preface().toLatin1()  << de.explain().toLatin1()  << endl;
	}
	
	return noDbError;  
} /* getUsers */

bool ApiDB_Dispatcher::getPipeLine()
{
	method ( "getPipeLine(ApiDB_Dispatcher): " );	
	 
	bool noDbError=false;
	PipeLine *pipeline;
	Task *t;
	
	QString strFieldName="";
	QString tableName="tab_pipeline";
	QString fieldName[]={"id_user","id_pipeline","id_task","pipeline_desc","status","task_desc","task_exe","task_pid","id_error",""};
	QString strWhere="1";
	QString strOrderBy="id_pipeline";
	
	QMap<QString, int> fieldName_toPos;
	
	int i=0;
	while(fieldName[i]!="")
	{
		strFieldName+=fieldName[i];
		strFieldName+=",";
		fieldName_toPos.insert ( fieldName[i], i );
		++i;
	}
	
	strFieldName=strFieldName.mid(0,strFieldName.size()-1); // remove , at the end string
	
	strSelect="SELECT "+strFieldName;
	strSelect+=" FROM "+tableName;
	strSelect+=" WHERE "+strWhere;
	strSelect+=" ORDER BY "+strOrderBy;

#ifdef DEBUG_APIDB_DISPATCHER_SELECT	
	lout << strSelect << endl;
#endif
	try {
		
		QSqlQuery query(db);
		query.prepare( strSelect );
		query_exec( query );
		
		while ( query.next() ) 
		{	
			int key=query.value(fieldName_toPos.value("id_pipeline")).toInt();
			
			pipeLineList_it it_pipeLineList = ListPipeLine.find(key);
			
			if(it_pipeLineList != ListPipeLine.end() ) /* key found!!!! */
			{
				/* GET TASK */
				int key_task=query.value(fieldName_toPos.value("id_task")).toInt();
				
				t = new Task();
				t->data.task_pid=query.value(fieldName_toPos.value("task_pid")).toInt();
				t->data.status=query.value(fieldName_toPos.value("status")).toInt();
				c_qstrncpy(t->data.task_desc,qPrintable(query.value(fieldName_toPos.value("task_desc")).toString()),PIPELINE_TASK_DESC_LEN);
				c_qstrncpy(t->data.task_exe,qPrintable(query.value(fieldName_toPos.value("task_exe")).toString()),PIPELINE_TASK_EXE_LEN);
				t->data.id_error=query.value(fieldName_toPos.value("id_error")).toInt();
				/* END GET TASK */
				
				taskList *pl=it_pipeLineList.value()->data.tList;
				pl->insert(key_task,t);
				
				
			}
			else /* key not found: new pipeline*/
			{
				pipeline = new PipeLine;
				pipeline->data.id_user = query.value(fieldName_toPos.value("id_user")).toInt();
				c_qstrncpy(pipeline->data.pipeline_desc,qPrintable(query.value(fieldName_toPos.value("pipeline_desc")).toString()),PIPELINE_DESC_LEN);
				
				/* GET TASK */
				int key_task=query.value(fieldName_toPos.value("id_task")).toInt();
				
				
				t = new Task();
				t->data.task_pid=query.value(fieldName_toPos.value("task_pid")).toInt();
				t->data.status=query.value(fieldName_toPos.value("status")).toInt();
				c_qstrncpy(t->data.task_desc,qPrintable(query.value(fieldName_toPos.value("task_desc")).toString()),PIPELINE_TASK_DESC_LEN);
				c_qstrncpy(t->data.task_exe,qPrintable(query.value(fieldName_toPos.value("task_exe")).toString()),PIPELINE_TASK_EXE_LEN);
				t->data.id_error=query.value(fieldName_toPos.value("id_error")).toInt();
				/* END GET TASK */
				
				pipeline->data.tList=new taskList();
				pipeline->data.tList->insert(key_task,t);
				
				ListPipeLine.insert(key,pipeline);
			}
			
			
		}
		noDbError=true;
	}
	catch ( A_DBException & de ) 
	{
		noDbError=false;
		lout << de.preface().toLatin1()  << de.explain().toLatin1()  << endl;
	}
	
	return noDbError;  
	
} /* getPipeLine */


void ApiDB_Dispatcher::load()
{
	releasePipeLine();
	releaseUsers();
	
	bool dbConnect = isConnect();
	
	if ( dbConnect == false ) 
	{
		dbConnect = openDB(strHOSTNAME,strPORT,strDBNAME,strUSER,strPSWD);
	}
	
	if(dbConnect==true)
	{
		getPipeLine();
		getStatusLib();
		getErrorLib();
		getUsers();
#ifdef DEBUG_APIDB_DISPATCHER_DEBUG
 		debug();
#endif
		closeDB();
	}
} /* load */

pipeLineList *ApiDB_Dispatcher::getPipeLineList()
{
    return &ListPipeLine;
} /* getPipeLineList */

int ApiDB_Dispatcher::getTaskID(int id_pipeline,int i)
{
	int key=id_pipeline;
	int task_id=-1;	
	pipeLineList_it it_pipeLineList = ListPipeLine.find(key);
	
	if(it_pipeLineList != ListPipeLine.end() ) /* key found!!!! */
	{
		QList<int> keys=it_pipeLineList.value()->data.tList->keys();
		task_id=keys.at(i);
	}
	
	return task_id;
} /* getTaskID */

int ApiDB_Dispatcher::getTaskSTATUS(int id_pipeline,int i)
{
	int key=id_pipeline;
	int task_status=-1;	
	pipeLineList_it it_pipeLineList = ListPipeLine.find(key);
	
	if(it_pipeLineList != ListPipeLine.end() ) /* key found!!!! */
	{
		QList<Task*> t=it_pipeLineList.value()->data.tList->values();
		task_status=t.at(i)->data.status;
	}
	
	return task_status;
} /* getTaskSTATUS */

int ApiDB_Dispatcher::getTaskERROR(int id_pipeline,int i)
{
	int key=id_pipeline;
	int task_id_error=-1;	
	pipeLineList_it it_pipeLineList = ListPipeLine.find(key);
	
	if(it_pipeLineList != ListPipeLine.end() ) /* key found!!!! */
	{
		QList<Task*> t=it_pipeLineList.value()->data.tList->values();
		task_id_error=t.at(i)->data.id_error;
	}
	
	return task_id_error;
} /* getTaskERROR */

int ApiDB_Dispatcher::getTaskPID(int id_pipeline,int i)
{
	int key=id_pipeline;
	int task_pid=-1;	
	pipeLineList_it it_pipeLineList = ListPipeLine.find(key);
	
	if(it_pipeLineList != ListPipeLine.end() ) /* key found!!!! */
	{
		QList<Task*> t=it_pipeLineList.value()->data.tList->values();
		task_pid=t.at(i)->data.task_pid;
	}
	
	return task_pid;
} /* getTaskPID */


int ApiDB_Dispatcher::getTaskSize(int id_pipeline)
{
	int key=id_pipeline;
	int task_size=-1;	
	pipeLineList_it it_pipeLineList = ListPipeLine.find(key);
	
	if(it_pipeLineList != ListPipeLine.end() ) /* key found!!!! */
	{
		task_size=it_pipeLineList.value()->data.tList->size();
	}
	
	return task_size;
} /* getTaskSize */

QString ApiDB_Dispatcher::getUserNAME(int id_user)
{
	int key=id_user;
	QString descr;
	
	userList_it it_userList = UserList.find(key);
	
	if(it_userList != UserList.end() ) /* key found!!!! */
	{
		descr=it_userList.value()->data.name;
	}
	else
	{
		descr="Unknown";
	}
	
	return descr;
} /* getUserNAME */

QString ApiDB_Dispatcher::getUserLOGIN(int id_user)
{
	int key=id_user;
	QString descr;
	
	userList_it it_userList = UserList.find(key);
	
	if(it_userList != UserList.end() ) /* key found!!!! */
	{
		descr=it_userList.value()->data.login;
	}
	else
	{
		descr="Unknown";
	}
	
	return descr;
} /* getUserLOGIN */

QString ApiDB_Dispatcher::getUserDESC(int id_user)
{
	int key=id_user;
	QString descr;
	
	userList_it it_userList = UserList.find(key);
	
	if(it_userList != UserList.end() ) /* key found!!!! */
	{
		descr=it_userList.value()->data.desc;
	}
	else
	{
		descr="Unknown";
	}
	
	return descr;
} /* getUserDESC */

int ApiDB_Dispatcher::getPipeLineID(int i)
{
    QList<int> keys=ListPipeLine.keys();
    return keys.at(i);
} /* getPipeLineID */

QString ApiDB_Dispatcher::getPipeLineDESC(int i)
{
    QList<PipeLine*> pl=ListPipeLine.values();
    QString description=QString(pl.at(i)->data.pipeline_desc);
    return description;
} /* getPipeLineDESC */

int ApiDB_Dispatcher::getPipeLineID_USER(int i)
{
    QList<PipeLine*> pl=ListPipeLine.values();
    int id_user=pl.at(i)->data.id_user;
    return id_user;
} /* getPipeLineID_USER */

QString ApiDB_Dispatcher::getTaskDESC(int id_pipeline,int i)
{
    int key=id_pipeline;
    QString description="";	
    pipeLineList_it it_pipeLineList = ListPipeLine.find(key);
    
    if(it_pipeLineList != ListPipeLine.end() ) /* key found!!!! */
    {
	    QList<Task*> t=it_pipeLineList.value()->data.tList->values();
	    description=QString(t.at(i)->data.task_desc);
    }
    
    return description;
} /* getTaskDESC */

QString ApiDB_Dispatcher::getTaskEXE(int id_pipeline,int i)
{
    int key=id_pipeline;
    QString task_exe="";	
    pipeLineList_it it_pipeLineList = ListPipeLine.find(key);
    
    if(it_pipeLineList != ListPipeLine.end() ) /* key found!!!! */
    {
	    QList<Task*> t=it_pipeLineList.value()->data.tList->values();
	    task_exe=QString(t.at(i)->data.task_exe);
    }
    
    return task_exe;
} /* getTaskEXE */

int ApiDB_Dispatcher::getPipeLineSize()
{
    return ListPipeLine.size();
} /* getPipeLineSize */

bool ApiDB_Dispatcher::startTask(int id_user,int id_pipeline,int id_task,int *newPid)
{
    int key_pipeline=id_pipeline;
    int key_task=id_task;
    bool noError=false;
    
    pipeLineList_it it_pipeLineList = ListPipeLine.find(key_pipeline);
    if(it_pipeLineList != ListPipeLine.end() ) /* pipeline found!!!! */
    {
	taskList_it it_taskList =it_pipeLineList.value()->data.tList->find(key_task);
	if(it_taskList != it_pipeLineList.value()->data.tList->end() ) /* task found!!!! */
	{
	    QString exe_name=it_taskList.value()->data.task_exe;
	    QString program=path_exe + exe_name;
	    it_taskList.value()->data.myProcess=new QProcess(this);
	    it_taskList.value()->data.myProcess->setProgram(program);
	    it_taskList.value()->data.myProcess->start();
	    
	    // Wait for it to start
	    if(it_taskList.value()->data.myProcess->waitForStarted()==false)
	    {
		  noError=false;
	    }
	    else
	    {
	    	  noError=true; 
		  int pid=it_taskList.value()->data.myProcess->pid();
		  *newPid=pid;
		  setTaskPID(id_user,id_pipeline,id_task,pid);
	    }
	}
	else
	{
	    noError=false;
	}
    }
    else
    {
	noError=false;
    }
    
    return noError;
} /* startTask */

bool ApiDB_Dispatcher::setTaskLASTSTART(int id_user,int id_pipeline,int id_task,QDateTime last_start)
{
	method ( "setTaskLASTSTART(ApiDB_Dispatcher): " );	
	
	bool dbConnect = isConnect();
	bool noDbError=false;
	
	if ( dbConnect == false ) 
	{
		dbConnect = openDB(strHOSTNAME,strPORT,strDBNAME,strUSER,strPSWD);
	}
	
	if(dbConnect==true)
	{
	      QSqlQuery query ( db );

	      try 
	      {
		      query_exec ( query, "set autocommit=0" );
		      query_exec ( query, "lock tables tab_pipeline write" );

		      /* prepare update */
		      query.prepare ( "UPDATE tab_pipeline SET "
					"last_start=? "
					"WHERE id_user=? " 
					"AND id_pipeline=? "
					"AND id_task=?" );
		      /* bind value */
		      query.addBindValue ( last_start );
		      query.addBindValue ( id_user );
		      query.addBindValue ( id_pipeline );
		      query.addBindValue ( id_task );

		      /* exec query */
		      query_exec ( query );
      
		      /* commit query */
		      query_exec ( query, "commit" );
		      query_exec ( query, "unlock tables" );
		      query_exec ( query, "set autocommit=1" );
	      }
	      catch ( A_DBException & de ) 
	      {
		      lout << de.preface() << de.explain() << endl;
		      query_exec ( query, "rollback" );
		      query_exec ( query, "unlock tables" );
		      query_exec ( query, "set autocommit=1" );
		      noDbError=false;
	      }

	      noDbError=true;
	    
	}
	else
	{
	      noDbError=false;
	}
	
	return noDbError;
} /* setTaskLASTSTART */

bool ApiDB_Dispatcher::setTaskPID(int id_user,int id_pipeline,int id_task,int pid)
{
	method ( "setTaskPID(ApiDB_Dispatcher): " );	
	
	bool dbConnect = isConnect();
	bool noDbError=false;
	
	if ( dbConnect == false ) 
	{
		dbConnect = openDB(strHOSTNAME,strPORT,strDBNAME,strUSER,strPSWD);
	}
	
	if(dbConnect==true)
	{
	      QSqlQuery query ( db );

	      try 
	      {
		      query_exec ( query, "set autocommit=0" );
		      query_exec ( query, "lock tables tab_pipeline write" );

		      /* prepare update */
		      query.prepare ( "UPDATE tab_pipeline SET "
					"task_pid=? "
					"WHERE id_user=? " 
					"AND id_pipeline=? "
					"AND id_task=?" );
		      /* bind value */
		      query.addBindValue ( pid );
		      query.addBindValue ( id_user );
		      query.addBindValue ( id_pipeline );
		      query.addBindValue ( id_task );

		      /* exec query */
		      query_exec ( query );
      
		      /* commit query */
		      query_exec ( query, "commit" );
		      query_exec ( query, "unlock tables" );
		      query_exec ( query, "set autocommit=1" );
	      }
	      catch ( A_DBException & de ) 
	      {
		      lout << de.preface() << de.explain() << endl;
		      query_exec ( query, "rollback" );
		      query_exec ( query, "unlock tables" );
		      query_exec ( query, "set autocommit=1" );
		      noDbError=false;
	      }

	      noDbError=true;
	    
	}
	else
	{
	      noDbError=false;
	}
	
	return noDbError;
} /* setTaskPID */

bool ApiDB_Dispatcher::setTaskERROR(int id_user,int id_pipeline,int id_task,int id_error)
{
	method ( "setTaskERROR(ApiDB_Dispatcher): " );	
	
	bool dbConnect = isConnect();
	bool noDbError=false;
	
	if ( dbConnect == false ) 
	{
		dbConnect = openDB(strHOSTNAME,strPORT,strDBNAME,strUSER,strPSWD);
	}
	
	if(dbConnect==true)
	{
	      QSqlQuery query ( db );

	      try 
	      {
		      query_exec ( query, "set autocommit=0" );
		      query_exec ( query, "lock tables tab_pipeline write" );

		      /* prepare update */
		      query.prepare ( "UPDATE tab_pipeline SET "
					"id_error=? "
					"WHERE id_user=? " 
					"AND id_pipeline=? "
					"AND id_task=?" );
		      /* bind value */
		      query.addBindValue ( id_error );
		      query.addBindValue ( id_user );
		      query.addBindValue ( id_pipeline );
		      query.addBindValue ( id_task );

		      /* exec query */
		      query_exec ( query );
      
		      /* commit query */
		      query_exec ( query, "commit" );
		      query_exec ( query, "unlock tables" );
		      query_exec ( query, "set autocommit=1" );
	      }
	      catch ( A_DBException & de ) 
	      {
		      lout << de.preface() << de.explain() << endl;
		      query_exec ( query, "rollback" );
		      query_exec ( query, "unlock tables" );
		      query_exec ( query, "set autocommit=1" );
		      noDbError=false;
	      }

	      noDbError=true;
	    
	}
	else
	{
	      noDbError=false;
	}
	
	return noDbError;
} /* setTaskERROR */


bool ApiDB_Dispatcher::setTaskSTATUS(int id_user,int id_pipeline,int id_task,int status)
{
	method ( "setTaskSTATUS(ApiDB_Dispatcher): " );	
	
	bool dbConnect = isConnect();
	bool noDbError=false;
	
	if ( dbConnect == false ) 
	{
		dbConnect = openDB(strHOSTNAME,strPORT,strDBNAME,strUSER,strPSWD);
	}
	
	if(dbConnect==true)
	{
	      QSqlQuery query ( db );

	      try 
	      {
		      query_exec ( query, "set autocommit=0" );
		      query_exec ( query, "lock tables tab_pipeline write" );

		      /* prepare update */
		      query.prepare ( "UPDATE tab_pipeline SET "
					"status=? "
					"WHERE id_user=? " 
					"AND id_pipeline=? "
					"AND id_task=?" );
		      /* bind value */
		      query.addBindValue ( status );
		      query.addBindValue ( id_user );
		      query.addBindValue ( id_pipeline );
		      query.addBindValue ( id_task );

		      /* exec query */
		      query_exec ( query );
      
		      /* commit query */
		      query_exec ( query, "commit" );
		      query_exec ( query, "unlock tables" );
		      query_exec ( query, "set autocommit=1" );
	      }
	      catch ( A_DBException & de ) 
	      {
		      lout << de.preface() << de.explain() << endl;
		      query_exec ( query, "rollback" );
		      query_exec ( query, "unlock tables" );
		      query_exec ( query, "set autocommit=1" );
		      noDbError=false;
	      }

	      noDbError=true;
	    
	}
	else
	{
	      noDbError=false;
	}
	
	return noDbError;
} /* setTaskSTATUS */

void ApiDB_Dispatcher::setPathExe(QString str)
{
	path_exe=str;
} /* setPathExe */ 

bool ApiDB_Dispatcher::sanityCheck()
{
	bool dbConnect = isConnect();
	
	if ( dbConnect == false ) 
	{
		dbConnect = openDB(strHOSTNAME,strPORT,strDBNAME,strUSER,strPSWD);
	}
	
	if(dbConnect==true)
	{
		lout << "******** START Sanity Check Report *********************************************************************" << endl;
		lout << " 	Task outdated, older than '" << VALID_DAY <<"' days: " << endl;
		sanityCheckTime();
		lout << " 	Tasks without user: " << endl;
		sanityCheckUser();
		lout << " 	Tasks without pipeline: " << endl;
		sanityCheckPipeLine();
		lout << "******** END Sanity Check Report ***********************************************************************" << endl;
		return _OK;
	}
	
	return _NOT_OK;
	
} /* sanityCheck */

bool ApiDB_Dispatcher::sanityCheckTime()
{
	bool noDbError=false;
	
	QDateTime dateTime=QDateTime::currentDateTime();
	dateTime=dateTime.addDays(-VALID_DAY);
	
	
	QString strFieldName="";
	QString tableName="tab_pipeline";
	QString fieldName[]={"id_user","id_pipeline","id_task","pipeline_desc","status","task_desc","task_exe","task_pid","creation_date",""};
	QString strWhere="creation_date < '"+dateTime.toString("yyyy-MM-dd hh:mm:ss")+"'";
	QString strOrderBy="id_pipeline";
	
	QMap<QString, int> fieldName_toPos;
	
	int i=0;
	while(fieldName[i]!="")
	{
		strFieldName+=fieldName[i];
		strFieldName+=",";
		fieldName_toPos.insert ( fieldName[i], i );
		++i;
	}
	
	strFieldName=strFieldName.mid(0,strFieldName.size()-1); // remove , at the end string
	
	strSelect="SELECT "+strFieldName;
	strSelect+=" FROM "+tableName;
	strSelect+=" WHERE "+strWhere;
	strSelect+=" ORDER BY "+strOrderBy;
	
#ifdef DEBUG_APIDB_DISPATCHER_SANITY_CHECK_TIME		
	lout << strSelect.toLatin1() << endl;
#endif	
	try {
		
		QSqlQuery query(db);
		query.prepare( strSelect );
		query_exec( query );
		
		while ( query.next() ) 
		{	
			int id_user = query.value(fieldName_toPos.value("id_user")).toInt();
			int id_pipeline = query.value(fieldName_toPos.value("id_pipeline")).toInt();
			QString desc_pipeline = query.value(fieldName_toPos.value("pipeline_desc")).toString();
			int id_task=query.value(fieldName_toPos.value("id_task")).toInt();
			QString task_desc=query.value(fieldName_toPos.value("task_desc")).toString();
			QString task_exe=query.value(fieldName_toPos.value("task_exe")).toString();
			int status=query.value(fieldName_toPos.value("status")).toInt();
			QDateTime last_start=query.value(fieldName_toPos.value("creation_date")).toDateTime();
			
			lout << " 		" << desc_pipeline
			  << "(" << id_pipeline << ")-> User:'"
			  <<  getUserNAME(id_user)
			  << "'  Task:'" << task_desc
			  << "(" << id_task << ")"
			  << "'  Status:'" << getStatus(status) 
			  << "'  Crated:'" 
			  << last_start.toString("yyyy-MM-dd hh:mm:ss")
			  << "'"
			  << endl;
			  
			  
			  QString strDelete;
			  QList<QString> listTable;
			  
			  strDelete="DELETE from "+tableName+" WHERE "+strWhere;
			  listTable.clear();
			  listTable.append(tableName);
			  deleteRecordInTable(listTable,strDelete);
			  
			  tableName="tab_task_param_query";
			  listTable.clear();
			  listTable.append(tableName);
			  strDelete="DELETE from "+tableName+" WHERE id_user="+QString::number(id_user)+" AND id_pipeline="+QString::number(id_pipeline)+" AND id_task="+QString::number(id_task);
			  deleteRecordInTable(listTable,strDelete);
			  
			  tableName="tab_task_param_root";
			  listTable.clear();
			  listTable.append(tableName);
			  strDelete="DELETE from "+tableName+" WHERE id_user="+QString::number(id_user)+" AND id_pipeline="+QString::number(id_pipeline)+" AND id_task="+QString::number(id_task);
			  deleteRecordInTable(listTable,strDelete);
		}
		noDbError=true;
	}
	catch ( A_DBException & de ) 
	{
		noDbError=false;
		lout << de.preface().toLatin1()  << de.explain().toLatin1()  << endl;
	}
	
	return noDbError;  
} /* sanityCheckTime */

bool ApiDB_Dispatcher::sanityCheckUser()
{
	bool noDbError=false;
	
	
	QString strFieldName="";
	QString tableName="tab_pipeline";
	QString fieldName[]={"id_user","id_pipeline","id_task","pipeline_desc","status","task_desc","task_exe","task_pid","creation_date",""};
	QString strWhere="id_user not in (select id_user from tab_users)";
	QString strOrderBy="id_pipeline";
	
	QMap<QString, int> fieldName_toPos;
	
	int i=0;
	while(fieldName[i]!="")
	{
		strFieldName+=fieldName[i];
		strFieldName+=",";
		fieldName_toPos.insert ( fieldName[i], i );
		++i;
	}
	
	strFieldName=strFieldName.mid(0,strFieldName.size()-1); // remove , at the end string
	
	strSelect="SELECT "+strFieldName;
	strSelect+=" FROM "+tableName;
	strSelect+=" WHERE "+strWhere;
	strSelect+=" ORDER BY "+strOrderBy;
	
#ifdef DEBUG_APIDB_DISPATCHER_SANITY_CHECK_USER		
	lout << strSelect.toLatin1() << endl;
#endif	
	try {
		
		QSqlQuery query(db);
		query.prepare( strSelect );
		query_exec( query );
		
		while ( query.next() ) 
		{	
			int id_user = query.value(fieldName_toPos.value("id_user")).toInt();
			int id_pipeline = query.value(fieldName_toPos.value("id_pipeline")).toInt();
			QString desc_pipeline = query.value(fieldName_toPos.value("pipeline_desc")).toString();
			int id_task=query.value(fieldName_toPos.value("id_task")).toInt();
			QString task_desc=query.value(fieldName_toPos.value("task_desc")).toString();
			QString task_exe=query.value(fieldName_toPos.value("task_exe")).toString();
			int status=query.value(fieldName_toPos.value("status")).toInt();
			QDateTime last_start=query.value(fieldName_toPos.value("creation_date")).toDateTime();
			
			lout << " 		" << desc_pipeline
			  << "(" << id_pipeline << ")-> User:'"
			  <<  getUserNAME(id_user)
			  << "'  Task:'" << task_desc
			  << "(" << id_task << ")"
			  << "'  Status:'" << getStatus(status) 
			  << "'  Crated:'" 
			  << last_start.toString("yyyy-MM-dd hh:mm:ss")
			  << "'"
			  << endl;
			  
			  
			  /*QString strDelete;
			  QList<QString> listTable;
			  
			  strDelete="DELETE from "+tableName+" WHERE "+strWhere;
			  listTable.append(tableName);
			  listTable.append("tab_users");
			  deleteRecordInTable(listTable,strDelete);
			  
			  tableName="tab_task_param_query";
			  listTable.clear();
			  listTable.append(tableName);
			  strDelete="DELETE from "+tableName+" WHERE id_user="+QString::number(id_user)+" AND id_pipeline="+QString::number(id_pipeline)+" AND id_task="+QString::number(id_task);
			  deleteRecordInTable(listTable,strDelete);
			  
			  tableName="tab_task_param_root";
			  listTable.clear();
			  listTable.append(tableName);
			  strDelete="DELETE from "+tableName+" WHERE id_user="+QString::number(id_user)+" AND id_pipeline="+QString::number(id_pipeline)+" AND id_task="+QString::number(id_task);
			  deleteRecordInTable(listTable,strDelete);*/
			  
			  setTaskERROR(id_user,id_pipeline,id_task,1);
		}
		noDbError=true;
	}
	catch ( A_DBException & de ) 
	{
		noDbError=false;
		lout << de.preface().toLatin1()  << de.explain().toLatin1()  << endl;
	}
	
	return noDbError; 
} /* sanityCheckUser */

bool ApiDB_Dispatcher::sanityCheckPipeLine()
{
	bool noDbError=false;
	return noDbError; 
} /* sanityCheckPipeLine */

bool ApiDB_Dispatcher::deleteRecordInTable ( QList<QString> listTable, const QString strDelete )
{
	method ( "deleteRecordInTable(" + strDelete + ")" );

	bool dbConnect = isConnect();
	bool noDbError=false;
	
#ifdef DEBUG_APIDB_DISPATCHER_DELETE
	lout << strDelete << endl;
#endif	

	QString strLockTables="lock tables ";
	for(int i=0;i<listTable.size();i++)
	{
	    strLockTables += listTable.at(i)+ " write";
	    if(i<listTable.size()-1)
	    {
	      strLockTables+=", ";
	    }
	}
		  
	if ( dbConnect == false ) 
	{
		dbConnect = openDB(strHOSTNAME,strPORT,strDBNAME,strUSER,strPSWD);
	}
	
	if(dbConnect==true)
	{
		QSqlQuery query ( db );
		
		try {
		  
			query_exec ( query, "set autocommit=0" );
			query_exec ( query, strLockTables );
			
			query.prepare ( strDelete );
			
			/* exec query */
			query_exec ( query );
			
			/* commit query */
			query_exec ( query, "commit" );
			query_exec ( query, "unlock tables" );
			query_exec ( query, "set autocommit=1" );
		      
		}
		catch ( A_DBException & de ) 
		{
			lout << de.preface() << de.explain() << endl;
			query_exec ( query, "rollback" );
			query_exec ( query, "unlock tables" );
			query_exec ( query, "set autocommit=1" );
			noDbError=false;
		}
		
		noDbError=true;
	}
	else
	{
	      noDbError=false;
	}
	
	return noDbError;
} /* deleteRecordInTable */