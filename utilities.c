#include "utilities.h"

LONG_list sort_user_by_N (GList* list,GCompareFunc func,int N) {
	User u = NULL;
	LONG_list res = create_list(N);
	int count =0;
	list=g_list_sort(list,func);
	while(list!=NULL && count<N) {
		u = (User)list->data;
		set_list(res,count,getIDUser(u));
		count++;
		list=list->next;
	}
	g_list_free_full (list,(GDestroyNotify) freeUser);
	return res;	
}

LONG_list sort_post_by_N (GList* list,GCompareFunc func,int N) {
	Post p = NULL;
	LONG_list res = create_list(N);
	int count =0;
	list=g_list_sort(list,func);
	while(list!=NULL && count<N) {
		p = (Post)list->data;
		set_list(res,count,getID(p));
		count++;
		list=list->next;
	}
	g_list_free_full (list,(GDestroyNotify) freePost);
	return res;
}

LONG_pair total_QandA(GList* list,Date begin, Date end) {
	LONG_pair lp;
	Post p=NULL;
	Date d=NULL;
	long answercount,questioncount;
	answercount=questioncount=0;
	while(list!=NULL) {
		p = (Post)list->data;
		d = get_DDate(p);	
		if (betweenDate (d,begin,end)) {
			if (isQuestion(p)) questioncount+=1;
			if (isAnswer(p)) answercount+=1;
		}
		list=list->next;
	}
	g_list_free_full (list,(GDestroyNotify) freePost);
	lp = create_long_pair(questioncount,answercount);
	return lp;
}

GList* filter_answer_by_dates(GList* list,Date begin,Date end) {
	Post p = NULL;
	Date d = NULL;
	GList* aux = NULL;
	while (list!=NULL) {
		p = (Post) list->data;
		d = get_DDate(p);
		if (betweenDate (d,begin,end)&& isAnswer(p)) aux = g_list_insert_sorted(aux,(gpointer) p,(GCompareFunc) cmpPostScore);
		list=list->next;
	}
	g_list_free_full (list,(GDestroyNotify) freePost);
	return aux;
}

GList* filter_questions_by_dates(GList* list,Date begin,Date end) {
	Post p = NULL;
	Date d = NULL;
	GList* aux = NULL;
	while (list!=NULL) {
		p = (Post) list->data;
		d = get_DDate(p);
		if (betweenDate (d,begin,end)&& isQuestion(p)) aux = g_list_insert_sorted(aux,(gpointer) p,(GCompareFunc) cmpAnswerCount);
		list=list->next;
	}
	g_list_free_full (list,(GDestroyNotify) freePost);
	return aux;
}

LONG_list set_long_N (GList* list,int N) {
	int i;
	Post p = NULL;
	LONG_list res = create_list(N);
	for (i=0;i<N && list!=NULL;i++,list=list->next) {
			p = (Post)list->data;
			set_list(res,i,getID(p));
	}
	return res;
}

STR_pair infos_from (Post p,User u) {
	STR_pair new;
	char* title = getTitle(p);
	char* name = getDisplayName(u);
	new=create_str_pair(title,name);
	freePost(p);
	freeUser(u);
	return new;
}

GList* filter_question_inTitle(GList* list,char* word) {
	Post p = NULL;
	GList* aux = NULL;
	while (list!=NULL) {
		p = (Post) list->data;
		if (isQuestion(p) && inTitle(p,word)) {
			aux = g_list_insert_sorted(aux,(gpointer) p,(GCompareFunc) cmpDate);
		}
		list=list->next;
	}
	g_list_free_full (list,(GDestroyNotify) freePost);
	return aux;
}

GList* filter_question_tags_date(GList* list,char* tag,Date begin,Date end) {
	Post p = NULL;
	Date d = NULL;
	GList* aux = NULL;
	char* tagz;
	while (list!=NULL) {
		p = (Post) list->data;
		d = get_DDate(p);
		if (isQuestion(p) && betweenDate (d,begin,end)) {
			tagz=getTags(p);
			if (inTag(tagz,tag)) aux = g_list_insert_sorted(aux,(gpointer) p,(GCompareFunc) cmpDate);
		}
		list=list->next;
	}
	g_list_free_full (list,(GDestroyNotify) freePost);
	return aux;
}
GList* filter_post_by_user(GList* list,long id) {
	Post p = NULL;
	GList* aux = NULL;
	while (list!=NULL) {
		p = (Post) list->data;
		if (getOwnerID(p)==id) aux = g_list_insert_sorted(aux,(gpointer) p,(GCompareFunc) cmpDate);
		list = list->next;
	}
	g_list_free_full (list,(GDestroyNotify) freePost);
	return aux;
}

long* get_10_latest(GList* list) {
	int i;
	Post p = NULL;
	long* l = malloc(sizeof(long)*10);
	for (i=0;i<10 && list!=NULL;i++,list=list->next) {
		p = (Post)list->data;
		l[i]=getID(p);
	}
	return l;
}

GList* get_Answers(GList* l,long postid) {
	Post p = NULL;
	GList* res = NULL;
	while (l!=NULL) {
		p = (Post) l->data;
		if (isAnswer(p) && getParentID(p)==postid) res = g_list_prepend(res,(gpointer) p);
		l=l->next;
	}
	return res;
}

int has_answered_post(GList* list,long postid,long uid) {
	GList* res = get_Answers(list,postid);
	Post p = NULL; 
	int r=0;
	while (res!=NULL) {
		p = (Post) res->data;
		if (getOwnerID(p)==uid) r=1;
		res=res->next;
	}
	return r;
}


LONG_list filter_both_contributions(GList* com,GList* aux, long id1,long id2,int N) {
	int i=0;
	long oid,pid;
	Post p = NULL;
	LONG_list res = create_list(N);
	while(aux!=NULL && i<N) {
		p = (Post)aux->data;
		oid = getOwnerID(p);
		if (isQuestion(p)) {
			pid = getID(p);
			if (oid==id1 && has_answered_post(com,pid,id2)) {
				set_list(res,i,pid);
				i++; 
			}
			else if (oid==id2 && has_answered_post(com,pid,id1)) {
				set_list(res,i,pid);
				i++;
			}
		}
		if (isAnswer(p)) {
			pid = getParentID(p);
			if (oid == id1 && has_answered_post(com,pid,id2))  {
				set_list(res,i,pid);
				i++;
			}
		}
		aux=aux->next;	
	}
	g_list_free_full (aux,(GDestroyNotify) freePost);
	return res;
}

GList* posts_from_both(GList* list,long id1,long id2) {
	GList* aux = NULL;
	Post p = NULL;
	while(list!=NULL) { 
		p = (Post) list->data;
		if (getOwnerID(p)==id1 || getOwnerID(p)==id2) aux = g_list_insert_sorted(aux,(gpointer) p,(GCompareFunc) cmpDate);
		list=list->next;
	}
	return aux;
}

GList* filter_answers_by_qid (GList* list,long id) {
	Post p1 = NULL;
	GList* aux = NULL;
	while (list!=NULL) {
		p1 = (Post)list->data;
		if(isAnswer(p1) && getParentID(p1)==id) aux = g_list_prepend(aux,(gpointer) p1);
		list=list->next;
	}
	g_list_free_full (list,(GDestroyNotify) freePost);
	return aux;
}

GList* filter_by_user_and_dates (GList* posts,long uid,Date x, Date y) {
	GList* res = NULL;
	Date d = NULL;
	Post p = NULL;
	long oid;
	while(posts!=NULL) {
		p = (Post) posts->data;
		oid = getOwnerID(p);
		d = get_DDate(p);
		if (oid==uid && betweenDate(d,x,y)) {
			if (isQuestion(p)) res = g_list_append(res,(gpointer) p);
		} 
		posts=posts->next;	
	}
	return res;
}

void set_Tag_Count (GList* tags,Post p) {
	Tag t=NULL;
	char* res = getTags(p);
	char* name=NULL;
	while (tags!=NULL) {
		t = (Tag) tags->data;	
		name = getTagName(t);
		if (inTag(res,name)) add_Tag_Count(t);
		tags = tags->next;
	}
	g_list_free_full (tags,(GDestroyNotify) freeTag);
}

int calc_answer (Post p,User u) {
	int rep,comt,score,res;
	rep = getRep(u);
	comt = getCommentCount(p);
	score = getScore(p);
	res = ((0.65*score)+(0.25*rep)+(0.1*comt));
	return res;
}

LONG_list sort_N_tags_by (GList* tags,GCompareFunc func,int N){
	LONG_list res = create_list(N);
	Tag t = NULL;
	long tid;
	int i=0;
	tags = g_list_sort(tags,func);
	while(tags!=NULL && i<N) {
		t = (Tag) tags->data;
		tid = getTagID(t);
		set_list(res,i,tid);
		i++;
		tags = tags->next;	
	}
	return res;
}

void set_Tag_Counters (GList* totalposts,GList* com) {
	Post p = NULL;
	while (totalposts!=NULL) {
		p = (Post) totalposts->data;
		set_Tag_Count (com,p);
		totalposts=totalposts->next;
	}
}

GList* create_N_best_users(GList* users,int N) {
	GList* nbest = NULL;
	User u = NULL;
	int i=0;
	while (users!=NULL && i<N) {
		u = (User) users->data;
		nbest = g_list_insert_sorted(nbest,(gpointer) u,(GCompareFunc) cmpRep);
		i++;
		users=users->next;
	}
	return nbest;
}

GList* filter_total_posts (GList* nbest,GList* com,Date begin,Date end) {
	GList* filter = NULL;
	GList* totalposts = NULL;
	User u = NULL;
	long uid;
	while(nbest!=NULL) {
		u = (User) nbest->data;
		uid = getIDUser(u);
		filter = filter_by_user_and_dates(com,uid,begin,end);
		totalposts = g_list_concat(totalposts,filter);
		nbest = nbest->next;
	}
	return totalposts;
}