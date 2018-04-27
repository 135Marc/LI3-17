 #ifndef INTERFACE_H
    
    #define INTERFACE_H
	#include <stdlib.h>
	#include <stdio.h>
	#include <glib.h>
	#include <gmodule.h>
	#include <libxml/xmlmemory.h>
	#include <libxml/parser.h>
	#include <libxml/tree.h>
	#include "./utilities.h"
	typedef struct TCD_community* TAD_community;
	TAD_community init (TAD_community hp);
	void insert_User (TAD_community ht,User u);
	GList* get_Users (TAD_community hp);
	User get_User (TAD_community ht,long id);
	void insert_Post (TAD_community hp,Post p);
	GList* get_Posts (TAD_community hp);
	Post get_Post (TAD_community hp,long id);
	void insert_Tag (TAD_community ht,Tag t);
	GList* get_Tags (TAD_community ht);
	Tag get_Tag (TAD_community ht,long id);
	TAD_community load_user (TAD_community com, char* dump_path);
	TAD_community load_post (TAD_community com, char* dump_path);
	TAD_community load_tag (TAD_community com, char* dump_path);
	TAD_community load (TAD_community com, char* dump_path);
	STR_pair info_from_post(TAD_community hp, long id);
	LONG_list top_most_active(TAD_community com, int N);
	LONG_pair total_posts(TAD_community com, Date begin, Date end);
	LONG_list questions_with_tag(TAD_community com, char* tag, Date begin, Date end);
	USER get_user_info(TAD_community com, long id);
	LONG_list most_voted_answers(TAD_community com, int N, Date begin, Date end);
	LONG_list most_answered_questions(TAD_community com, int N, Date begin, Date end);
	LONG_list contains_word(TAD_community com, char* word, int N);
	LONG_list both_participated(TAD_community com, long id1, long id2, int N);
	long better_answer(TAD_community com, long id);
	LONG_list most_used_best_rep(TAD_community com, int N, Date begin, Date end);
	TAD_community clean (TAD_community hu);

#endif