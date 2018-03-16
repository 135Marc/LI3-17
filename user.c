#include "user.h"
#include "post.h"

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
	User tmp=NULL;
	for(u;u!=NULL;u=u->next) {
		if(u->next!=NULL) tmp=u->next;
		free(u->displayname);
		free(u);
		u=tmp;
	}
}
/*
int llistSize (User u) {
	int r=0;
	for(u;u!=NULL;u=u->next) r++;
	return r; 
}
*/
int getRep (User u) {
	return u->reputation;
}

long getID (User u) {
	return u->id;
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

int main () {/*
	User u = nUser(600,50,"asshole");
	u->next=nUser(550,49,"merdas");
	u->next->next=nUser(510,20,"Jacker");
	u->next->next->next=nUser(20,49,"merdas");
	u->next->next->next->next=nUser(2000,49,"asshole");
	int* ordenado = nBest(u,4);
	int i;
	for(i=0;i<4;i++) printf("%d\n",ordenado[i]);
	int res = postcount(u->p,49);*/
}
