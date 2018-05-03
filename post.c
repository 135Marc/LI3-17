#include "post.h"

typedef struct Posts {
	long id,ownerid,parentid;
	int typeid,score,answercount,commentcount;
	char* title;
	char* date;
	char* tags;
	Date d;
}Posts;

// Cria um novo Post 

Post nPost (long id,long ownerid,long parentid,int typeid,int score,int answercount,int commentcount,char* title,char* date,char* tags) {
	Post new = malloc(sizeof(Posts));
	new->id=id;
	new->ownerid=ownerid;
	new->parentid=parentid;
	new->typeid=typeid;
	new->score=score;
	new->answercount=answercount;
	new->commentcount = commentcount;
	new->title=mystrdup(title);
	new->date=mystrdup(date);
	new->tags=mystrdup(tags);
	return new;
}

// Liberta o espaço utilizado por um Post na memória

void freePost (Post p) {
	if (p) {
		free(p->title);
		free(p->date);
		free(p->tags);
		p->d=NULL;
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

// Devolver o "ID Parente" caso seja uma resposta

long getParentID (Post p) {
	return p->parentid;
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

int getCommentCount (Post p) {
	return p->commentcount;
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
	Date d = p->d;
	return d;
}
// Verifica se um Post é uma pergunta ou resposta

int isQuestion (Post p) {
	return (getTypeID(p)==1) ? 1 : 0;
}

int isAnswer (Post p) {
	return (getTypeID(p)==2) ? 1 : 0;
}

void printPost (Post p) {
	printf("ID: %li\n",getID(p));
	printf("ID do Utilizador : %li\n",getOwnerID(p));
	printf("Parent ID : %li\n", getParentID(p));
	printf("ID_Type : %d\n",getTypeID(p));
	printf("Score: %d\n",getScore(p));
	printf("Answer_Count : %d\n",getAnswerCount(p));
	printf("Comment_Count : %d\n",getCommentCount(p));
	if (getTitle(p)!=NULL) printf("Título : %s\n",getTitle(p));
	if (getDate(p)!=NULL) printf("Data : %s\n",getDate(p));
	if (getTags(p)!=NULL)printf("Tags : %s\n",getTags(p));
	printDate(get_DDate(p));
}

int cmpPostID (Post u1, Post u2) {
	long r1 = getID(u1);
	long r2 = getID(u2);
	return (r1>r2) ? -1 : 1;
}

int cmpPostScore (Post u1, Post u2) {
	int r1 = getScore(u1);
	int r2 = getScore(u2);
	if (r1==r2) return cmpPostID (u1,u2);
	return (r1>r2) ? -1 : 1;
}

int cmpAnswerCount (Post p1, Post p2) {
	int r1 = getAnswerCount(p1);
	int r2 = getAnswerCount(p2);
	if (r1==r2) return cmpPostID(p1,p2);
	return (r1>r2) ? -1 : 1;
}

int cmpDate (Post p1, Post p2) {
	Date d1 = dateFromPost(getDate(p1));
	Date d2 = dateFromPost(getDate(p2));
	int year1 = get_Year(d1);
	int year2 = get_Year(d2);
	int month1 = get_Month(d1);
	int month2 = get_Month(d2);
	int day1 = get_Day(d1);
	int day2 = get_Day(d2);
	freeDate(d1);
	freeDate(d2);
	if (cmpVal(year1,year2)==1) return 1;
		else if (cmpVal(year1,year2)==-1) return -1;
	if (cmpVal(year1,year2) == 0 && cmpVal(month1,month2) == 1) return 1;
		else if (cmpVal(year1,year2) == 0 && cmpVal(month1,month2) == -1) return -1;
	if (cmpVal(year1,year2) == 0 && cmpVal(month1,month2) == 0 && cmpVal(day1,day2)==1) return 1;
		else if (cmpVal(year1,year2) == 0 && cmpVal(month1,month2) == 0 && cmpVal(day1,day2)==-1) return -1;	
	return cmpPostID(p1,p2);
}