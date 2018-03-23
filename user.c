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
   return ( *(int*)a - *(int*)b );
}

/*
 // Constrói um array de reputações

int* arrayrep (User u) {
	int i=0;
	int *res= malloc(4*sizeof(int));
	while (u!=NULL) {
		res[i++]=u->reputation;
		u=u->next;
	}
	qsort(res, i, sizeof(int), cmpfunc);
	return res;
} 

// Calcula as N melhores reputações

int* nBest (User u,int N) {
	int i,j=0,d,size;
	int*arr=arrayrep(u),*res=malloc(4*sizeof(int));
	size=llistSize(u)-1;
	d = size - N;
	for(i=size;i>=d;i--) res[j++]=arr[i];
	return res;
}*/

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
	lista = g_list_append(lista,u);
	lista = g_list_append(lista,u1);
	lista= g_list_append(lista,u2);
	lista = g_list_append(lista,u3);
	lista = g_list_append(lista,u4);
	
	int res;
	
	res = (int) g_list_length(lista);
	
	printf("O tamanho da lista ligada é : %d\n",res);
	
	g_list_foreach(lista , (GFunc) printUser , (User)lista->data);
	/*for(lista;lista!=NULL;lista=lista->next) {
		printUser((User)lista->data);
		printf("\n");
	}*/
	return 0;
}


