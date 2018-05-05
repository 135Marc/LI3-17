#include "users.h"

typedef struct Users {
	int reputation;
	long id;
	char* displayname;
	char* shortbio;
	int postcount;
} Users;



/**	@brief Função que cria um user
*   @param int reputaçao
*   @param long ID
*   @param char* nome do utilizador 
*   @param char* shortbio
*	@return User 
*/
User new_User(int reputation, long id,char* displayname,char* shortbio) {
	User new = malloc(sizeof(Users));
	new->reputation=reputation;
	new->id=id;
	new->displayname = mystrdup(displayname);
	new->shortbio= mystrdup(shortbio);
	new->postcount=0;
	return new;
}


/**	@brief Função que liberta a estrutura user da memoria
*   @param User
*/
void freeUser (User u) {
	if (u) {
		free(u->displayname);
		free(u->shortbio);
		u->postcount=0;
		free(u);
	}
}


/**	@brief Função que extrai a reputaçao do user
*   @param User
*	@return int reputaçao
*/
int getRep (User u) {
	return u->reputation;
}


/**	@brief Função que extrai o identificador do user
*   @param User
*	@return long ID do user
*/
long getIDUser (User u) {
	return u->id;
}


/**	@brief Função que extrai o contador de posts do user
*   @param User
*	@return int contador de posts
*/
int getPostCount (User u) {
	return u->postcount;
}


/**	@brief Função que extrai o nome do user
*   @param User
*	@return char* nome do user
*/
char* getDisplayName (User u) {
	return u->displayname;
}


/**	@brief Função que extrai a shorbio do user
*   @param User
*	@return char* shortbio
*/
char* getShortBio (User u) {
	return u->shortbio;
}


/**	@brief 
*   @param User
*/
void printUser (User u) {
	printf("Display do utilizador : %s\n",getDisplayName(u));
	printf("ID do utilizador : %li\n",getIDUser(u));
	printf("Reputação : %d\n",getRep(u));
	printf("About me: %s\n",getShortBio(u));
	printf("PostCount : %d\n",getPostCount(u));
}


/**	@brief Função que compara os ID's de dois users
*   @param User u1 utilizador 1
*   @param User u2 utilizador 2
*	@return int retorna -1 se o u1 for maior que u2 e 1 caso contrario
*/
int cmpUserID (User u1, User u2) {
	long id1 = getIDUser(u1);
	long id2 = getIDUser(u2);
	return (id1>id2) ? -1 : 1;
}


/**	@brief Função que compara a reputaçao de dois users
*   @param User u1 utilizador 1
*   @param User u2 utilizador 2
*	@return int retorna -1 se u1 for maior que u2 e 1 caso contrario
*/
int cmpRep (User u1, User u2) {
	int r1 = getRep(u1);
	int r2 = getRep(u2);
	if (r1==r2) return cmpUserID(u1,u2);
	return (r1>r2) ? -1 : 1;
}


/**	@brief Função que compara o contador de post de dois users
*   @param User u1 utilizador 1
*   @param User u2 utilizador 2
*	@return int retorna -1 se u1 for maior que u2 e 1 caso contrario
*/
int cmpPostCount (User u1, User u2) {
	int r1 = getPostCount(u1);
	int r2 = getPostCount(u2);
	if (r1==r2) return cmpUserID(u1,u2);
	return (r1>r2) ? -1 : 1;
}


/**	@brief Função que incrementa o numero de posts que o user faz
*   @param User
*/
void add_Post(User u) {
	u->postcount+=1;
}