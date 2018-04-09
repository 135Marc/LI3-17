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
	Post p = get_Post(hp,id);
	long uid = getOwnerID(p);
	User u = get_User(hp,uid);
	if (u == NULL || p== NULL) return NULL;
	STR_pair new=NULL;
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
				 add_Post(get_User(com,ownerid));
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

int main () {
	TAD_community ht=NULL;
	ht=init(ht);
	ht=load_user(ht,"../dump exemplo/android/");
	ht=load_post(ht,"../dump exemplo/android/");
	STR_pair query1=info_from_post(ht,130669);
	print_pair(query1); 
	return 0;
}