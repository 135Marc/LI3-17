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

// Função para fazer postcount NOTA: voltar a meter as tags aqui! //
int postcount (Post p,long oid) {
	int i=0;
	while (p!=NULL) {
		if (p->ownerid==oid) i++;
		p=p->next;
	}
	return i;
} 


int main () {
	Post abc= nPost(1,2,3,10,11,"Fode-te puta");
	abc->next=nPost(4,0,3,1,2,"Caralhinho");
	abc->next->next = nPost(5,2,3,1,2,"lll");
	printf("%d\n",postcount(abc,-1));
	freePost(abc);
	printf("%d\n",postcount(abc,0));
}