 #ifndef HASHUSER_H_
    
    #define HASHUSER_H_
	#include <stdlib.h>
	#include <stdio.h>
	#include <glib.h>
	#include <gmodule.h>
	#include "./post.h"
	#include "./user.h"
	#include "./pair.h"
	#include "./list.h"
	typedef struct TCD_community* TAD_community;
	GHashTable* init_HashUser (GHashTable* hp);
	void clearHashUser (GHashTable* hp);
	void insertUserH (GHashTable* hp,User p);
	void removeUserH (GHashTable* hp, User p);
	GList* getUsersHTU (GHashTable* hp);
	User getUserHT (GHashTable* hp,long id);
	GHashTable* init_HashPost (GHashTable* hp);
	void clearHashPost (GHashTable* hp);
	void insertPostH (GHashTable* hp,Post p);
	void removePostH (GHashTable* hp, Post p);
	GList* getPostsHTP (GHashTable* hp);
	Post getPostHT (GHashTable* hp,long id);


#endif