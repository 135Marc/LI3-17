#include "parser.h"

/**
* @file parser.c
* @brief Parser
*/


/**	@brief Função que insere o user na tabela de Hash
*   @param GHashTable*
*   @param User 
*/
void insert_User (GHashTable* ht,User u) {
	glong id = (glong) getIDUser(u);
	g_hash_table_insert(ht,(gpointer)GINT_TO_POINTER(id),(gpointer) u);
}


/**	@brief Função que insere a tag na tabela de Hash
*   @param GHashTable*
*   @param Tag 
*/
void insert_Tag (GHashTable* ht,Tag t) {
	glong id = (glong) getTagID(t);
	g_hash_table_insert(ht,(gpointer)GINT_TO_POINTER(id),(gpointer) t);
}


/**	@brief Função que insere o post na tabela de Hash
*   @param GHashTable*
*   @param Post
*/
void insert_Post (GHashTable* hp,Post p) {
	glong id = (glong) getID(p);
	g_hash_table_insert(hp,(gpointer)GINT_TO_POINTER(id),(gpointer) p);
}


/**	@brief Função que devolve o user da tabela de Hash
*   @param GHashTable*
*   @param long ID
*   @return User
*/
User get_UUser (GHashTable* ht,long id) {
	return g_hash_table_lookup(ht,GINT_TO_POINTER((glong) id));
}


/**	@brief Função que carrega os ficheiros XML dos users para a tabela de hash
*   @param GHashTable*
*   @param char* path para os ficheiros XML
*   @return GHashTable* 
*/
GHashTable* load_user (GHashTable* com, char* dump_path) {
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


/**	@brief Função que carrega os ficheiros XML das Tags para a tabela de hash
*   @param GHashTable*
*   @param char* path para os ficheiros XML
*   @return GHashTable* 
*/
GHashTable* load_tag (GHashTable* com, char* dump_path) {
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


/**	@brief Função que carrega os ficheiros XML dos Posts para a tabela de hash
*   @param GHashTable*
*   @param GHashTable*
*   @param char* path para os ficheiros XML
*   @return GHashTable* 
*/
GHashTable* load_post (GHashTable* com, GHashTable* comz,char* dump_path) {
	xmlDocPtr doc;
	xmlNodePtr cur;
	Post p=NULL;
	User u=NULL;
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
				 if (isQuestion(p) || isAnswer(p)){
				 		u=get_User(comz,getOwnerID(p));
				 		add_Post(u);
				 } 
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
