#include "mongodb_test.h"
#include "applogger.h"


using namespace std;
using namespace mongo;

MongoDB_test::MongoDB_test(const QString strName,ConfigParser *cnf) 
{
    cnfparser=cnf;
    config_name=strName;
    
    /* Environment MySql_Env*/
    DB_HOSTNAME = cnfparser->parTxtGetValue("DB_HOSTNAME", "MySql_Env", config_name.toStdString().c_str());
    DB_PORT 	= cnfparser->parTxtGetValue("DB_PORT", "MySql_Env", config_name.toStdString().c_str());
    DB_NAME 	= cnfparser->parTxtGetValue("DB_NAME", "MySql_Env", config_name.toStdString().c_str());
    DB_LOGIN 	= cnfparser->parTxtGetValue("DB_LOGIN", "MySql_Env", config_name.toStdString().c_str());
    DB_PASS 	= cnfparser->parTxtGetValue("DB_PASS", "MySql_Env", config_name.toStdString().c_str());
    
    lout << "MySql_Env" << endl;
    lout << " - DB_HOSTNAME      = " << DB_HOSTNAME << endl;
    lout << " - DB_PORT          = " << DB_PORT << endl;
    lout << " - DB_NAME          = " << DB_NAME << endl;
    lout << " - DB_PASS          = " << DB_PASS << endl;
    lout << " - DB_LOGIN         = " << DB_LOGIN << endl;
    
    /* Environment MongoDB_Env*/
    MONGODB_HOSTNAME   = cnfparser->parTxtGetValue("DB_HOSTNAME", "MongoDB_Env", config_name.toStdString().c_str());
    MONGODB_PORT       = cnfparser->parTxtGetValue("DB_PORT", "MongoDB_Env", config_name.toStdString().c_str());
    MONGODB_NAME       = cnfparser->parTxtGetValue("DB_NAME", "MongoDB_Env", config_name.toStdString().c_str());
    MONGODB_COLLECTION = cnfparser->parTxtGetValue("DB_COLLECTION", "MongoDB_Env", config_name.toStdString().c_str());
    
    lout << "MongoDB_Env" << endl;
    lout << " - MONGODB_HOSTNAME   = " << MONGODB_HOSTNAME << endl;
    lout << " - MONGODB_PORT       = " << MONGODB_PORT << endl;
    lout << " - MONGODB_NAME       = " << MONGODB_NAME << endl;
    lout << " - MONGODB_COLLECTION = " << MONGODB_COLLECTION << endl;
    
    /* Environment Web_Env */
    ROOT_WEB_PATH = cnfparser->parTxtGetValue("ROOT_WEB_PATH", "Web_Env", config_name.toStdString().c_str());
    lout << "Web_Env" << endl;
    lout << " - ROOT_WEB_PATH   = " << ROOT_WEB_PATH << endl;
    
    /* Environment PamelaRoot_Test_Env */
    SHOW_INTERVAL = QString(cnfparser->parTxtGetValue("SHOW_INTERVAL", "PamelaRoot_Test_Env", config_name.toStdString().c_str())).toInt();
    lout << "PamelaRoot_Test_Env" << endl;
    lout << " - SHOW_INTERVAL   = " << SHOW_INTERVAL << endl;

    
	
} /* MongoDB_test */

MongoDB_test::~MongoDB_test()
{
	
} /* ~MongoDB_test */

void MongoDB_test::load(int pid)
{
	myPid = pid;
	lout << " - PID             = " << myPid << endl;
	
	apidb.setPid(myPid);
	
	dbConnect = apidb.isConnect();
	if ( dbConnect == false ) 
	{
		dbConnect = apidb.openDB ( DB_HOSTNAME,DB_PORT, DB_NAME, DB_LOGIN, DB_PASS );
	}

	if ( dbConnect == true ) 
	{
		lout << "Connect to MySql_DB." << endl;
	}
	else 
	{
		lout << "Unable to MySql_DB connect." << endl;
	}
	
	apidb.load();
} /* load */

bool MongoDB_test::openDB()
{
	bool dbConnect = true;
	
	try 
	{	
		mongodb.connect(MONGODB_HOSTNAME.toStdString().c_str());
		lout  << "Connected to Mongo_DB."<< endl;
		dbConnect=true;
	} 
	catch( const mongo::DBException &e ) 
	{
		lout  << "Connection Error to Mongo_DB: "<< e.what() << endl;
		dbConnect=false;      
	}
	
	return dbConnect;
} /* openDB */

void MongoDB_test::showParamQuery(taskParamQueryList *paramList)
{
	if(paramList->size()>0)
	{
		lout << endl;
		
		lout << "START QueryParam Lib " << endl;
		for ( taskParamQueryList_it it_taskParamQueryList = paramList->begin(); it_taskParamQueryList != paramList->end(); it_taskParamQueryList++ )
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
	
} /* showParamQuery */

BSONObjBuilder *MongoDB_test::createQuery(taskParamQueryList *paramList)
{
	BSONObjBuilder *bld=NULL;
	BSONObjBuilder *inner=NULL;
	
	bld=new BSONObjBuilder();

	for ( taskParamQueryList_it it_taskParamQueryList = paramList->begin(); it_taskParamQueryList != paramList->end(); it_taskParamQueryList++ )
	{
		inner = new BSONObjBuilder(bld->subobjStart( it_taskParamQueryList.value()->data.name_param ));
		for ( paramQueryList_it it_paramQueryList = it_taskParamQueryList.value()->data.pList->begin(); it_paramQueryList != it_taskParamQueryList.value()->data.pList->end(); it_paramQueryList++ )
		{
			ParamQuery* t=(*it_paramQueryList);
			switch(t->data.type_param)
			{
				case 0: /* Int*/
				{
				      inner->append( t->data.name_operator , QString(t->data.value_param).toInt() );
				}break;
				
				case 1: /* Double */
				{
				      inner->append( t->data.name_operator , QString(t->data.value_param).toDouble() );
				}break;
				
				default:
				{
				      lout << "Error, type '"<< t->data.type_param << "' undefined." << endl;
				      bld=NULL;
				}
			}
		}
		inner->done();
	}	  
	
	if(inner!=NULL)
	    delete(inner);
	
	return bld;
} /* createQuery */

void MongoDB_test::run()
{
	bool 	dbConnect	= openDB();
	int 	cont		= 0;
	double 	x		= 0.0;
	double 	y		= 0.0;
	double 	z		= 0.0;
	int bin			= 0;
	QString mongodb_name_str=MONGODB_NAME + "." +MONGODB_COLLECTION;

	if(dbConnect==true)
	{
		taskParamQueryList *paramList=apidb.getParamList();
	      
		if(paramList!=NULL)
		{	
			//if(paramList->size())  /* Make QUERY on MongoDB */
			if(true)
			{
				lout << " Entry on " << mongodb_name_str << " = " << mongodb.count(mongodb_name_str.toStdString().c_str()) << endl;	
				
				//showParamQuery(paramList);
				BSONObjBuilder *queryBuilder=createQuery(paramList);
				
				if(queryBuilder!=NULL)
				{
					/* START MONGODB Elaboration */
					apidb.setTaskSTATUS(myPid,WORKING);
					
					QString png_file=ROOT_WEB_PATH+"/img/"+apidb.getTaskPNGFILE(myPid);
					QString root_file=ROOT_WEB_PATH+"/files/"+apidb.getTaskROOTFILE(myPid);
					
					
					lout << " PNG File  = '" << png_file << "'" << endl;
					lout << " ROOT File = '" << root_file << "'" << endl;
					
					/* Init ROOT Histogram */
					TFile f(root_file.toStdString().c_str(), "RECREATE");
					TCanvas *c1 	= new TCanvas("PamelaRoot Test","A Simple 3dGraph Example",200,10,700,500);
					TH2D* h1 	= new TH2D("Histogram h1","Histogram h1", 360, -180.,180.,180,-90.,90.);
					TH2D* h1_f 	= new TH2D("Histogram h1_f","Histogram h1_f", 360, -180.,180.,180,-90.,90.);
					TH2D* hnorm 	= new TH2D("Histogram hnorm","Normalized", 360, -180.,180.,180,-90.,90.);  
					
					
					BSONObj 	query = queryBuilder->done();
					BSONElement 	field;
					
					/* PER INSERIRE LA QUERY MANUALMENTE, altrimenti commentare la riga*/
					// query=fromjson("{abstime: {$gt: 0.0} }");
					
					/* PRELEVO LA QUERY DIRETTAMENTE DAL DB MySQL (tab_pipeline) */
					query=fromjson(apidb.getTaskQUERYMONGO(myPid).toStdString());
					
					
					lout << " MONGO Query (MySQL-DB) = '" << QString::fromStdString(query.toString()) << "'" << endl;
					
					
					/* START ROOT Elaboration  */
					auto_ptr<DBClientCursor> cursor = mongodb.query(mongodb_name_str.toStdString().c_str(), query);
					while (cursor->more())
					{
						BSONObj p = cursor->next();
						QString str=QString::fromStdString(p.toString());
						//lout << str << endl;
						cont++;
						//if(cont==1) continue;

						field = p["lat"];
						x=(double)field.Number();
						
						field = p["lon"];
						y=(double)field.Number();
						
						field = p["pmtpl0"];
						z=(double)field.Number()/0.06;
						
						bin = h1->FindBin(y,x);
						h1->SetBinContent(bin,z);
						h1_f->Fill(y,x);
						
						if (cont%SHOW_INTERVAL == 0)
						{
						    lout << " Row # " << cont  << " - lat,lon,pmtpl0" << endl;
						    fflush(stdout);
						}
					}
					
					/* Write Histogram on root_file */
					h1->Write();
					h1_f->Write();
					
					/* Elaboration Histogram */
					Int_t nbins = (hnorm->GetNbinsY()+1)*(hnorm->GetNbinsX()+1);
					for(Int_t k = 0; k < nbins; k++)
					{
					    if(h1_f->GetBinContent(k) != 0)
					    {
						hnorm->SetBinContent(k, h1->GetBinContent(k)/h1_f->GetBinContent(k) );
					    }
					}
  
					hnorm->Draw("colz");
					
					/* Write Histogram on root_file */
					hnorm->Write();
					
					/* Write png_file  */
					TImage *img = TImage::Create();
					img->FromPad(c1);
					img->WriteImage(png_file.toStdString().c_str());

					/* Release memory */
					if(c1!=NULL)
					  delete(c1);
					
					if(h1!=NULL)
					  delete(h1);
					
					if(h1_f!=NULL)
					  delete(h1_f);
					
					if(hnorm!=NULL)
					  delete hnorm;
					
					/* Close Root file.*/
					f.Close();
					
					lout << "Record read: " << cont << endl;
					apidb.setTaskSTATUS(myPid,FINISHED);
					
					/* END ROOT Elaboration */
					/* END MONGODB Elaboration */
				}
				else
				{
					lout << "Error, task not runniung." << endl;
				}
				
				if(queryBuilder!=NULL)
					delete(queryBuilder);
			}
			else
			{
			  lout << "parmaList size=0." << endl;
			}
		}
		else
		{
			lout << "parmaList NULL." << endl;
		}
		
	}
} /* run */