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

