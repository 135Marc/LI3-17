#include "user.h"

typedef struct Users {
	int reputation;
	double id;
	struct Users* next;
} Users;

User nUser(int reputation, double id) {
	User new = malloc(sizeof(Users));
	new->reputation=reputation;
	new->id=id;
	new->next=NULL;
	return new;
}

void freeUser (User u) {
	User tmp=NULL;
	while (u!=NULL) {
		if(u->next!=NULL) tmp=u->next;
		free(u);
		u=tmp;
	}
}

int getRep (User u) {
	return u->reputation;
}

double getID (User u) {
	return u->id;
}
/*
int getMaxRep (User u) {
	int nextr,maxr;
	int rep=maxr=nextr=0;
	User unext=NULL;
	if (u->next!=NULL) unext=u->next;
	while (u!=NULL & unext !=NULL) {
		rep=getRep(u);
		nextr=getRep(unext);
		if (rep>=nextr && maxr < rep) maxr=rep;
		else  if (nextr>=rep && maxr< nextr) maxr=nextr;
		u=u->next;
		unext=unext->next;
	}
	if (u!=NULL && u->reputation > maxr) maxr=u->reputation;
	return maxr;

}
*/
int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

int* arrayrep (User u) {
	int i=0;
	int *res= malloc(4*sizeof(int));
	while (u!=NULL) {
		res[i++]=u->reputation;
		u=u->next;
	}
	qsort(res, 3, sizeof(int), cmpfunc);
	return res;
} // funca para um número conhecido de elementos


int* nBest (User u,int N,int nelem) {
	int i,j=0;
	int*arr=arrayrep(u),*res=malloc(4*sizeof(int));
	for(i=nelem-1;i!=0;i--) res[j++]=arr[nelem];
	return res;
}
int main () {
	User u = nUser(60,50);
	u->next=nUser(550,49);
	u->next->next=nUser(510,20);
	//u->next->next->next=nUser(20,49);
	int* ordenado = nBest(u,3,3);
	int i;
	for (i=0;i<2;i++) {
		printf ("%d\n",ordenado[i]);
	}
}
