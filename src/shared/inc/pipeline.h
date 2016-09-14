#ifndef PIPELINE_H
#define PIPELINE_H

#include "pamela_limits.h"
#include "task.h"

/** Gestione dei record Pipe Line.
  *@short Pipe Line.
  *@author Raffaele Ficcadenti.
  */
class PipeLine {
public:
	
	PipeLine() { memset((void*)&data, 0, sizeof(DATA)); }
	~PipeLine() {}
	
		/** Metodo statico utilizzato per avere la dimensione in byte della struttura dati */
	static int dataSize() { return sizeof(DATA); }
	
	
	typedef struct {
		int id_user;
		char pipeline_desc[PIPELINE_DESC_LEN];
		taskList *tList;
	} DATA;
	
	DATA data;
	bool Delete;
	
};


typedef QMap<int,PipeLine*> pipeLineList;
typedef QMap<int,PipeLine*>::iterator pipeLineList_it;

#endif
