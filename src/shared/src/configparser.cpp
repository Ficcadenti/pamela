/***************************************************************************
                          configparser.cpp  -  description
                             -------------------
    begin                : Thu Mar 03 2016
    copyright            : (C) 2016 by ASI
    author               : Ficcadenti Raffaele
    email                : ficcadenti.raffaele@gmail.com
 ***************************************************************************/

/***[ Module Description ]**************************************************
 *
 *
 *
 *
 *
 *
 ***************************************************************************/

/***[ History ]*************************************************************
  ===            LETTURA DATI DI CONFIGURAZIONE DA FILE ESTERNI            ===
  ===                                                                      ===
  === Le due funzioni seguenti estraggono valori da file (configurazioni)  ===
  === esterni. I dati sono organizzati in sezioni e le sezioni includono   ===
  === valori di due tipi: liste e coppie argomento/valore.                 ===
  ===                                                                      ===
  === Regole sintattiche:                                                  ===
  === .1 - I commenti sono identificati dal token '#'                      ===
  === .2 - Le righe blank sono ammesse ed ignorate                         ===
  === .3 - Le sezioni sono identificate da un token racchiuso tra parente- ===
  ===      si quadre (Es.: [My_Section]) e privo di spazi                  ===
  === .4 - I valori del tipo lista sono stringhe semplici. Spazi in testa  ===
  ===      o in coda vengono eliminati                                     ===
  === .5 - I valori del tipo coppia argomento/valore sono separati da un   ===
  ===      segno di '='. Nel token argomento non sono ammessi spazi.       ===
  ===      Nella sezione valore gli spazi in testa e in coda vengono       ===
  ===      eliminati.                                                      ===
  === .6 - Tenere presente che gli array vengono da aree malloced,         ===
  ===      pertanto dopo l'uso possono (dovrebbero) essere liberati con    ===
  ===      una free().                                                     ===
  ===                                                                      ===
  ===  ESEMPIO:                                                            ===
  ===                                                                      ===
  ===  # This is an example                                                ===
  ===                                                                      ===
  ===  [Section_One]                                                       ===
  ===                                                                      ===
  ===  An argument line.                                                   ===
  ===  Another argument line.                                              ===
  ===                                                                      ===
  ===  [Section_Two]                                                       ===
  ===                                                                      ===
  ===  Arg_id_One = a value for the first argument                         ===
  ===  Arg_id_Two = a value                                                ===
  ===                                                                      ===
 * - Date - - By ---------------- - What -----------------------------------
 ***************************************************************************/

#include "configparser.h"
#include "applogger.h"

ConfigParser::ConfigParser(){
	txtDelimiters = parDELIMITERS;
}
ConfigParser::~ConfigParser(){
}


/* allocate and returns a string initialized with path to standard PAMELA (graphics) configuration file */

char * ConfigParser::getStandardGraphicConfigFilename()
{
	char *fname=NULL, *envptr=NULL;
	
	if ((envptr = getenv(COMMON_DIRNAME_ENV)) == (char *)0) {
		if ((envptr = getenv(ALTERNATE_DIRNAME_ENV)) == (char *)0) {
			lout << "Unavailable PAMELA configuration path " << COMMON_DIRNAME_ENV << " or " << ALTERNATE_DIRNAME_ENV << endl;
			return(envptr);
		}
	}	
	fname = new char [strlen(envptr) + strlen(COMMON_CONFIG_FILE) + 2];
	strcpy(fname, envptr);
	strcat(fname, "/");
	strcat(fname, COMMON_CONFIG_FILE);
	return(fname);
}

QString ConfigParser::locateFile(QString name, QString exename)
{
	if (name.mid(0,1) == "~") 
	{				// home relative path
		char * homedir = getenv("HOME");
		if (homedir) 
		{
			name.replace(0,1,homedir);
			return name;
		}
	}
	
	if (name.mid(0,1) == "/" || name.mid(0,2) == "./")	// absolute path
		return name;
	
	if (QFile::exists(name))				// try local, no path
		return name;
	
	char d[1024];
	int slashpos = exename.indexOf('/');			// try with executable name
	if (slashpos < 0) {					// no path in exe, try cwd
		if (QFile::exists(getcwd(d, 1023)))
			return QString(d)+ "/" + name;
	}
	else 
	{							// path in exe, try it
		QString p = exename.left(slashpos) + "/" + name;
		if (QFile::exists(p))
			return p;	
	}
	
	char *envptr = NULL;					// may be in standard rep.
	
	if ((envptr = getenv(COMMON_DIRNAME_ENV)) == (char *)0) 
	{
		envptr = getenv(ALTERNATE_DIRNAME_ENV);
	}
	if (envptr) {
		QString p = QString(envptr) + "/" + name;
		if (QFile::exists(p))
			return p;	
	}	
	
	return QString("");					// sigh! ......
}


/**
 ** Function:		parTxtGetSection()
 **
 ** Description:	Alloca un array contenente valori (stringhe) prelevati da un file
 **			ascii. Vengono riportati tutti i valori relativi alla sezione.
 **
 ** Arguments:		char *sectnam	= Id della sezione da cui recuperare i valori
 **			char *filnam	= Nome file dati
 **			int  *numitems	= Puntatore ad un intero inizializzato con il numero
 **					  degli items letti
 **
 ** Returned values:	QStrList *	= Array contenente i nominativi
 **			QStrList *0	= condizione di errore
 **
 ** External var. involved:
 **			parLastError	= codice dell'errore quando ret. val. == NULL
 **/

QStringList *ConfigParser::parTxtGetSection(const char *sectnam, const char *filnam)
{
	FILE *fTxtData=NULL;
	QStringList *reqdata = new QStringList();
	char buf[BUFSIZ+1];
	bool flagRetrievingData = false;
	char *strptr=NULL;
		
	fTxtData = fopen(filnam, "r");
	if (fTxtData == (FILE *) NULL) 
	{
		parLastError = ceOPEN_ERROR;
		delete reqdata;
		return((QStringList *)0);		/* no file found */
	}
	
	while (true) 
	{
		if (feof(fTxtData))
			goto Exit_Code;
		if (fgets(buf, BUFSIZ, fTxtData) == (char *)NULL)
			goto Exit_Code;
		
		strptr = buf + strlen(buf);
						/* remove linefeeds retrieved from file */
		while (strptr >= buf) {	
			if (*strptr == '\n' || *strptr == '\r')
				*strptr = '\0';
			--strptr;
		}
		unleadch(buf); 			/* remove leading spaces */
		untrailch(buf);			/* remove trailing spaces */
		if (strlen(buf) == 0)		/* is a null line */
			continue;
		switch (buf[0]) {
			case '[':			/* is a section identifier */	
		 		if (flagRetrievingData)	/* found another section: exit */
		 			goto Exit_Code;
		 		if (TestSection(buf, sectnam))	/* found it ! */
		 			flagRetrievingData = true;
		 		continue;
		 	case '#':			/* is a comment line */
		 		continue;		/* so ignore it */
		 	default:			/* this SHOULD be a data line */
				if (!flagRetrievingData)	/* still searching the section */
					continue;
		 		if (!isalnum(buf[0]) &&	/* paranoia check */
		 		    !ispunct(buf[0]))
		 			continue;
		 		reqdata->append(buf);
		 		continue;
		 }
		
//		 continue;			/* unreachable */
	 }
Exit_Code:
	if (reqdata->count() > 0) 
	{
		parLastError = 0;
		if(fTxtData!=NULL)
		{
			fclose(fTxtData);
			fTxtData=NULL;
		}				
		return(reqdata);
	}
	else 
	{
		parLastError = ceNOT_FOUND;
		if(fTxtData!=NULL)	
		{
			fclose(fTxtData);
			fTxtData=NULL;
		}
		if(reqdata!=NULL)
		{
			delete reqdata;
			reqdata=NULL;
		}	
		return ((QStringList *)0);
	}
}

/**
 ** Function:		parTxtGetValue()
 **
 ** Description:	Alloca e ritorna un valore (stringa) prelevato da un file
 **			ascii. Il valore e' comunque riferito ad una specifica
 **			sezione.
 **
 ** Arguments:		char *valueid	= Identificatore del valore
 **			char *sectnam	= Id della sezione da cui recuperare i valori
 **			char *filnam	= Nome file dati
 **
 ** Returned values:	char *		= Stringa valore
 **			char * NULL	= condizione di errore
 **
 ** External var. involved:
 **			parLastError	= codice dell'errore quando ret. val. == NULL
 **/

char *ConfigParser::parTxtGetValue(const char *valueid, const char *sectnam, const char *filnam)
{
	QStringList *SectionValues;
	char *token;
	char *arg;
	int idx;
	
	SectionValues = parTxtGetSection(sectnam, filnam);
	if (SectionValues == (QStringList *)0)
		return((char *)NULL);		/* parLastError contain the right error value */
	idx = 0;
	if (SectionValues->count() == 0) {			/* empty section */
		parLastError = ceNOT_FOUND;
		delete SectionValues;
		return ((char *) NULL);
	}
	while (true) {				/* main loop: decompose strings & seek the array */
		QString appo=SectionValues->at(idx);
		token = strtok((char *)(appo.toStdString().c_str()), txtDelimiters); /* get the id */
		if (token == (char *)NULL) {	/* unknown error */
			parLastError = ceGOT_AN_ERROR;
			delete SectionValues;
			return ((char *) NULL);
		}
		if (strcmp(token, valueid)) {	/* test if the desired value */
			if (idx < (int)SectionValues->count()) {	/* it isn't */
				++idx;
				continue;
			}
			else {
				parLastError = ceNOT_FOUND;
				delete SectionValues;
				return ((char *)NULL);
			}
		}
						/* found the id: now search the "=" sign */
		token = strtok((char *)NULL, txtDelimiters);
		if (strcmp(token, parARGSEPARATOR)) {	/* if test fail we have a syntax error */
			parLastError = ceSYNTAX_ERROR;
			delete SectionValues;
			return ((char *)NULL);
		}
						/* if all goes well next token (up to the end of
						   the string) is our argument */
		token = strtok((char *)NULL, "");
		if (token == (char *)NULL) {	/* something wrong */
			parLastError = ceSYNTAX_ERROR;
			delete SectionValues;
			return ((char *) NULL);
		}
	
		arg = new char [strlen(token)+1];
		strcpy(arg, token);
		if (arg == (char *)NULL) {	/* may happen */
			parLastError = ceNO_MEMORY;
			delete SectionValues;
			return(arg);
		}
		
		parLastError = ceNO_ERROR;
		delete SectionValues;
		return(arg);
	}
}


/**
 ** Utility functions
 **/


void ConfigParser::unleadch(char *s)
{
	char *cs;
	char *malladdr = (char *) 0;
	char locbuf[1024+1];

	if (strlen(s) > 1024) {
		cs = new char [strlen(s)+1];
		malladdr = cs;
	}
	else {
		cs = locbuf;
	}
	if (cs == (char *)0)
		return;
	strcpy(cs,s);
	while (*cs == ' ' || *cs == '0' || *cs == '\t')
		cs++;
	strcpy(s,cs);
	if (malladdr != (char *)0)
		delete malladdr;
}

void ConfigParser::untrailch(char *s)
{
	char *p;

	p = s+strlen(s)-1;
	while(*p == ' ' || *p == '\t') --p;
	++p; *p = '\0';
}

bool ConfigParser::TestSection(char *tData, const char *fSectid)
{
	char *strptr;
	
	strptr = tData + strlen(tData);
	while (strptr >= tData) {
		if (strptr > tData) {
			--strptr;
			if (*strptr == ']') {
				*strptr = '\0';
				break;
			}
		}
		else {
			return(false);		/* no ending "]": syntax error */
		}
	}	
	++tData;				/* skip starting "[" */
	return ((!strcmp(tData, fSectid))?true:false);	/* Test the name and return */
}
	

/*---[ Eof ]---*/
