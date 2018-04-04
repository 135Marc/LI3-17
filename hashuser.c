#include "hashuser.h"

typedef struct ht {
	GHashTable* hashUser;
	GHashTable* hashPost;
}ht;

GHashTable* initHashUser (GHashTable* hu) {
	hu= g_hash_table_new_full((GHashFunc) g_direct_hash,(GEqualFunc) g_direct_equal ,(GDestroyNotify) free,(GDestroyNotify) freeUser);
	return hu;
}

void clearHashUser (GHashTable* hu) {
	 g_hash_table_destroy(hu);
}

void insertUserH (GHashTable* hu,User u) {
	glong id = (glong) getIDUser(u);
	g_hash_table_insert(hu,(gpointer) GINT_TO_POINTER(id),(gpointer) u);
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

void initHashPost (GHashTable* hp) {
	hp= g_hash_table_new_full((GHashFunc) g_direct_hash,(GEqualFunc) g_direct_equal,(GDestroyNotify) free,(GDestroyNotify) freePost);
}

void clearHashPost (GHashTable* hp) {
	 g_hash_table_destroy(hp);
}

void insertPostH (GHashTable* hp,Post p) {
	glong id = (glong) getOwnerID(p);
	g_hash_table_insert(hp,GINT_TO_POINTER(id),(gpointer) p);
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

int main () {
	GHashTable* hm = initHashUser(hm);
	User u = nUser(600,50,"asshole");
	User u1 =nUser(550,49,"merdas");
	User u2=nUser(510,20,"Jacker");
	User u3=nUser(20,49,"merdas");
	User u4=nUser(2000,49,"asshole");
	insertUserH (hm,u);
	insertUserH (hm,u1);
	insertUserH (hm,u2);
	/* GList* lista = g_hash_table_get_values(hm);
	for(lista;lista!=NULL;lista=lista->next) {
	printf("Display do utilizador : %s\n",lista -> (User) data -> displayname);
	printf("ID do utilizador : %li\n",lista -> (User) data ->id);
	printf("Reputação : %d\n",lista -> (User) data -> reputation);
	}	
	//insertUserH (hm,u3);
	//insertUserH (hm,u4);
	/*int res;
	res = (int) g_list_length(lista);
	printf("O tamanho da lista ligada é : %d\n",res);*/
	return 0;
}