 #ifndef PARSER_H_
    
    #define PARSER_H_
	#include <stdlib.h>
	#include <stdio.h>
	#include <libxml/xmlmemory.h>
	#include <libxml/parser.h>
	#include <libxml/tree.h>
	#include "./utilities.h"
	void insert_User (GHashTable* ht,User u);
	void insert_Tag (GHashTable* ht,Tag t);
	void insert_Post (GHashTable* hp,Post p);
	GHashTable* load_user (GHashTable* com, char* dump_path);
	GHashTable* load_tag (GHashTable* com, char* dump_path);
	GHashTable* load_post (GHashTable* com, GHashTable* comz,char* dump_path);
	

#endif