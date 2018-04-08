#include "hashuser.h"

typedef struct TCD_community {
	GHashTable* hashUser;
	GHashTable* hashPost;
}TCD_community;

GHashTable* init_HashUser (GHashTable* hu) {
	hu = g_hash_table_new((GHashFunc) g_direct_hash,(GEqualFunc) g_direct_equal);
	return hu;
}

void clearHashUser (GHashTable* hu) {
	 g_hash_table_destroy(hu);
}

void insertUserH (GHashTable* hu,User u) {
	glong id = (glong) getIDUser(u);
	g_hash_table_insert(hu,(gpointer)GINT_TO_POINTER(id),(gpointer) u);
}

void removeUserH (GHashTable* hu, User u) {
	glong id = (glong) getIDUser(u);
	g_hash_table_remove(hu,GINT_TO_POINTER(id));
}

GList* getUsersHTU (GHashTable* hu) {
	return g_hash_table_get_values(hu); // Usar glist free depois de acabar o que é para fazer.
}

User getUserHT (GHashTable* hu,long id) {
	return g_hash_table_lookup(hu,GINT_TO_POINTER((glong) id));
}

GHashTable* init_HashPost (GHashTable* hp) {
	hp= g_hash_table_new((GHashFunc) g_direct_hash,(GEqualFunc) g_direct_equal);
	return hp;
}

void clearHashPost (GHashTable* hp) {
	 g_hash_table_destroy(hp);
}

void insertPostH (GHashTable* hp,Post p) {
	glong id = (glong) getID(p);
	g_hash_table_insert(hp,(gpointer)GINT_TO_POINTER(id),(gpointer) p);
}

void removePostH (GHashTable* hp, Post p) {
	glong id = (glong) getOwnerID(p);
	g_hash_table_remove(hp,GINT_TO_POINTER(id));
}

GList* getPostsHTP (GHashTable* hp) {
	return g_hash_table_get_values(hp); // Usar glist free depois de acabar o que é para fazer.
}

Post getPostHT (GHashTable* hp,long id) {
	return g_hash_table_lookup(hp,GINT_TO_POINTER((glong) id));
}

STR_pair info_from_post(GHashTable* hp, long id) {
	Post p = getPostHT(hp,id);
	STR_pair new = create_str_pair(getTitle(p),getTags(p));
	return new;
}


int main () {
	GHashTable* test = NULL;
	test=init_HashUser(test);	
	User u = new_User(600,50,"asshole","Cago-te na fronha");
	User u1 =new_User(550,47,"merdas","Cago-te na cozinha");
	User u2=new_User(510,20,"Jacker","Só fumo umas merdas para me divertir");
	User u3=new_User(20,49,"merdas1","Cago-te na cozinha");
	User u4=new_User(2000,48,"asshole1","Cago-te na fronha");
	insertUserH(test,u);
	insertUserH(test,u1);
	insertUserH(test,u2);
	insertUserH(test,u3);
	insertUserH(test,u4);
	GHashTable* hp = NULL;
	hp = init_HashPost(hp);
	Post p = nPost(1,50,1,100,3,"Como não ser fodido pela TERESONA?","2013-12-23T15:52:19.960","<rooting><root-access>");
	Post p1 = nPost(2,47,2,200,0,NULL,"2010-09-13T19:21:30.790",NULL);
	Post p2 = nPost(4,47,1,0,3,"Será que O Proença vai me dar o 6?","2010-09-13T19:21:10.473","<contacts><sms>");
	Post p3 = nPost(3,48,2,10,3,NULL,"2010-09-13T19:21:30.790","<task-management>");
	Post p4 = nPost(5,50,1,1000,3,"Como é que a Ralha virou avózinha?","2010-09-13T19:22:01.080","<sms><notifications><google-voice>");
	insertPostH(hp,p);
	insertPostH(hp,p1);
	insertPostH(hp,p2);
	insertPostH(hp,p3);
	insertPostH(hp,p4);
	STR_pair res = info_from_post(hp,3);
	print_pair(res);
	/*GList* res = getPostsHTP(hp);
	g_list_foreach(res , (GFunc) printPost , (Post)res->data);*/
	return 0;
}