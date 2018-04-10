 #ifndef HASHUSER_H_
    
    #define HASHUSER_H_
	#include <stdlib.h>
	#include <stdio.h>
	#include <glib.h>
	#include <gmodule.h>
	#include <libxml/xmlmemory.h>
	#include <libxml/parser.h>
	#include <libxml/tree.h>
	#include "./post.h"
	#include "./user.h"
	#include "./pair.h"
	typedef struct TCD_community* TAD_community;
	TAD_community init (TAD_community hp);
	void insert_User (TAD_community ht,User u);
	void remove_User (TAD_community hp, User p);
	GList* get_Users (TAD_community hp);
	User get_User (TAD_community ht,long id);
	void insert_Post (TAD_community hp,Post p);
	void remove_Post (TAD_community hp, Post p);
	GList* get_Posts (TAD_community hp);
	Post get_Post (TAD_community hp,long id);
	TAD_community clean (TAD_community hu);
	LONG_list top_most_active(TAD_community com, int N);


#endif