/*
#  MODULE DESCRIPTION:
#  dispatcher.cpp
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

#include "dispatcher.h"

#include <QtCore/QDir>
#include <QtCore/QFile>
#include <QtCore/QFileInfo>
#include <QtCore/QFileInfoList>
#include <QtCore/QFileInfoListIterator>


AppLogger *AppLoggerStream;
static QString strDtOld,strDtCurrent;

bool dayIsChanged()
{
    QDateTime dt = QDateTime::currentDateTime();
    strDtCurrent=dt.toString("yyyyMMdd");
    
    if(strDtCurrent==strDtOld)
    {
	  return false; /* No change DAY*/
    }
    else
    {
	  dt = QDateTime::currentDateTime();
	  strDtOld=dt.toString("yyyyMMdd");
	  
	  return true; /* Day changed*/
    }
}

bool clearLog(QString LOG_PATH,QString LOG_NAME,QString LOG_CLEAR_GG)
{
	bool flag = true;	
	QDateTime dtCurrent,dtCreatedFile,dtClearTime;
	
	dtCurrent = QDateTime::currentDateTime();
	dtClearTime=dtCurrent.addDays(-(LOG_CLEAR_GG.toInt()));

	lout << dtCurrent.toString("yyyy-MM-dd hh:mm:ss") << endl;
	lout << dtClearTime.toString("yyyy-MM-dd hh:mm:ss") << endl;
	lout << "     Delete '"+LOG_PATH+"*"+LOG_NAME+"' files outdated, older than '" << LOG_CLEAR_GG <<"' days." << endl;
	
	QDir dir = QDir::root();
	QStringList filters;
	filters << "*"+LOG_NAME;
	
	if ( !dir.cd ( LOG_PATH ) ) 
	{
		lout << "Error on file system" << endl;
		flag=false;
	}
	else 
	{
		flag=true;
		
		dir.setFilter ( QDir::Files );
		dir.setNameFilters(filters);
		dir.setSorting ( QDir::Size | QDir::Reversed );

		QFileInfoList list = dir.entryInfoList();
		QFileInfoList::iterator it;
		QFileInfo fi;

		for ( it = list.begin(); it != list.end(); ++it ) 
		{
			fi = (*it);
			QDateTime dtCreatedFile=fi.created();
			if(dtCreatedFile<dtClearTime)
			{
			    
			    if( dir.remove(fi.fileName()) )
			    {
				  lout << "     Remove '"  <<  fi.fileName() << "'" << endl;
			    }
			    else
			    {
				  lout << "     ERROR Remove '"  <<  fi.fileName() << "'" << endl;
				  flag=true;
			    }
			}
		}
		
	}
	
	return flag;
	 
}

int main (int   argc, char *argv[])
{
	bool 		 dbConnect;
	int 		 newPid;
	ApiDB_Dispatcher apidb;	
	char 		 *fname=NULL;
	char 		 *envptr=NULL;
	
	
	/* Initialize date */
	QDateTime dt = QDateTime::currentDateTime();
	strDtCurrent=dt.toString("yyyyMMdd");
	strDtOld=strDtCurrent;
	
	//QCoreApplication a(argc, argv);
	
	if ((envptr = getenv(PAMELA_RES)) == (char *)0) 
	{
		cout << "Unavailable PAMELA configuration path " << PAMELA_RES << endl;
		cout << "Setenv: PAMELA_DIR to pamela path, " << endl;
		cout << "        PAMELA_RES to $PAMELA_DIR/resources. " << PAMELA_RES << endl;
		return 1;
	}
	else
	{
		fname = new char [strlen(envptr) + strlen(PAMELA_CONFIG_FILE) + 2];
		strcpy(fname, envptr);
		strcat(fname, "/");
		strcat(fname, PAMELA_CONFIG_FILE);
		cout << "PAMELA Config File: [" << fname << "]" << endl;
	}
	
	
	ConfigParser cnfparser;
	QString config_name		= cnfparser.locateFile(QString(fname),StoreNode::myExeName());
	
	/* Environment Dispatcher_Env*/
	QString LOG_NAME 		= cnfparser.parTxtGetValue("LOG_NAME", "Dispatcher_Env", config_name.toStdString().c_str());
	QString LOG_PATH 		= cnfparser.parTxtGetValue("LOG_PATH", "Dispatcher_Env", config_name.toStdString().c_str());
	QString LOG_CLEAR_GG 		= cnfparser.parTxtGetValue("LOG_CLEAR_GG", "Dispatcher_Env", config_name.toStdString().c_str());
	QString PAMELA_EXE_PATH 	= cnfparser.parTxtGetValue("PAMELA_EXE_PATH", "Dispatcher_Env", config_name.toStdString().c_str());
	int SLEEP_DISPATCHER_PIELINE 	= QString(cnfparser.parTxtGetValue("SLEEP_DISPATCHER_PIELINE", "Dispatcher_Env", config_name.toStdString().c_str())).toInt();
	int SLEEP_DISPATCHER_TASK 	= QString(cnfparser.parTxtGetValue("SLEEP_DISPATCHER_TASK", "Dispatcher_Env", config_name.toStdString().c_str())).toInt();
	
	/* Setup LOG and APIDB */
	apidb.setPathExe(PAMELA_EXE_PATH);
	AppLogger::setLogPath(LOG_PATH);
	AppLogger::setLogFileName(LOG_NAME);
	AppLoggerStream = new AppLogger();
	
	/* Environment MySql_Env*/
	QString DB_HOSTNAME 	= cnfparser.parTxtGetValue("DB_HOSTNAME", "MySql_Env", config_name.toStdString().c_str());
	QString DB_PORT 	= cnfparser.parTxtGetValue("DB_PORT", "MySql_Env", config_name.toStdString().c_str());
	QString DB_NAME 	= cnfparser.parTxtGetValue("DB_NAME", "MySql_Env", config_name.toStdString().c_str());
	QString DB_LOGIN 	= cnfparser.parTxtGetValue("DB_LOGIN", "MySql_Env", config_name.toStdString().c_str());
	QString DB_PASS 	= cnfparser.parTxtGetValue("DB_PASS", "MySql_Env", config_name.toStdString().c_str());

	/* Print All Environment */
	lout << "Configuration file = " << config_name << endl;
	lout << "Dispatcher_Env" << endl;
	lout << " - LOG_NAME                 = " << LOG_NAME << endl;
	lout << " - LOG_PATH                 = " << LOG_PATH << endl;
	lout << " - LOG_CLEAR_GG             = " << LOG_CLEAR_GG << endl;
	lout << " - PAMELA_EXE_PATH          = " << PAMELA_EXE_PATH << endl;
	lout << " - SLEEP_DISPATCHER_PIELINE = " << SLEEP_DISPATCHER_PIELINE << endl;
	lout << " - SLEEP_DISPATCHER_TASK    = " << SLEEP_DISPATCHER_TASK << endl;
	lout << "MySql_Env" << endl;
	lout << " - DB_HOSTNAME              = " << DB_HOSTNAME << endl;
	lout << " - DB_PORT                  = " << DB_PORT << endl;
	lout << " - DB_NAME                  = " << DB_NAME << endl;
	lout << " - DB_PASS                  = " << DB_PASS << endl;
	lout << " - DB_LOGIN                 = " << DB_LOGIN << endl;
	
	
 	/* Try to Conncet MySQL DB */
 	dbConnect = apidb.isConnect();
	if ( dbConnect == false ) {
		dbConnect = apidb.openDB ( DB_HOSTNAME,DB_PORT, DB_NAME, DB_LOGIN, DB_PASS );
	}

	if ( dbConnect == true ) 
	{
		lout << "Connect to DB." << endl;
	}
	else 
	{
		lout << "Unable to DB connect." << endl;
	}
	
	while(true)
	{
	    apidb.load();
	    
	    if(dayIsChanged()==true) /* Check change day */
	    {
		    lout << "Change Day: execute SanityCheck adn ClearLog." << endl;
		    apidb.sanityCheck();
 		    clearLog(LOG_PATH,LOG_NAME,LOG_CLEAR_GG);
	    }
	    
	    for ( int i=0;i<apidb.getPipeLineSize();i++ ) /* Loop PipeLine */
	    {
		int id_pl=apidb.getPipeLineID(i);
		int id_user=apidb.getPipeLineID_USER(i);

		lout << "START PipeLine(id=" 
			    << id_pl 
			    << ",desc=" 
			    << apidb.getPipeLineDESC(i) 
			    << ")  User(" 
			    << id_user
			    << ","
			    << apidb.getUserNAME(id_user)
			    << ")"
			    << endl;
			    
		for ( int j=0;j<apidb.getTaskSize(id_pl);j++ ) /* Loop Task in PipeLine */
		{
		      int id_task  = apidb.getTaskID(id_pl,j) ;
		      int status   = apidb.getTaskSTATUS(id_pl,j);
		      int id_error = apidb.getTaskERROR(id_pl,j);
		      
		      if((status==TO_BE_SUBMITTED)&&(id_error==TASK_WITHOUT_ERROR))
		      {
			  lout <<"      ...Staring Task(id=" 
			    << id_task
			    << ",desc=" 
			    << apidb.getTaskDESC(id_pl,j)
			    << ",exe="
			    << apidb.getTaskEXE(id_pl,j)
			    <<") Status("
			    << apidb.getStatus(status) 
			    << ")" 
			    << endl;
			    
			    
			    bool NoError=apidb.startTask(id_user,id_pl,id_task,&newPid);
			    if(NoError==true)
			    {
				lout << "      ...Started Task(id="
				      << id_task
				      << ",desc=" 
				      << apidb.getTaskDESC(id_pl,j)
				      << ",exe="
				      << apidb.getTaskEXE(id_pl,j)
				      << ") Status(Submitted" 
				      << ") PID("
				      << newPid
				      << ")"
				      << endl;
				      
				apidb.setTaskSTATUS(id_user,id_pl,id_task,SUBMITTED);
				apidb.setTaskLASTSTART(id_user,id_pl,id_task,QDateTime::currentDateTime());
			    }
			    else
			    {
				lout << "      ...ERROR Starting Task(id="
				      << id_task
				      << ",desc=" 
				      << apidb.getTaskDESC(id_pl,j)
				      << ",exe="
				      << apidb.getTaskEXE(id_pl,j)
				      <<") Status("
				      << apidb.getStatus(status) 
				      << ")" 
				      << endl;
			    }
			    lout << "      ...Wait '"<< SLEEP_DISPATCHER_TASK <<"' sec." << endl;
			    sleep(SLEEP_DISPATCHER_TASK);
		      }
		      else
		      {
			    if(id_error!=TASK_WITHOUT_ERROR)
			    {
				  lout <<"      ...Skiping Task(id=" 
				  << id_task
				  << ",desc=" 
				  << apidb.getTaskDESC(id_pl,j)
				  << ",exe="
				  << apidb.getTaskEXE(id_pl,j)
				  <<") Status("
				  << apidb.getStatus(status) 
				  << ") Error(" 
				  << apidb.getError(id_error) 
				  << ")"
				  << endl;
			    }
			    else
			    {
				  lout <<"      ...Skiping Task(id=" 
				  << id_task
				  << ",desc=" 
				  << apidb.getTaskDESC(id_pl,j)
				  << ",exe="
				  << apidb.getTaskEXE(id_pl,j)
				  <<") Status("
				  << apidb.getStatus(status) 
				  << ")"
				  << endl;
			    }
		      }
		}
		lout << "END Pipeline" << endl;
		lout << endl;
		
	    }
	    lout << "Wait '"<< SLEEP_DISPATCHER_PIELINE << "' sec." << endl;
	    sleep(SLEEP_DISPATCHER_PIELINE);
	}
	
 	apidb.closeDB();
	
	return 0;
}
