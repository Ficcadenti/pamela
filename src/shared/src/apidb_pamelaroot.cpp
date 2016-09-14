/*
#  MODULE DESCRIPTION:
#  apidb_pamelaroot.cpp
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

#include "apidb_pamelaroot.h"
#include "applogger.h"

using namespace std;


void ApiDB_PamelaRoot::releaseTaskParam()
{
	for ( taskParamQueryList_it it_taskParamQueryList = tpqList.begin(); it_taskParamQueryList != tpqList.end(); it_taskParamQueryList++ )
	{
		TaskParamQuery *pl = *it_taskParamQueryList;
		if(pl!=NULL)
		{
			if(pl->data.pList!=NULL)
			{
			    pl->data.pList->clear();
			    delete(pl->data.pList);
			}
			delete (pl);
		}
	}
	tpqList.clear();
}


ApiDB_PamelaRoot::ApiDB_PamelaRoot() : m_connection ( "ApiDB_PamelaRoot" )
{
  
} /* ApiDB_PamelaRoot */

ApiDB_PamelaRoot::~ApiDB_PamelaRoot()
{
	if(isConnect()==true)
	{
		closeDB();
	}
	releaseTaskParam();

} /* ~ApiDB_PamelaRoot */

void ApiDB_PamelaRoot::closeDB()
{
	QString connection;
	connection = db.connectionName();
	db.close();
	db = QSqlDatabase();
	db.removeDatabase ( connection );
} /* closeDB */

QString ApiDB_PamelaRoot::getTaskROOTFILE(int pid)
{
	QString strName="default.root";
	
	QString strFieldName="";
	QString tableName="tab_pipeline";
	QString fieldName[]={"id_pipeline","root_file",""};
	QString strWhere="task_pid="+QString::number(pid);
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

#ifdef DEBUG_APIDB_PAMELAROOT_SELECT	
	lout << strSelect << endl;
#endif
	
	try {
		
		QSqlQuery query(db);
		query.prepare( strSelect );
		query_exec( query );
		
		while ( query.next() ) 
		{	
			strName=query.value(fieldName_toPos.value("root_file")).toString();
		}
	}
	catch ( A_DBException & de ) 
	{
		strName="default.root";
		lout << de.preface().toLatin1()  << de.explain().toLatin1()  << endl;
	}
	
	return strName;  
} /* getTaskROOTFILE */

QString ApiDB_PamelaRoot::getTaskQUERYMONGO(int pid)
{
	QString strQueryMongo="{}";
	
	QString strFieldName="";
	QString tableName="tab_pipeline";
	QString fieldName[]={"id_pipeline","query_mongo",""};
	QString strWhere="task_pid="+QString::number(pid);
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

#ifdef DEBUG_APIDB_PAMELAROOT_SELECT	
	lout << strSelect << endl;
#endif
	
	try {
		
		QSqlQuery query(db);
		query.prepare( strSelect );
		query_exec( query );
		
		while ( query.next() ) 
		{	
			strQueryMongo=query.value(fieldName_toPos.value("query_mongo")).toString();
		}
	}
	catch ( A_DBException & de ) 
	{
		strQueryMongo="{}";
		lout << de.preface().toLatin1()  << de.explain().toLatin1()  << endl;
	}
	
	return strQueryMongo;  
} /* getTaskQUERYMONGO */

QString ApiDB_PamelaRoot::getTaskPNGFILE(int pid)
{
	QString strName="default.png";
	
	QString strFieldName="";
	QString tableName="tab_pipeline";
	QString fieldName[]={"id_pipeline","png_file",""};
	QString strWhere="task_pid="+QString::number(pid);
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

#ifdef DEBUG_APIDB_PAMELAROOT_SELECT	
	lout << strSelect << endl;
#endif
	
	try {
		
		QSqlQuery query(db);
		query.prepare( strSelect );
		query_exec( query );
		
		while ( query.next() ) 
		{	
			strName=query.value(fieldName_toPos.value("png_file")).toString();
		}
		
	}
	catch ( A_DBException & de ) 
	{
		strName="default.png";
		lout << de.preface().toLatin1()  << de.explain().toLatin1()  << endl;
	}
	
	return strName;  
} /* getTaskPNGFILE */

bool ApiDB_PamelaRoot::openDB ( QString hstrHOSTNAME, QString hstrPORT, QString hstrDBNAME, QString hstrUSER, QString hstrPSWD )
{
	bool noDbError = false;
	bool ok;
	
	method ( "openDB(ApiDB_PamelaRoot): " );	

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

void ApiDB_PamelaRoot::setError ( QSqlDatabase &dbError )
{
	last_result_db = dbError.lastError().number();
} /* setError */

bool ApiDB_PamelaRoot::isConnect()
{
	QSqlDatabase db_test = QSqlDatabase::database(m_connection);
// 	lout << "ApiDB_PamelaRoot.isOpen("<< m_connection << ")=" << db_test.isOpen() << endl;	
	return db_test.isOpen();
} /* isConnect */

void ApiDB_PamelaRoot::debug()
{	
	if(StatusList.size()>0)
	{
		lout << "START Status Lib " << endl;
		for ( statusList_it it_statusList = StatusList.begin(); it_statusList != StatusList.end(); it_statusList++ )
		{
		      lout << "  " << it_statusList.key() << "=" << it_statusList.value() << endl; 
		}
		lout << "END Status Lib " << endl;
	}
	
	if(ErrorList.size()>0)
	{
		lout << endl;
		lout << "START Error Lib " << endl;
		for ( errorList_it it_errorList = ErrorList.begin(); it_errorList != ErrorList.end(); it_errorList++ )
		{
		      lout << "  " << it_errorList.key() << "=" << it_errorList.value() << endl; 
		}
		lout << "END Error Lib " << endl;
	}
	
	if(ParamList.size()>0)
	{
		lout << endl;
		lout << "START Param Lib " << ParamList.size() << endl;
		for ( paramList_it it_paramList = ParamList.begin(); it_paramList != ParamList.end(); it_paramList++ )
		{
		      lout << "  " << it_paramList.key() << "=" << it_paramList.value() << endl; 
		}
		lout << "END Param Lib " << endl;
	}
	
	if(TypeList.size()>0)
	{
		lout << endl;
		
		lout << "START Type Lib " << endl;
		for ( typeList_it it_typeList = TypeList.begin(); it_typeList != TypeList.end(); it_typeList++ )
		{
		      lout << "  " << it_typeList.key() << "=" << it_typeList.value() << endl; 
		}
		lout << "END Type Lib " << endl;
	}
	
	if(OperatorList.size()>0)
	{
		lout << endl;
		
		lout << "START Operator Lib " << endl;
		for ( operatorList_it it_operatorList = OperatorList.begin(); it_operatorList != OperatorList.end(); it_operatorList++ )
		{
		      lout << "  " << it_operatorList.key() << "=" << it_operatorList.value() << endl; 
		}
		lout << "END Operator Lib " << endl;
	}
	
	if(tpqList.size()>0)
	{
		lout << endl;
		
		lout << "START QueryParam Lib " << endl;
		for ( taskParamQueryList_it it_taskParamQueryList = tpqList.begin(); it_taskParamQueryList != tpqList.end(); it_taskParamQueryList++ )
		{
		      lout << "id_param   = " << it_taskParamQueryList.key() << endl; 
		      lout << "name_param = " << it_taskParamQueryList.value()->data.name_param << endl;
		      for ( paramQueryList_it it_paramQueryList = it_taskParamQueryList.value()->data.pList->begin(); it_paramQueryList != it_taskParamQueryList.value()->data.pList->end(); it_paramQueryList++ )
		      {
			      ParamQuery* t=(*it_paramQueryList);
			      lout << "  " << "id_operator   = " << t->data.id_operator << endl;
			      lout << "  " << "type_param    = " << t->data.type_param << endl;
			      lout << "  " << "name_operator = " << t->data.name_operator << endl;
			      lout << "  " << "value_param   = " << t->data.value_param << endl;
		      }		      
		}
		lout << "END QueryParam Lib " << endl;
	}
} /* debug */

taskParamQueryList *ApiDB_PamelaRoot::getParamList()
{
	return &tpqList;
}

QString ApiDB_PamelaRoot::getStatus(int status)
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

QString ApiDB_PamelaRoot::getError(int id_error)
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

QString ApiDB_PamelaRoot::getType(int id_type)
{
	QString descr;
	int key=id_type;
	
	typeList_it it_typeList = TypeList.find(key);
			
	if(it_typeList == TypeList.end() ) // key not found!!!!
	{
		descr="Undefined";
	}
	else
	{
		descr=TypeList.value(key);
	}
	  
	return descr;
} /* getType */

QString ApiDB_PamelaRoot::getParam(int id_param)
{
	QString descr;
	int key=id_param;
	
	paramList_it it_paramList = ParamList.find(key);
			
	if(it_paramList == ParamList.end() ) // key not found!!!!
	{
		descr="Undefined";
	}
	else
	{
		descr=ParamList.value(key);
	}
	  
	return descr;
} /* getParam */

QString ApiDB_PamelaRoot::getOperator(int id_operator)
{
	QString descr;
	int key=id_operator;
	
	operatorList_it it_operatorList = OperatorList.find(key);
			
	if(it_operatorList == OperatorList.end() ) // key not found!!!!
	{
		descr="Undefined";
	}
	else
	{
		descr=OperatorList.value(key);
	}
	  
	return descr;
} /* getOperator */

bool ApiDB_PamelaRoot::getParamLib()
{
	method ( "getParamLib(ApiDB_PamelaRoot): " );	
	
	bool noDbError=false;
	
	QString strFieldName="";
	QString tableName="tab_param_lib";
	QString fieldName[]={"id_param","param_name",""};
	QString strWhere="1";
	QString strOrderBy="id_param";
	
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

#ifdef DEBUG_APIDB_PAMELAROOT_SELECT	
	lout << strSelect << endl;
#endif
	
	try {
		
		QSqlQuery query(db);
		query.prepare( strSelect );
		query_exec( query );
		
		while ( query.next() ) 
		{	
			
			int key=query.value(fieldName_toPos.value("id_param")).toInt();
			QString value=query.value(fieldName_toPos.value("param_name")).toString();

 			paramList_it it_paramList = ParamList.find(key);
 			
			if(it_paramList == ParamList.end() ) // key not found!!!!
			{
				ParamList.insert(key,value);
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
} /* getParamLib */

bool ApiDB_PamelaRoot::getTypeLib()
{
	method ( "getTypeLib(ApiDB_PamelaRoot): " );	
	
	bool noDbError=false;
	
	QString strFieldName="";
	QString tableName="tab_type_lib";
	QString fieldName[]={"id_type","type_desc","mongo_type",""};
	QString strWhere="1";
	QString strOrderBy="id_type";
	
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

#ifdef DEBUG_APIDB_PAMELAROOT_SELECT	
	lout << strSelect << endl;
#endif
	
	try {
		
		QSqlQuery query(db);
		query.prepare( strSelect );
		query_exec( query );
		
		while ( query.next() ) 
		{	
			
			int key=query.value(fieldName_toPos.value("id_type")).toInt();
			QString value=query.value(fieldName_toPos.value("mongo_type")).toString();

			if(TypeList.size()==0)
			{
				TypeList.insert(key,value);
			}
			else
			{
				typeList_it it_typeList = TypeList.find(key);
				
				if(it_typeList == TypeList.end() ) // key not found!!!!
				{
					TypeList.insert(key,value);
				}
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
} /* getTypeLib */

bool ApiDB_PamelaRoot::getErrorLib()
{
	method ( "getErrorLib(ApiDB_PamelaRoot): " );	
	
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

#ifdef DEBUG_APIDB_PAMELAROOT_SELECT	
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

bool ApiDB_PamelaRoot::getStatusLib()
{
	method ( "getStatusLib(ApiDB_PamelaRoot): " );	
	
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

#ifdef DEBUG_APIDB_PAMELAROOT_SELECT	
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

bool ApiDB_PamelaRoot::getOperatorLib()
{
	method ( "getOperatorLib(ApiDB_PamelaRoot): " );	
	
	bool noDbError=false;
	
	QString strFieldName="";
	QString tableName="tab_operators_lib";
	QString fieldName[]={"id_opt","mongo_opt",""};
	QString strWhere="1";
	QString strOrderBy="id_opt";
	
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

#ifdef DEBUG_APIDB_PAMELAROOT_SELECT	
	lout << strSelect << endl;
#endif
	
	try {
		
		QSqlQuery query(db);
		query.prepare( strSelect );
		query_exec( query );
		
		while ( query.next() ) 
		{	
			
			int key=query.value(fieldName_toPos.value("id_opt")).toInt();
			QString value=query.value(fieldName_toPos.value("mongo_opt")).toString();
						
 			operatorList_it it_operatorList = OperatorList.find(key);
			
			if(it_operatorList == OperatorList.end() ) // key not found!!!!
			{
				OperatorList.insert(key,value);
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
} /* getOperatorLib */


void ApiDB_PamelaRoot::load()
{
	bool dbConnect = isConnect();
	
	if ( dbConnect == false ) 
	{
		dbConnect = openDB(strHOSTNAME,strPORT,strDBNAME,strUSER,strPSWD);
	}
	
	if(dbConnect==true)
	{
 		getStatusLib();
		getErrorLib();
 		getTypeLib();
		getParamLib();
		getOperatorLib();
		getParamQuery();
#ifdef DEBUG_APIDB_PAMELAROOT_DEBUG
 		debug();
#endif
		closeDB();
	}
} /* load */

bool ApiDB_PamelaRoot::getParamQuery()
{
	method ( "getParamQuery(ApiDB_Dispatcher): " );	
	 
	bool noDbError=false;
	TaskParamQuery *taskParamQuery;
	ParamQuery *param;
	
	QString strFieldName="";
	QString fieldName[]={"b.id_param","b.type_param","b.id_operator","b.value_param",""};	
	QString strWhere="a.task_pid="+QString::number(myPid);
	
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
	
	strSelect= "SELECT "+strFieldName;
	strSelect+=" FROM tab_pipeline a INNER JOIN tab_task_param_query b ";
	strSelect+=" ON a.id_task = b.id_task AND a.id_pipeline = b.id_pipeline AND a.id_user = b.id_user ";
	strSelect+=" WHERE "+strWhere;

#ifdef DEBUG_APIDB_PAMELAROOT_SELECT	
	lout << strSelect << endl;
#endif
	try {
		
		QSqlQuery query(db);
		query.prepare( strSelect );
		query_exec( query );
		
		while ( query.next() ) 
		{	
			int key_param=query.value(fieldName_toPos.value("b.id_param")).toInt();
			
			/* Make new Param */
			param=new ParamQuery();	
			param->data.id_operator=query.value(fieldName_toPos.value("b.id_operator")).toInt();
			param->data.type_param=query.value(fieldName_toPos.value("b.type_param")).toInt();
			c_qstrncpy(param->data.name_operator,qPrintable(getOperator(param->data.id_operator)),OPERATOR_NAME_LEN);
			c_qstrncpy(param->data.value_param,qPrintable(query.value(fieldName_toPos.value("b.value_param")).toString()),PARAM_VALUE_LEN);
			      
			taskParamQueryList_it it_taskParamQueryList = tpqList.find(key_param);
			
			if(it_taskParamQueryList != tpqList.end() ) /* key found!!!! */
			{
				paramQueryList *pl=it_taskParamQueryList.value()->data.pList;
				pl->append(param);
			}
			else /* key not found */
			{
				taskParamQuery = new TaskParamQuery();
				c_qstrncpy(taskParamQuery->data.name_param,qPrintable(getParam(key_param)),PARAM_NAME_LEN);
								
				/* Add value param */
				taskParamQuery->data.pList=new paramQueryList();
				taskParamQuery->data.pList->append(param);
				
				/* Add param to list */
				tpqList.insert(key_param,taskParamQuery);
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


bool ApiDB_PamelaRoot::setTaskERROR(int id_user,int id_pipeline,int id_task,int id_error)
{
	method ( "setTaskERROR(ApiDB_PamelaRoot): " );	
	
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

bool ApiDB_PamelaRoot::setTaskSTATUS(int pid,int status)
{
	method ( "setTaskSTATUS(ApiDB_PamelaRoot): " );	
	
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
					"WHERE task_pid=? ");
		      /* bind value */
		      query.addBindValue ( status );
		      query.addBindValue ( pid );

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


void ApiDB_PamelaRoot::setPid(int pid)
{
	myPid=pid;
} /* setPid */ 


bool ApiDB_PamelaRoot::deleteRecordInTable ( QList<QString> listTable, const QString strDelete )
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

