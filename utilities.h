 #ifndef UTILITIES_H_
    
    #define UTILITIES_H_
	#include <stdlib.h>
	#include <stdio.h>
	#include <glib.h>
	#include <gmodule.h>
	#include "./list.h"
	#include "./post.h"
	#include "./users.h"
	#include "./pair.h"
	#include "./tag.h"
	#include "./user.h"
	#include "./common.h"
	User get_User (GHashTable* ht,long id);
	Post get_Post (GHashTable* hp,long id);
	LONG_list sort_user_by_N (GList* list,GCompareFunc func,int N);
	LONG_list sort_post_by_N (GList* list,GCompareFunc func,int N);
	LONG_pair total_QandA(GList* list,Date begin, Date end);
	GList* filter_answer_by_dates(GList* list,Date begin,Date end);
	GList* filter_questions_by_dates(GList* list,Date begin,Date end);
	LONG_list set_long_N (GList* list,int N);
	STR_pair infos_from (GHashTable* ht,Post p,User u);
	GList* filter_question_inTitle(GList* list,char* word);
	GList* filter_question_tags_date(GList* list,char* tag,Date begin,Date end);
	GList* filter_post_by_user(GList* list,long id);
	long* get_10_latest(GList* list);
	LONG_list filter_both_contributions(GList* com,GList* aux, long id1,long id2,int N);
	GList* posts_from_both(GList* list,long id1,long id2);
	GList* filter_answers_by_qid (GList* list,long id);
	GList* filter_by_user_and_dates (GList* posts,long uid,Date x, Date y);
	void set_Tag_Count (GList* tags,Post p);
	int calc_answer (Post p,User u);
	long calculate_best_answer(GHashTable* com,GList* aux);
	LONG_list sort_N_tags_by (GList* tags,GCompareFunc func,int N);
	void set_Tag_Counters (GList* totalposts,GList* com);
	GList* create_N_best_users(GList* users,int N);
	GList* filter_total_posts (GList* nbest,GList* com,Date begin,Date end);


#endif