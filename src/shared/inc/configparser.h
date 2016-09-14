/*
#  MODULE DESCRIPTION:
#  configparser.h
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

#ifndef CONFIGPARSER_H
#define CONFIGPARSER_H

extern "C" {
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
}

#include <QtCore/qstring.h>
#include <QtCore/qstringlist.h>
#include <QtCore/qfile.h>
#include <iostream>

/**In questa classe viene implementato un parser per eseguire la decodifica della sintassi
  *utilizzata per i file di configurazione degli applicativi PAMELA.
  */

#define COMMON_DIRNAME_ENV			"GRAPHDATA"
#define ALTERNATE_DIRNAME_ENV			"LD_LIBRARY_PATH"
#define COMMON_CONFIG_FILE			"pamela.cfg"

#define parDELIMITERS	" \t"			/* Delimitatori ammessi */
#define parARGSEPARATOR	"="			/* Separatore id /valore */

#define MAXITEMSPERSECTION	1024		/* max admitted items per section */


class ConfigParser {
public:
	enum parCodeEnums {
		ceNO_ERROR,
		ceGOT_AN_ERROR,
		ceOPEN_ERROR,
		ceCORRUPT_DATA_ERROR,
		ceNO_MEMORY,
		ceREAD_ERROR,
		ceNOT_FOUND,
		ceSYNTAX_ERROR
	};

	ConfigParser();
	~ConfigParser();
			/** Questo metodo ritorna tutte le righe definit all'interno di un sezione.
			  *@param sectnam Identificativo (nome) della sezione desiderata
			  *@param filnam File di configurazione per la lettura dei dati
			  */
	QStringList * parTxtGetSection(const char *sectnam, const char *filnam);
			/** Questo metodo ritorna (come stringa) una valore assegnato ad uno specifico
			  * tag di una sezione.
			  *@param valueid Tag di cui ricercare il valore
			  *@param sectnam Identificativo della sezione proprietaria del tag "valueid"
			  *@param filnam File di configurazione per la lettura dei dati
			  */
	char * parTxtGetValue(const char *valueid, const char *sectnam, const char *filnam);
			/** Questo metodo esegue la lettura da variabile ambientali dei path
			  * di default per i (il) file di configrazione degli applicativi PAMELA.
			  */
	char * getStandardGraphicConfigFilename();
			/** Si tenta di determinare il nome del file in assenza di path assoluta */
	QString locateFile(QString name, QString exename);

private:
	int parLastError;
	const char * txtDelimiters;
			/** Eliminazione dei blank ad inizio stringa */
	void unleadch(char *s);
			/** Eliminazione dei blank a fine stringa */
	void untrailch(char *s);
			/** Metodo ad uso'interno pe la ricerca dell'header di una sezione */
	bool TestSection(char *tData, const char *fSectid);
};

#endif
