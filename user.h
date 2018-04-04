 #ifndef USER_H_
    
    #define USER_H_
	#include <stdlib.h>
	#include <stdio.h>
	#include <string.h>
	#include <gmodule.h>
	#include <glib.h>
	#include "list.h"
	typedef struct Users *User;
	User nUser(int reputation, long id,char* display,char* shortbio);
	void freeUser (User u);
	int getRep (User u);
	long getIDUser (User u);
	char* getDisplayName (User u);
	char* getShortBio (User u);
	void printUser (User u);


#endif