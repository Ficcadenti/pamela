#ifndef USER_H
#define USER_H

#include "pamela_limits.h"

/** Gestione dei record User
  *@short User.
  *@author Raffaele Ficcadenti.
  */
class User {
public:
	
	User() { memset((void*)&data, 0, sizeof(DATA)); }
	~User() {}
	
		/** Metodo statico utilizzato per avere la dimensione in byte della struttura dati */
	static int dataSize() { return sizeof(DATA); }
	
	
	typedef struct {
		char login[USER_LOGIN_LEN];
		char name[USER_NAME_LEN];
		char desc[USER_DESC_LEN];
	} DATA;
	
	DATA data;
	bool Delete;
	
};


typedef QMap<int,User*> userList;
typedef QMap<int,User*>::iterator userList_it;

#endif
