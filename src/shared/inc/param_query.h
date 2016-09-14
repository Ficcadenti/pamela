#ifndef PARAMQUERY_H
#define PARAMQUERY_H

#include <QtCore/QProcess>
#include <QtCore/QDebug>

#include "pamela_limits.h"

/** Gestione dei record TaskParamQuery.
  *@short TaskParamQuery.
  *@author Raffaele Ficcadenti.
  */
class ParamQuery {
public:
	
	ParamQuery() { memset((void*)&data, 0, sizeof(DATA)); }
	~ParamQuery() {}
	
		/** Metodo statico utilizzato per avere la dimensione in byte della struttura dati */
	static int dataSize() { return sizeof(DATA); }
	
	typedef struct {
		int id_operator;
		int type_param;
		char name_operator[OPERATOR_NAME_LEN];
		char value_param[PARAM_VALUE_LEN];
		
	} DATA;
	
	DATA data;
	bool Delete;
	
};

typedef QList<ParamQuery*> paramQueryList; 			
typedef QList<ParamQuery*>::iterator paramQueryList_it; 	

#endif
