#include "interface.h"

typedef struct TCD_community {
	GHashTable* hashUser;
	GHashTable* hashPost;
	GHashTable* hashTags;
}TCD_community;

TAD_community init (TAD_community ht) {
	ht = g_new(TCD_community,1);
	ht->hashUser = g_hash_table_new((GHashFunc) g_direct_hash,(GEqualFunc) g_direct_equal);
	ht->hashPost = g_hash_table_new((GHashFunc) g_direct_hash,(GEqualFunc) g_direct_equal);
	ht->hashTags = g_hash_table_new((GHashFunc) g_direct_hash,(GEqualFunc) g_direct_equal);
	return ht;
}

void insert_User (TAD_community ht,User u) {
	glong id = (glong) getIDUser(u);
	g_hash_table_insert(ht->hashUser,(gpointer)GINT_TO_POINTER(id),(gpointer) u);
}


GList* get_Users (TAD_community ht) {
	return g_hash_table_get_values(ht->hashUser);
}

User get_User (TAD_community ht,long id) {
	return g_hash_table_lookup(ht->hashUser,GINT_TO_POINTER((glong) id));
}

void insert_Post (TAD_community hp,Post p) {
	glong id = (glong) getID(p);
	g_hash_table_insert(hp->hashPost,(gpointer)GINT_TO_POINTER(id),(gpointer) p);
}

GList* get_Posts (TAD_community hp) {
	return g_hash_table_get_values(hp->hashPost); 
}

Post get_Post (TAD_community hp,long id) {
	return g_hash_table_lookup(hp->hashPost,GINT_TO_POINTER((glong) id));
}

void insert_Tag (TAD_community ht,Tag t) {
	glong id = (glong) getTagID(t);
	g_hash_table_insert(ht->hashTags,(gpointer)GINT_TO_POINTER(id),(gpointer) t);
}

GList* get_Tags (TAD_community ht) {
	return g_hash_table_get_values(ht->hashTags);
}

Tag get_Tag (TAD_community ht,long id) {
	return g_hash_table_lookup(ht->hashTags,GINT_TO_POINTER((glong) id));
}

TAD_community load_post (TAD_community com, char* dump_path) {
	xmlDocPtr doc;
	xmlNodePtr cur;
	Post p=NULL;
	long id,ownerid,parentid;
	int typeid,score,answercount,commentcount;
	char* title=NULL;
	char* date=NULL;
	char* tags=NULL;
	char* buff=malloc(150);
	strcpy(buff,dump_path);
	strcat(buff,"Posts.xml");
	doc=xmlParseFile(buff);
	if(doc==NULL){
		printf("Couldn't parse\n");
		exit(-1);
	}
	cur=xmlDocGetRootElement(doc);
	if(cur==NULL){
		printf("Nothing here.\n");
		xmlFreeDoc(doc);
		exit(0);
	}
	cur=cur->xmlChildrenNode;
	while(cur!=NULL){
			if(!xmlStrcmp((cur->name),((const xmlChar *)"row"))){
				 id = atol((char*) xmlGetProp(cur,(const xmlChar *)"Id"));
				 ownerid = atol((char*) xmlGetProp(cur,(const xmlChar *)"OwnerUserId"));
				 buff =(char*) xmlGetProp(cur,(const xmlChar *)"ParentId");
				 if (buff!=NULL) parentid= atoi((char*) xmlGetProp(cur,(const xmlChar *)"ParentId"));
				 else parentid=0;
				 typeid = atoi((char*) xmlGetProp(cur,(const xmlChar *)"PostTypeId"));
				 score = atoi((char*) xmlGetProp(cur,(const xmlChar *)"Score"));
				 buff =(char*) xmlGetProp(cur,(const xmlChar *)"AnswerCount");
				 if (buff!=NULL) answercount= atoi((char*) xmlGetProp(cur,(const xmlChar *)"AnswerCount"));
				 else answercount=0;
				 commentcount = atoi((char*) xmlGetProp(cur,(const xmlChar *)"CommentCount")); 
				 title = (char*) xmlGetProp(cur,(const xmlChar *)"Title");
				 date = (char*) xmlGetProp(cur,(const xmlChar *)"CreationDate");
				 tags =  (char*) xmlGetProp(cur,(const xmlChar *)"Tags");
				 p=nPost(id,ownerid,parentid,typeid,score,answercount,commentcount,title,date,tags);
				 set_Date(p);
				 add_Post(get_User(com,getOwnerID(p)));
				 insert_Post(com,p);
				 free(title);
				 free(date);
				 free(tags);
			}
			cur=cur->next;
		}
		free(buff);
		xmlFreeDoc(doc);
		xmlFreeNode(cur);
	return com;
}

TAD_community load_user (TAD_community com, char* dump_path) {
	xmlDocPtr doc;
	xmlNodePtr cur;
	User u=NULL;
	long id;
	int reputation;
	char* display=NULL;
	char* shortbio=NULL;
	char* buff=malloc(150);
	strcpy(buff,dump_path);
	strcat(buff,"Users.xml");
	doc=xmlParseFile(buff);
	if(doc==NULL){
		printf("Couldn't parse\n");
		exit(-1);
	}
	cur=xmlDocGetRootElement(doc);
	if(cur==NULL){
		printf("Nothing here.\n");
		xmlFreeDoc(doc);
		exit(0);
	}
	cur=cur->xmlChildrenNode;
	while(cur!=NULL){
			if(!xmlStrcmp((cur->name),((const xmlChar *)"row"))){
				 id = atol((char*) xmlGetProp(cur,(const xmlChar *)"Id"));
				 reputation =atoi((char*) xmlGetProp(cur,(const xmlChar *)"Reputation"));
				 display = (char*) xmlGetProp(cur,(const xmlChar *)"DisplayName");
				 shortbio = (char*) xmlGetProp(cur,(const xmlChar *)"AboutMe");
				 u=new_User(reputation,id,display,shortbio);
				 insert_User(com,u);
				 free(display);
				 free(shortbio);
			}
			cur=cur->next;
		}
		free(buff);
		xmlFreeDoc(doc);
		xmlFreeNode(cur);
	return com;
}

TAD_community load_tag (TAD_community com, char* dump_path) {
	xmlDocPtr doc;
	xmlNodePtr cur;
	Tag t =NULL;
	long id;
	char* name=NULL;
	char* buff=malloc(150);
	strcpy(buff,dump_path);
	strcat(buff,"Tags.xml");
	doc=xmlParseFile(buff);
	if(doc==NULL){
		printf("Couldn't parse\n");
		exit(-1);
	}
	cur=xmlDocGetRootElement(doc);
	if(cur==NULL){
		printf("Nothing here.\n");
		xmlFreeDoc(doc);
		exit(0);
	}
	cur=cur->xmlChildrenNode;
	while(cur!=NULL){
			if(!xmlStrcmp((cur->name),((const xmlChar *)"row"))){
				 id = atol((char*) xmlGetProp(cur,(const xmlChar *)"Id"));
				 name = (char*) xmlGetProp(cur,(const xmlChar *)"TagName");
				 t=new_Tag(id,name);
				 insert_Tag(com,t);
				 free(name);
			}
			cur=cur->next;
		}
		free(buff);
		xmlFreeDoc(doc);
		xmlFreeNode(cur);
	return com;
}

TAD_community load (TAD_community com, char* dump_path) {
	com = load_user(com,dump_path);
	com = load_post(com,dump_path);
	com = load_tag(com,dump_path);
	return com;
}

// QUERY 1
STR_pair info_from_post(TAD_community hp, long id) {
	Post p = get_Post(hp,id);
	long uid,pid;
	uid=getOwnerID(p);
	User u = get_User(hp,uid);
	if (isAnswer(p)) {
		pid = getParentID(p);
		p = get_Post(hp,pid);
	}
	STR_pair new = infos_from(p,u);
	return new;
}

// QUERY 2 -> funca
LONG_list top_most_active(TAD_community com, int N) {
	GList* usa = get_Users(com);
	LONG_list res = sort_user_by_N (usa,(GCompareFunc) cmpPostCount,N);
	return res;
}

// QUERY 3 -> funca
LONG_pair total_posts(TAD_community com, Date begin, Date end) {
	GList* res = get_Posts(com);
	LONG_pair lp = total_QandA(res,begin,end);
	return lp;
}

//QUERY 4 -> funca
LONG_list questions_with_tag(TAD_community com, char* tag, Date begin, Date end) {
	GList* posts = get_Posts(com);
	GList* filtered = filter_question_tags_date(posts,tag,begin,end);
	int i = (int) g_list_length(filtered);
	LONG_list res = sort_post_by_N (filtered,(GCompareFunc) cmpDate,i);
	return res;
}

// QUERY 5 -> funca
USER get_user_info(TAD_community com, long id) {
	GList* posts = get_Posts(com);
	User u = get_User(com,id);
	GList* aux = filter_post_by_user(posts,id);
	char* shortbio = getShortBio(u);
	long *l = get_10_latest(aux);
	USER res = create_user(shortbio,l);
	return res;
}

// QUERY 6 -> funca
LONG_list most_voted_answers(TAD_community com, int N, Date begin, Date end) {
	GList* posts = get_Posts(com);
	GList* filtered = filter_answer_by_dates(posts,begin,end);
	LONG_list res = set_long_N (filtered,N); 
	return res;
}
// QUERY 7 -> funca
LONG_list most_answered_questions(TAD_community com, int N, Date begin, Date end) {
	GList* posts = get_Posts(com);
	GList* aux = filter_questions_by_dates(posts,begin,end);
	LONG_list res= set_long_N (aux,N);
	return res;
}

// QUERY 8
LONG_list contains_word(TAD_community com, char* word, int N) {
	GList* posts = get_Posts(com);
	GList* aux = filter_question_inTitle(posts,word);
	LONG_list res = set_long_N(aux,N);
	return res;
}

//QUERY 9 -> funca
LONG_list both_participated(TAD_community com, long id1, long id2, int N) {
	GList* posts = get_Posts(com);
	GList* aux = posts_from_both(posts,id1,id2);
	LONG_list res = filter_both_contributions(posts,aux,id1,id2,N);
	return res;
}

// QUERY 10 -> funca
long better_answer(TAD_community com, long id) {
	GList* list = get_Posts(com);
	GList* aux=filter_answers_by_qid(list,id);
	Post p1 = NULL;
	User u = NULL;
	long idr=0;
	int curr,max,oid;
	curr=max=0;
	while (aux!=NULL) {
		p1 = (Post)aux->data;
		oid = getOwnerID(p1);
		u = get_User(com,oid);
		curr = calc_answer(p1,u);
		if (curr>max) {
			max = curr;
			idr = getID(p1);
		}
		aux = aux->next;
	}
	g_list_free_full (aux,(GDestroyNotify) freePost);
	return idr;
}

//QUERY 11 
LONG_list most_used_best_rep(TAD_community com, int N, Date begin, Date end) {
	GList* users = get_Users(com);
	users = g_list_sort(users,(GCompareFunc) cmpRep);
	GList* posts = get_Posts(com);
	GList* tags = get_Tags(com);
	GList* nbest = create_N_best_users(users,N);
	GList* totalposts = filter_total_posts (nbest,posts,begin,end);
	set_Tag_Counters (totalposts,tags);
	LONG_list res = sort_N_tags_by (tags,(GCompareFunc) cmpCounter,N);
	return res;
}

TAD_community clean (TAD_community hu) {
	 g_hash_table_destroy(hu->hashPost);
	 g_hash_table_destroy(hu->hashUser);
	 g_hash_table_destroy(hu->hashTags);
	 g_free(hu);
	 return hu;
}
