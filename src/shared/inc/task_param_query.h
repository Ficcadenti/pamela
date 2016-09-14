#ifndef TASKPARAMQUERY_H
#define TASKPARAMQUERY_H

#include <QtCore/QProcess>
#include <QtCore/QDebug>

#include "pamela_limits.h"
#include "param_query.h"

/** Gestione dei record TaskParamQuery.
  *@short TaskParamQuery.
  *@author Raffaele Ficcadenti.
  */
class TaskParamQuery {
public:
	
	TaskParamQuery() { memset((void*)&data, 0, sizeof(DATA)); }
	~TaskParamQuery() {}
	
		/** Metodo statico utilizzato per avere la dimensione in byte della struttura dati */
	static int dataSize() { return sizeof(DATA); }
	
	typedef struct {
		char name_param[PARAM_NAME_LEN];
		paramQueryList *pList;
	} DATA;
	
	DATA data;
	bool Delete;
	
};

typedef QMap<int,TaskParamQuery*> taskParamQueryList; 			/* key: id_param */
typedef QMap<int,TaskParamQuery*>::iterator taskParamQueryList_it; 	/* key: id_param */

#endif
