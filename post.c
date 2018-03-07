#include "post.h"

typedef struct Posts {
	long id,ownerid;
	int typeid,score,answercount;
	char* title;
	struct Posts* next;
} Posts;

Post nPost (long id,long ownerid,int typeid,int score,int answercount,char* title) {
	Post new = malloc(sizeof(Posts));
	new->title=malloc(sizeof(char*));
	new->id=id;
	new->ownerid=ownerid;
	new->typeid=typeid;
	new->score=score;
	new->answercount=answercount;
	new->title=title;
	return new;
}

void freePost (Post p) {
	Post tmp=NULL;
		while (p!=NULL) {
			if (p->next!=NULL) tmp = tmp->next;
			free(p);
			p=tmp;
		}
}

long getID (Post p) {
	return p->id;
}

long getOwnerID (Post p) {
	return p->ownerid;
}

int getTypeID (Post p) {
	return p->typeid;
}

int getScore (Post p) {
	return p->score;
}

int getAnswerCount (Post p) {
	return p->answercount;
}

char* getTitle (Post p) {
	return p->title;
}

int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

int llistSize (Post p) {
	int r=0;
	for(p;p!=NULL;p=p->next) r++;
	return r; 
}

//Scores ordenados por ordem crescente.

int* arrayScore (Post p) {
	int *res = malloc(4*sizeof(int));
	int i=0;
	for(p;p!=NULL;p=p->next) {
	res[i++] = getScore(p);
}	
	qsort(res,i,sizeof(int),cmpfunc);
	return res;
}
// Devolve os N melhores scores!

int* nBestScores(Post p,int N) {
	int *res=malloc(4*sizeof(int)),*answer=arrayScore(p);
	int i,j=0,size,d;
	size = llistSize(p)-1;
	d=size-N;
	for(i=size;i>=d;i--) {
		res[j++]=answer[i];
	}
	return res;
}

//	Número de respostas ordenadas por ordem crescente

int* arrayAnswerCount (Post p) {
	int *res = malloc(4*sizeof(int));
	int i=0;
	for(p;p!=NULL;p=p->next) res[i++] = getAnswerCount(p);
	qsort(res,i,sizeof(int),cmpfunc);
	return res;	
} 

// Devolve as N respostas mais votadas!

int* nBestAnswers (Post p,int N) {
	int i,j=0,size,d;
	int *res=malloc(4*sizeof(int)),*answers=arrayAnswerCount(p);
	size=llistSize(p)-1;
	d=size-N;
	for(i=size;i>=d;i--) {
		res[j++]=answers[i];
	}
	return res;
}

int postcount (Post p,long oid) {
	int i=0;
	for(p;p!=NULL;p=p->next) {
		if (p->ownerid==oid) i++;
	}
	return i;
} 


int main () {
	Post abc= nPost(1,2,3,16,14,"Teste1");
	abc->next=nPost(4,0,4,15,13,"Teste2");
	abc->next->next = nPost(5,3,3,10,16,"lll");
	abc->next->next->next = nPost(5,2,3,11,24,"lll");
	abc->next->next->next->next = nPost(5,0,3,2,15,"lll");
	int i,*scores=nBestScores(abc,5);
	for(i=0;i<5;i++) printf("%d\n",scores[i]);
	/*printf("Tamanho da lista ligada: %d\n",llistSize(abc));
	printf(" Post count do user com id 0 : %li\n ",postcount(abc,0));*/
	
}