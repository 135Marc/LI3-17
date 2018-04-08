#include "user.h"

typedef struct Users {
	int reputation;
	long id;
	char* displayname;
	char* shortbio;
} Users;

User new_User(int reputation, long id,char* displayname,char* shortbio) {
	User new = malloc(sizeof(Users));
	new->reputation=reputation;
	new->id=id;
	new->displayname = malloc(sizeof(char*));
	new->displayname = displayname;
	new->shortbio = malloc(sizeof(char*));
	new->shortbio=shortbio;
	return new;
}

void freeUser (User u) {
	if (u) {
		free(u->displayname);
		free(u->shortbio);
		free(u);
	}
}

int getRep (User u) {
	return u->reputation;
}

long getIDUser (User u) {
	return u->id;
}

char* getDisplayName (User u) {
	return u->displayname;
}

char* getShortBio (User u) {
	return u->shortbio;
}

void printUser (User u) {
	printf("Display do utilizador : %s\n",getDisplayName(u));
	printf("ID do utilizador : %li\n",getIDUser(u));
	printf("Reputação : %d\n",getRep(u));
	printf("About me: %s\n",getShortBio(u));
}

long cmpUserID (User u1, User u2) {
	long r1 = getIDUser(u1);
	long r2 = getIDUser(u2);
	if (r1==r2) return 0;
	return (r1>r2) ? -1 : 1;
}
/*
int main () {
	User u = new_User(600,50,"asshole","Cago-te na fronha");
	User u1 =new_User(550,49,"merdas","Cago-te na cozinha");
	User u2=new_User(510,20,"Jacker","Só fumo umas merdas para me divertir");
	User u3=new_User(20,49,"merdas","Cago-te na cozinha");
	User u4=new_User(2000,49,"asshole","Cago-te na fronha");
	GList* lista = NULL;
	lista = g_list_insert_sorted(lista,u,(GCompareFunc) cmpfunci);
	lista = g_list_insert_sorted(lista,u1,(GCompareFunc) cmpfunci);
	lista= g_list_insert_sorted(lista,u2,(GCompareFunc) cmpfunci);
	lista = g_list_insert_sorted(lista,u3,(GCompareFunc) cmpfunci);
	lista = g_list_insert_sorted(lista,u4,(GCompareFunc) cmpfunci);
	int res;
	res = (int) g_list_length(lista);
	printf("O tamanho da lista ligada é : %d\n",res);
	g_list_foreach(lista , (GFunc) printUser , (User)lista->data);
	return 0;
}*/