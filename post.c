#include "post.h"

typedef struct Posts {
	long id,ownerid;
	int typeid,score,answercount;
	char* title;
	char* date;
	char* tags;
} Posts;

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

//Retorna a string resultante até um caracter específico.

char* stringTill(char* string, char c) {
	int i;
	char* res = malloc(sizeof(char*));
	for(i=0;string[i]!=c ;i++) {
		res[i]=string[i];
	}
	return res;
}

char* sortDate (char* date) {
	char *res = stringTill(date,'T');
	return res;
}

//Retorna a string resultante após dois caracteres específico.

char* stringAfter (char* string, char c,int n) {
	int i,count;
	i=count=0;
	char* res = malloc(sizeof(char*));
	while(string[i]!='\0' && count < n){
		if (string[i]==c) count+=1;
		i+=1;
	}
	for (i;string[i]!='\0';i++) {
		res[i] = string[i];
	}
	return res;
}

char* stringBetween (char* string, char c) {
	int i,count,j;
	i=count=j=0;
	char* res = malloc(sizeof(char*));	
	while (string[i]!='\0' && count==0) {
		if (string[i]==c) count+=1;
		i+=1;
	}
	for (i;string[i]!='\0' && count < 2;i++) {
		res[j++]=string[i];
	}
	return res;
}




Date postDate (char* date) {
	Date d;
	char* year = stringTill(date,'-');
	char* month = stringBetween(date,'-');
	char *day = stringAfter(date,'-',2);
	int y = atoi(year);
	int m = atoi(month);
	int dd = atoi(day);
	d = nDate(y,m,dd);
	return d;
}
/*
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
	/*Post abc= nPost(1,2,3,16,14,"Teste1","2017-03-02");
	
	abc->next=nPost(4,0,4,15,13,"Teste2","2017-04-01");
	abc->next->next = nPost(5,3,3,10,16,"lll","2017-03-03");
	abc->next->next->next = nPost(5,2,3,11,24,"lll","2017-03-05");
	abc->next->next->next->next = nPost(5,0,3,2,15,"lll","2017-03-01");
	int i,*scores=nBestScores(abc,1);
	for(i=0;i<1;i++) printf("%d\n",scores[i]);
	/*printf("Tamanho da lista ligada: %d\n",llistSize(abc));
	printf(" Post count do user com id 0 : %li\n ",postcount(abc,0));*/ }
	
