#include "hashuser.h"

typedef struct TCD_community {
	GHashTable* hashUser;
	GHashTable* hashPost;
}TCD_community;

TAD_community init (TAD_community ht) {
	ht = g_new(TCD_community,1);
	ht->hashUser = g_hash_table_new((GHashFunc) g_direct_hash,(GEqualFunc) g_direct_equal);
	ht->hashPost = g_hash_table_new((GHashFunc) g_direct_hash,(GEqualFunc) g_direct_equal);
	return ht;
}

void insert_User (TAD_community ht,User u) {
	glong id = (glong) getIDUser(u);
	g_hash_table_insert(ht->hashUser,(gpointer)GINT_TO_POINTER(id),(gpointer) u);
}

void remove_User (TAD_community ht, User u) {
	glong id = (glong) getIDUser(u);
	g_hash_table_remove(ht->hashUser,GINT_TO_POINTER(id));
}

GList* get_Users (TAD_community ht) {
	return g_hash_table_get_values(ht->hashUser); // Usar glist free depois de acabar o que é para fazer.
}

User get_User (TAD_community ht,long id) {
	return g_hash_table_lookup(ht->hashUser,GINT_TO_POINTER((glong) id));
}

void insert_Post (TAD_community hp,Post p) {
	glong id = (glong) getID(p);
	g_hash_table_insert(hp->hashPost,(gpointer)GINT_TO_POINTER(id),(gpointer) p);
}

void remove_Post (TAD_community hp, Post p) {
	glong id = (glong) getOwnerID(p);
	g_hash_table_remove(hp->hashPost,GINT_TO_POINTER(id));
}

GList* get_Posts (TAD_community hp) {
	return g_hash_table_get_values(hp->hashPost); // Usar glist free depois de acabar o que é para fazer.
}

Post get_Post (TAD_community hp,long id) {
	return g_hash_table_lookup(hp->hashPost,GINT_TO_POINTER((glong) id));
}

STR_pair info_from_post(TAD_community hp, long id) {
	STR_pair new=NULL;
	Post p = get_Post(hp,id);
	long uid = getOwnerID(p);
	User u = get_User(hp,uid);
	new=create_str_pair(getTitle(p),getDisplayName(u));
	return new;
}

TAD_community clean (TAD_community hu) {
	 g_hash_table_destroy(hu->hashPost);
	 g_hash_table_destroy(hu->hashUser);
	 g_free(hu);
	 return hu;
}

TAD_community load_post (TAD_community com, char* dump_path) {
	xmlDocPtr doc;
	xmlNodePtr cur;
	Post p=NULL;
	long id,ownerid;
	int typeid,score,answercount;
	char* title;
	char* date;
	char* tags;
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
				 typeid = atoi((char*) xmlGetProp(cur,(const xmlChar *)"PostTypeId"));
				 score = atoi((char*) xmlGetProp(cur,(const xmlChar *)"Score"));
				 buff =(char*) xmlGetProp(cur,(const xmlChar *)"AnswerCount");
				 if (buff!=NULL) answercount= atoi((char*) xmlGetProp(cur,(const xmlChar *)"AnswerCount"));
				 else answercount=0;
				 title = (char*) xmlGetProp(cur,(const xmlChar *)"Title");
				 date = (char*) xmlGetProp(cur,(const xmlChar *)"CreationDate");
				 tags = (char*) xmlGetProp(cur,(const xmlChar *)"Tags");
				 p=nPost(id,ownerid,typeid,score,answercount,title,date,tags);
				 insert_Post(com,p);
				 set_Date(p);
				 add_Post(get_User(com,getOwnerID(p)));
			}
			cur=cur->next;
		}
	return com;
}

TAD_community load_user (TAD_community com, char* dump_path) {
	xmlDocPtr doc;
	xmlNodePtr cur;
	User u=NULL;
	long id;
	int reputation;
	char* display;
	char* shortbio;
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
			}
			cur=cur->next;
		}
	return com;
}

TAD_community load (TAD_community com, char* dump_path) {
	com = load_user(com,dump_path);
	com = load_post(com,dump_path);
	return com;
}

LONG_list top_most_active(TAD_community com, int N) {
	GList* usa = get_Users(com);
	LONG_list res = create_list(N);
	User u = NULL;
	int count=0;
	usa=g_list_sort(usa,(GCompareFunc) cmpPostCount);
	while(usa!=NULL && count<N) {
		u = (User)usa->data;
		set_list(res,count,getIDUser(u));
		count++;
		usa=usa->next;
	}
	return res;
}

LONG_pair total_posts(TAD_community com, Date begin, Date end) {
	LONG_pair lp;
	Post p=NULL;
	Date d =NULL;
	long answercount,questioncount;
	answercount=questioncount=0;
	GList* res = get_Posts(com);
	while(res!=NULL) {
		p = (Post)res->data;
		d = get_DDate(p);
		if (betweenDate (d,begin,end)) {
			if (isQuestion(p)) questioncount+=1;
			else answercount+=1;
		}
		res=res->next;
	}
	lp = create_long_pair(questioncount,answercount);
	return lp;
}

User get_user_info(TAD_community com, long id) {
	int i;
	LONG_list l = create_list(10);
	User u = get_User (com,id);
	Post p = NULL;
	GList* posts = get_Posts(com);
	GList* aux = NULL;
	while (posts!=NULL) {
		p = (Post) posts->data;
		if (getOwnerID(p)==getIDUser(u)) aux = g_list_insert_sorted(aux,(gpointer) p,(GCompareFunc) cmpDate);
		posts = posts->next;
	}
	for (i=0;i<10 && aux!=NULL;i++,aux=aux->next) {
		p = (Post)aux->data;
		set_list(l,i,getID(p));
	}
	setList10(u,l);
	return u;
}

LONG_list most_voted_answers(TAD_community com, int N, Date begin, Date end) {
	int i;
	Post p = NULL;
	Date d = NULL;
	LONG_list res = create_list(N);
	GList* posts = get_Posts(com);
	GList* aux = NULL;
	while (posts!=NULL) {
		p = (Post) posts->data;
		d = get_DDate(p);
		if (betweenDate (d,begin,end)&& isQuestion(p)==0) aux = g_list_insert_sorted(aux,(gpointer) p,(GCompareFunc) cmpPostScore);
		posts=posts->next;
	}
	//g_list_foreach(aux,(GFunc) printPost,(Post) aux->data);
	for (i=0;i<N && aux!=NULL;i++,aux=aux->next) {
		p = (Post)aux->data;
		set_list(res,i,getID(p));
	}
	return res;
}

LONG_list most_answered_questions(TAD_community com, int N, Date begin, Date end) {
	int i;
	Post p = NULL;
	Date d = NULL;
	LONG_list res = create_list(N);
	GList* posts = get_Posts(com);
	GList* aux = NULL;
	while (posts!=NULL) {
		p = (Post) posts->data;
		d = get_DDate(p);
		if (betweenDate (d,begin,end) && isQuestion(p)) aux = g_list_insert_sorted(aux,(gpointer) p,(GCompareFunc) cmpAnswerCount);
		posts=posts->next;
	}
	for (i=0;i<N && aux!=NULL;i++,aux=aux->next) {
		p = (Post)aux->data;
		set_list(res,i,getID(p));
	}
	return res;
}
// LENTA QUE FODE!! (se metermos letras maiusculas ao baralho)
LONG_list contains_word(TAD_community com, char* word, int N) {
	int i;
	Post p = NULL;
	LONG_list res = create_list(N);
	GList* posts = get_Posts(com);
	GList* aux = NULL;
	while (posts!=NULL) {
		p = (Post) posts->data;
		if (isQuestion(p) && inTitle(p,word)) aux = g_list_insert_sorted(aux,(gpointer) p,(GCompareFunc) cmpDate);
		posts=posts->next;
	}
	for (i=0;i<N && aux!=NULL;i++,aux=aux->next) {
		p = (Post)aux->data;
		set_list(res,i,getID(p));
	}
	return res;
}
int main () {
	TAD_community ht=NULL;
	ht=init(ht);
	ht=load(ht,"../dump exemplo/android/");
	/*Date begin = nDate(6,5,2009);
	Date end = nDate(21,12,2009);*/
	LONG_list r = contains_word(ht,"phone",5);
	print_LONG_list(r);
	return 0;
}