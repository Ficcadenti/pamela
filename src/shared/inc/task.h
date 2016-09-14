#ifndef TASK_H
#define TASK_H

#include <QtCore/QProcess>
#include <QtCore/QDebug>

#include "pamela_limits.h"

/** Gestione dei record task.
  *@short Task.
  *@author Raffaele Ficcadenti.
  */
class Task {
public:
	
	Task() { memset((void*)&data, 0, sizeof(DATA)); }
	~Task() {}
	
		/** Metodo statico utilizzato per avere la dimensione in byte della struttura dati */
	static int dataSize() { return sizeof(DATA); }
	
	typedef struct {
		char task_desc[PIPELINE_TASK_DESC_LEN];
		char task_exe[PIPELINE_TASK_EXE_LEN];
		int task_pid;
		int status;
		char root_file[PIPELINE_ROOT_FILE_LEN];
		char png_file[PIPELINE_PNG_FILE_DESC_LEN];	
		int id_error;
		/* process for this task */
		QProcess *myProcess;
	} DATA;
	
	DATA data;
	bool Delete;
	
};


typedef QMap<int,Task*> taskList;
typedef QMap<int,Task*>::iterator taskList_it;

#endif
