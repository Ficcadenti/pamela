#ifndef MongoDB_test__H
#define MongoDB_test_H

// Global Class Includes
#include "pamela_limits.h"
#include "apidb_pamelaroot.h"
#include "applogger.h"
#include "cnfglobals.h"
#include "configparser.h"
#include "task_param_query.h"

// Mongo Class Includes 
#include "mongo/client/dbclient.h"

// Root Class includes
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include "TSystem.h"
#include "TAxis.h"
#include "TGraph.h"
#include "TMultiGraph.h"
#include "TCanvas.h"
#include "TApplication.h"
#include "TImage.h"
#include "TStyle.h"
#include "TPad.h"
#include "TROOT.h"
#include "TColor.h"
#include "TGFrame.h"
#include "TVirtualPad.h"
#include "TRandom.h"
#include "TPolyLine3D.h"
#include "TView.h"
#include "TVirtualViewer3D.h"
#include "TBuffer3D.h"
#include "TBuffer3DTypes.h"
#include "TGeometry.h"
#include "TMath.h"
#include "TFile.h"
#include "THStack.h"


#include <QtCore/qstring.h>

/** Gestione dei grafici root.
  *@short MongoDB_test.
  *@author Raffaele Ficcadenti.
  */

using namespace mongo;

class MongoDB_test {
public:
	
	MongoDB_test(const QString strName,ConfigParser *cnf);
	~MongoDB_test();
	
	bool openDB();
	
	/* Manage global */
	void load(int pid);
	void run();
	BSONObjBuilder *createQuery(taskParamQueryList *paramList);
	
private:
  
	DBClientConnection 	mongodb;
	ApiDB_PamelaRoot	apidb;
	bool 			dbConnect;
	bool 			mongoDbConnect;
	int 			myPid;
	
	
	/* Debug */
	void showParamQuery(taskParamQueryList *paramList);
	
	/* Environment MySql_Env*/
	QString DB_HOSTNAME;
	QString DB_PORT;
	QString DB_NAME;
	QString DB_LOGIN;
	QString DB_PASS;
	
	/* Environment MongoDB_Env*/
	QString MONGODB_HOSTNAME;
	QString MONGODB_PORT;
	QString MONGODB_NAME;
	QString MONGODB_COLLECTION;
	
	/* Environment PamelaRoot_Test_Env */
	QString ROOT_WEB_PATH;
	int SHOW_INTERVAL;

	/* Configuration file */
	ConfigParser *cnfparser;
	QString config_name;
  
};

#endif