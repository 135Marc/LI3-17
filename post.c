#include "post.h"

typedef struct Posts {
	long id,ownerid;
	int typeid,score,answercount;
	char* title;
	char* date;
	char* tags;
}Posts;

Post nPost (long id,long ownerid,int typeid,int score,int answercount,char* title,char* date,char* tags) {
	Post new = malloc(sizeof(Posts));
	new->title=malloc(sizeof(char*));
	new->date = malloc(sizeof(char*));
	new->tags=malloc(sizeof(char*));
	new->id=id;
	new->ownerid=ownerid;
	new->typeid=typeid;
	new->score=score;
	new->answercount=answercount;
	new->title=title;
	new->date=date;
	new->tags=tags;
	return new;
}

void freePost (Post p) {
	if (p) {
		free(p->title);
		free(p->date);
		free(p);
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

char* getDate (Post p) {
	return p->date;
}

char* getTags (Post p) {
	return p->tags;
}

int elemTag (char* name,char* tag) {
	char* res = strstr(name,tag);
	(strcmp(res,name)==0) ? 1 : 0;	
}

int isQuestion (Post p) {
	(getTypeID(p)==1) ? 1 : 0;
}

/*
int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
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
	int *res=malloc(N*sizeof(int)),*answer=arrayScore(p);
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
	int len = llistSize(p);
	int *res = malloc(len*sizeof(int));
	int i=0;
	for(p;p!=NULL;p=p->next) res[i++] = getAnswerCount(p);
	qsort(res,i,sizeof(int),cmpfunc);
	return res;	
} 

// Devolve as N respostas mais votadas!

int* nBestAnswers (Post p,int N) {
	int i,j=0,size,d;
	int *res=malloc(N*sizeof(int)),*answers=arrayAnswerCount(p);
	size=llistSize(p)-1;
	d=size-N;
	for(i=size;i>=d;i--) {
		res[j++]=answers[i];
	}
	return res;
}
*/

int main () {
	return 0;
}
	
