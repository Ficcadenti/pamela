/* My class includes */
#include "pamelaroot.h"

AppLogger *AppLoggerStream;

int main (int argc, char *argv[])
{
    int myPid;
    char *fname=NULL, *envptr=NULL;

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


    /* Environment PamelaRoot_Test_Env*/
    
    ConfigParser cnfparser;
    QString config_name	= cnfparser.locateFile(QString(fname),StoreNode::myExeName());
    QString LOG_NAME 	= cnfparser.parTxtGetValue("LOG_NAME", "PamelaRoot_Test_Env", config_name.toStdString().c_str());
    QString LOG_PATH 	= cnfparser.parTxtGetValue("LOG_PATH", "PamelaRoot_Test_Env", config_name.toStdString().c_str());

    AppLogger::setLogPath(LOG_PATH);
    AppLogger::setLogFileName(LOG_NAME);
    AppLoggerStream = new AppLogger();

    QDateTime dtStart=QDateTime::currentDateTime();
    lout << "Elaboration start at: " << dtStart.toString("dd-MM-yy hh:mm:ss") << endl;
    
    lout << "Configuration file = " << config_name << endl;
	
    lout << "PamelaRoot_Test_Env" << endl;
    lout << " - LOG_NAME         = " << LOG_NAME << endl;
    lout << " - LOG_PATH         = " << LOG_PATH << endl;
      
    if (argc>1)
    {
	QString param1=QString(argv[1]);
	if(param1.toUpper()=="-PID")
	{
	    myPid=QString(argv[2]).toInt();
	}
    }
    else
    {
	    myPid=getpid();
    }
    
    
    MongoDB_test myTask(config_name,&cnfparser);
    myTask.load(myPid); 		/* Create config and select statement for task whit actual pid*/
    myTask.run(); 			/* Run task and generate root file*/
    
    
    QDateTime dtStop=QDateTime::currentDateTime();
    lout << "Elaboration stop at: " << dtStop.toString("dd-MM-yy hh:mm:ss")  << endl;
    lout << "Elapsed time: " << dtStart.secsTo(dtStop) << endl;
    
    return 0;
}
