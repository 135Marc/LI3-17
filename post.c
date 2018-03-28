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
	return (strcmp(res,name)==0) ? 1 : 0;	
}

int isQuestion (Post p) {
	return (getTypeID(p)==1) ? 1 : 0;
}

int main () {
	return 0;
}
	
