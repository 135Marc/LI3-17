 #ifndef USERS_H_
    
    #define USERS_H_
	#include <stdlib.h>
	#include <stdio.h>
	#include <string.h>
	#include <gmodule.h>
	#include <glib.h>
	#include "./common.h"
	#include "./date.h"
	typedef struct Users *User;
	User new_User(int reputation, long id,char* displayname,char* shortbio);
	void freeUser (User u);
	int getRep (User u);
	long getIDUser (User u);
	int getPostCount (User u);
	char* getDisplayName (User u);
	char* getShortBio (User u);
	void printUser (User u);
	int cmpUserID (User u1, User u2);
	int cmpRep (User u1, User u2);
	int cmpPostCount (User u1, User u2);
	void add_Post(User u);


#endif