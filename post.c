#include "post.h"

typedef struct Posts {
	long id,ownerid;
	int typeid,score,answercount;
	char* title;
	char* date;
	char* tags;
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

// Verifica se um Post é uma pergunta ou resposta

int isQuestion (Post p) {
	return (getTypeID(p)==1) ? 1 : 0;
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
}

int cmpPostScore (Post u1, Post u2) {
	int r1 = getScore(u1);
	int r2 = getScore(u2);
	if (r1==r2) return 0;
	return (r1>r2) ? -1 : 1;
}