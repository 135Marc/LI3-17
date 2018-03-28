#include "user.h"

typedef struct Users {
	int reputation;
	long id;
	char* displayname;
} Users;

User nUser(int reputation, long id,char* display) {
	User new = malloc(sizeof(Users));
	new->reputation=reputation;
	new->id=id;
	new->displayname = malloc(sizeof(char*));
	new->displayname = display;
	return new;
}

void freeUser (User u) {
	if (u) {
		free(u->displayname);
		free(u);
	}
}

int getRep (User u) {
	return u->reputation;
}

long getID (User u) {
	return u->id;
}

char* getDisplayName (User u) {
	return u->displayname;
}

int cmpfunc (const void * a, const void * b) {
   return ( *(int*)b - *(int*)a );
}

void printUser (User u) {
	printf("Display do utilizador : %s\n",u->displayname);
	printf("ID do utilizador : %li\n",u->id);
	printf("Reputação : %d\n",u->reputation);
}

int main () {
	User u = nUser(600,50,"asshole");
	User u1 =nUser(550,49,"merdas");
	User u2=nUser(510,20,"Jacker");
	User u3=nUser(20,49,"merdas");
	User u4=nUser(2000,49,"asshole");
	GList* lista = NULL;
	lista = g_list_insert_sorted(lista,u,(GCompareFunc) cmpfunc);
	lista = g_list_insert_sorted(lista,u1,(GCompareFunc) cmpfunc);
	lista= g_list_insert_sorted(lista,u2,(GCompareFunc) cmpfunc);
	lista = g_list_insert_sorted(lista,u3,(GCompareFunc) cmpfunc);
	lista = g_list_insert_sorted(lista,u4,(GCompareFunc) cmpfunc);
	int res;
	res = (int) g_list_length(lista);
	printf("O tamanho da lista ligada é : %d\n",res);
	g_list_foreach(lista , (GFunc) printUser , (User)lista->data);
	return 0;
}


