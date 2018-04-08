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
	STR_pair new = create_str_pair(getTitle(p),getDisplayName(u));
	return new;
}

TAD_community clean (TAD_community hu) {
	 g_hash_table_destroy(hu->hashPost);
	 g_hash_table_destroy(hu->hashUser);
	 g_free(hu);
	 return hu;
}


int main () {
	TAD_community ht=NULL;
	ht=init(ht);	
	return 0;
}