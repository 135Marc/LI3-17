#include "post.h"

/**
* @file post.c
* @brief Estrutura dos posts;
*/

typedef struct Posts {
	long id; /**< Identificador do post */
	long ownerid /**< Identificador do autor do post */
	long parentid; /**< Identificador do post parente */
	int typeid; /**< Identificador de tipo do post */
	int score; /**< Score do post */
	int answercount; /**< Contagem de respostas do post */
	int commentcount; /**< Contagem de comenários do post */
	char* title; /**< Titulo do post */
	char* date; /**< Data do post (em string) */
	char* tags; /**< Tags do post */
	Date d; /**< Data do post (formato Date)*/
}Posts;



/**	@brief Função que cria um post
*   @param long ID
*   @param long ID do criador do post
*   @param long ID do parente
*   @param long ID do tipo de post
*   @param int score
*   @param int contador de perguntas
*   @param int contador de comentarios
*   @param char* titulo do post
*   @param char* data do post
*   @param char* tag do post
*	@return Post
*/
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


/**	@brief Função que liberta o espaço utilizado por um Post na memoria
*   @param Post
*/
void freePost (Post p) {
	if (p) {
		free(p->title);
		free(p->date);
		free(p->tags);
		p->d=NULL;
		free(p);
	}
}



/**	@brief Função que devolve o identificador do Post
*   @param Post
*   @return long
*/
long getID (Post p) {
	return p->id;
}


/**	@brief Função que devolve o identificador do criador do Post
*   @param Post
*   @return long
*/
long getOwnerID (Post p) {
	return p->ownerid;
}


/**	@brief Função que devolve o identificador do parente caso seja uma resposta
*   @param Post
*   @return long
*/
long getParentID (Post p) {
	return p->parentid;
}


// Devolver o tipo de um Post
/**	@brief Função que devolve o tipo do post
*   @param Post
*   @return int
*/
int getTypeID (Post p) {
	return p->typeid;
}


/**	@brief Função que devolve o score de um Post
*   @param Post
*   @return int 
*/
int getScore (Post p) {
	return p->score;
}


// Devolver o número de respostas presentes num Post
/**	@brief Função que devolve o numero de respostas presentes num Post
*   @param Post
*   @return int 
*/
int getAnswerCount (Post p) {
	return p->answercount;
}


/**	@brief Função que devolve o numero de comentarios de um Post
*   @param Post
*   @return int 
*/
int getCommentCount (Post p) {
	return p->commentcount;
}


/**	@brief Função que devolve o titulo de um Post
*   @param Post
*   @return char*
*/
char* getTitle (Post p) {
	return p->title;
}


/**	@brief Função que devolve a data de um Post
*   @param Post
*   @return char*
*/
char* getDate (Post p) {
	return p->date;
}


// Devolver as tags presente num Post(caso este seja uma questão)
/**	@brief Função que devolve as tags presentes num Post
*   @param Post
*   @return char*
*/
char* getTags (Post p) {
	return p->tags;
}


/**	@brief Função que devolve a data de um Post
*   @param Post
*   @return long
*/
void set_Date(Post p) {
	Date d1 = dateFromPost(getDate(p));
	p-> d = d1;
}


/**	@brief Função que devolve a data de um Post
*   @param Post
*   @return long
*/
Date get_DDate (Post p) {
	Date d = p->d;
	return d;
}


// Verifica se um Post é uma pergunta ou resposta
/**	@brief Função que devolve se um Post e pergunta ou resposta
*   @param Post
*   @return int retorna 1 se for uma pergunta e 0 caso contrario
*/
int isQuestion (Post p) {
	return (getTypeID(p)==1) ? 1 : 0;
}


/**	@brief Função que devolve se um Post e uma resposta
*   @param Post
*   @return int retorna 1 se for resposta e 0 caso contrario
*/
int isAnswer (Post p) {
	return (getTypeID(p)==2) ? 1 : 0;
}


/**	@brief Função que faz os printf 
*   @param Post
*/
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


/**	@brief Função que compara os identificadores de dois Posts
*   @param Post u1
*   @param Post u2
*   @return int retorna -1 se o ID do primeiro post for maior que o segundo e 1 caso contrario
*/
int cmpPostID (Post u1, Post u2) {
	long r1 = getID(u1);
	long r2 = getID(u2);
	return (r1>r2) ? -1 : 1;
}


/**	@brief Função que compara o score de dois Posts
*   @param Post u1
*   @param Post u2
*   @return int retorna -1 se o score do primeiro post for maior que o segundo e 1 caso contrario
*/
int cmpPostScore (Post u1, Post u2) {
	int r1 = getScore(u1);
	int r2 = getScore(u2);
	if (r1==r2) return cmpPostID (u1,u2);
	return (r1>r2) ? -1 : 1;
}


/**	@brief Função que compara o numero de respostas de dois Posts
*   @param Post u1
*   @param Post u2
*   @return int retorna -1 se o numero de respostas do primeiro post for maior que o segundo e 1 caso contrario
*/
int cmpAnswerCount (Post p1, Post p2) {
	int r1 = getAnswerCount(p1);
	int r2 = getAnswerCount(p2);
	if (r1==r2) return cmpPostID(p1,p2);
	return (r1>r2) ? -1 : 1;
}


/**	@brief Função que compara as datas de dois Posts
*   @param Post u1
*   @param Post u2
*   @return int retorna -1 se a data do primeiro post for maior que o segundo e 1 caso contrario
*/
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