 #ifndef INTERFACE_H
    
    #define INTERFACE_H
	#include <stdlib.h>
	#include <stdio.h>
	#include <glib.h>
	#include <gmodule.h>
	#include "./utilities.h"
	#include "./parser.h"
	typedef struct TCD_community* TAD_community;
	TAD_community init (TAD_community hp);
	GHashTable* get_HashT_Posts (TAD_community ht);
	GHashTable* get_HashT_Users (TAD_community ht);
	GHashTable* get_HashT_Tags (TAD_community ht);
	GList* get_Users (TAD_community hp);
	GList* get_Posts (TAD_community hp);
	GList* get_Tags (TAD_community ht);
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