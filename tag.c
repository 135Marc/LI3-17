#include "tag.h"

/**
* @file tag.c
* @brief Estrutura das tags;
*/

typedef struct Tags {
	long id; /**< Identificador da tag*/
	char* name; /**< Nome da tag */
	int counter; /**< Contador da tag */
}Tags;


/**	@brief Função que cria uma tag
*   @param long ID
*   @param char* nome  
*	@return Tag
*/
Tag new_Tag (long id,char* name) {
	Tag t = malloc(sizeof(Tags));
	t->id = id;
	t->name = mystrdup(name);
	t->counter=0;
	return t;
}


/**	@brief Função que extrai uma tag da estrutura
*   @param Tag
*	@return long
*/
long getTagID (Tag t) {
	return t->id;
}


/**	@brief Função que extrai o nome da tag da estrutura
*   @param Tag
*	@return char*
*/
char* getTagName (Tag t) {
	return t->name;
}


/**	@brief Função que extrai o contador da tag da estrutura
*   @param Tag
*	@return int contador
*/
int get_TagCounter(Tag t) {
	return t->counter;
}


/**	@brief Função que liberta o espaço utilizado na estrutura
*   @param Tag 
*/
void freeTag (Tag t) {
	if (t) {
		free(t->name);
		t->counter=0;
		free(t);
	}
}


/**	@brief Função que faz os printf
*   @param Tag 
*/
void printTag (Tag t) {
	if (t) {
		printf("ID : %li\n",getTagID(t));
		printf("Name : %s\n",getTagName(t));
		printf("Count : %d\n",get_TagCounter(t));
	}
}


/**	@brief Função que incrementa o contador das tags
*   @param Tag 
*/
void add_Tag_Count(Tag t) {
	t->counter+=1;
}


/**	@brief Função que compara os identificadores de duas tags
*   @param Tag t1
*   @param Tag t2
*	@return int retorna 1 se a tag t1 for maior que t2 e -1 caso contrario
*/
int cmpTagID (Tag t1,Tag t2) {
	long r1 = getTagID(t1);
	long r2 = getTagID(t2);
	return (r1>r2) ? 1 : -1;
}


/**	@brief Função que compara o contador de duas tags
*   @param Tag t1
*   @param Tag t2
*	@return int retorna -1 se o contador da primeira tag for maior do que o da segunda e 1 caso contrario
*/
int cmpCounter (Tag t1,Tag t2) {
	int r1 = get_TagCounter(t1);
	int r2 = get_TagCounter(t2);
	if (r1==r2) return cmpTagID(t1,t2);
	return (r1>r2) ? -1 : 1;
}