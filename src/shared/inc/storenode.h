/*
#  MODULE DESCRIPTION:
#  storenode.h
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

#ifndef STORENODE_H
#define STORENODE_H

#include <string.h>
#include <QtCore/qstring.h>

/** Questa classe definisce alcuni metodi di utlita' per semplificare l'accesso alle sezioni della configurazione.
  *  Tutti i metodi della classe sono statici al fine di consentire l'utilizzo in qualsiasi punto del codice sorgente.
  */



class StoreNode {
public:
		/** Imposta il nome dell'eseguibile corrente in un area statica */
	static void setMyExeName(const QString & exename);
		/** Imposta il nome della centrale di riferimento in un area statica */
	static void set(char *name);
		/** Imposta un prefisso di riferimento in un area statica */
	static void setPrefix(char * prefix);
		/** Ritorna il nome centrale precedentemente impostato */
	static char * get();
		/** Combina il prefisso impostato con l'argomento */
	static char * combine(char * prefix);
		/** Restituisce il nome dell'eseguibile corrente precedentemente salvato in area statica */
	static QString myExeName();

};

#endif
