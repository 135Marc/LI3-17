#include "post.h"

typedef struct Posts {
	long id,ownerid;
	int typeid,score,answercount;
	char* title;
	char* date;
	char* tags;
	Date d;
}Posts;

// Cria um novo Post 

Post nPost (long id,long ownerid,int typeid,int score,int answercount,char* title,char* date,char* tags) {
	Post new = malloc(sizeof(Posts));
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

// Liberta o espaço utilizado por um Post na memória

void freePost (Post p) {
	if (p) {
		free(p->title);
		free(p->date);
		freeDate(p->d);
		free(p);
	}
}

// Devolver o ID de um Post

long getID (Post p) {
	return p->id;
}

// Devolver o ID do criador de um Post

long getOwnerID (Post p) {
	return p->ownerid;
}

// Devolver o tipo de um Post

int getTypeID (Post p) {
	return p->typeid;
}

// Devolver o score(upvote-downvote) de um Post

int getScore (Post p) {
	return p->score;
}

// Devolver o número de respostas presentes num Post

int getAnswerCount (Post p) {
	return p->answercount;
}

// Devolver o título de um Post

char* getTitle (Post p) {
	return p->title;
}

// Devolver a data(em forma de string) de um Post

char* getDate (Post p) {
	return p->date;
}

// Devolver as tags presente num Post(caso este seja uma questão)

char* getTags (Post p) {
	return p->tags;
}

void set_Date(Post p) {
	Date d1 = dateFromPost(getDate(p));
	p-> d = d1;
}

Date get_DDate (Post p) {
	return p->d;
}
// Verifica se um Post é uma pergunta ou resposta

int isQuestion (Post p) {
	return (getTypeID(p)==1) ? 1 : 0;
}

int inTitle (Post p,char* word) {
	char* title = getTitle(p);
	if (strstr(title,word)==NULL) return 0;
	return 1;
}

void printPost (Post p) {
	printf("ID: %li\n",getID(p));
	printf("ID do Utilizador : %li\n",getOwnerID(p));
	printf("ID_Type : %d\n",getTypeID(p));
	printf("Score: %d\n",getScore(p));
	printf("Answer_Count : %d\n",getAnswerCount(p));
	if (getTitle(p)!=NULL) printf("Título : %s\n",getTitle(p));
	if (getDate(p)!=NULL) printf("Data : %s\n",getDate(p));
	if (getTags(p)!=NULL)printf("Tags : %s\n",getTags(p));
	printDate(get_DDate(p));
}

int cmpPostScore (Post u1, Post u2) {
	int r1 = getScore(u1);
	int r2 = getScore(u2);
	if (r1==r2) return 0;
	return (r1>r2) ? -1 : 1;
}

int cmpAnswerCount (Post p1, Post p2) {
	int r1 = getAnswerCount(p1);
	int r2 = getAnswerCount(p2);
	if (r1==r2) return 0;
	return (r1>r2) ? -1 : 1;
}

int cmpVal (int a,int b) {
	if (a==b) return 0;
	return (a>b) ? -1 : 1;
}

int cmpDate (Post p1, Post p2) {
	Date d1 = dateFromPost(getDate(p1));
	Date d2 = dateFromPost(getDate(p2));
	if (cmpVal(get_Year(d1),get_Year(d2))==1) return 1;
		else if (cmpVal(get_Year(d1),get_Year(d2))==-1) return -1;
	if (cmpVal(get_Year(d1),get_Year(d2)) == 0 && cmpVal(get_Month(d1),get_Month(d2)) == 1) return 1;
		else if (cmpVal(get_Year(d1),get_Year(d2)) == 0 && cmpVal(get_Month(d1),get_Month(d2)) == -1) return -1;
	if (cmpVal(get_Year(d1),get_Year(d2)) == 0 && cmpVal(get_Month(d1),get_Month(d2)) == 0 && cmpVal(get_Day(d1),get_Day(d2))==1) return 1;
		else if (cmpVal(get_Year(d1),get_Year(d2)) == 0 && cmpVal(get_Month(d1),get_Month(d2)) == 0 && cmpVal(get_Day(d1),get_Day(d2))==-1) return -1;	
	return 0;
}

int cmpDates (Date d1, Date d2) {
	if (cmpVal(get_Year(d1),get_Year(d2))==1) return 1;
		else if (cmpVal(get_Year(d1),get_Year(d2))==-1) return -1;
	if (cmpVal(get_Year(d1),get_Year(d2)) == 0 && cmpVal(get_Month(d1),get_Month(d2)) == 1) return 1;
		else if (cmpVal(get_Year(d1),get_Year(d2)) == 0 && cmpVal(get_Month(d1),get_Month(d2)) == -1) return -1;
	if (cmpVal(get_Year(d1),get_Year(d2)) == 0 && cmpVal(get_Month(d1),get_Month(d2)) == 0 && cmpVal(get_Day(d1),get_Day(d2))==1) return 1;
		else if (cmpVal(get_Year(d1),get_Year(d2)) == 0 && cmpVal(get_Month(d1),get_Month(d2)) == 0 && cmpVal(get_Day(d1),get_Day(d2))==-1) return -1;	
	return 0;
}

// Verifica se uma data está entre um dado intervalo de datas.
int betweenDate (Date d,Date x,Date y) {
	return (cmpDates(d,x) <= 0 && cmpDates(d,y) >= 0) ? 1 : 0;
}