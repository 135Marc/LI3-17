#include "pair.h"

/**
* @file pair.c
* @brief Estrutura dos pares;
*/

struct str_pair {
  char* fst;
  char* snd;
};


/** @brief Função que cria um par de strings
*   @param char* primeiro
*   @param char* segundo
*   @return STR_pair
*/
STR_pair create_str_pair(char* fst, char* snd) {
  STR_pair p = malloc(sizeof(struct str_pair));
  p->fst = mystrdup(fst);
  p->snd = mystrdup(snd);
  return p;
}


/** @brief Função que insere a primeira string na estrutura
*   @param STR_pair 
*   @param char* string
*/
void set_fst_str(STR_pair pair, char* str) {
  free(pair->fst);
  pair->fst = mystrdup(str);
}


/** @brief Função que insere a segunda string na estrutura
*   @param STR_pair 
*   @param char* string
*/
void set_snd_str(STR_pair pair, char* str) {
  free(pair->snd);
  pair->snd = mystrdup(str);
}


/** @brief Função que insere a primeira string na estrutura
*   @param STR_pair 
*   @param char* string
*/
char* get_fst_str(STR_pair pair) {
  return pair? mystrdup(pair->fst) : NULL;
}


/** @brief Função que insere a primeira string na estrutura
*   @param STR_pair 
*   @param char* string
*/
char* get_snd_str(STR_pair pair) {
  return pair? mystrdup(pair->snd) : NULL;
}


/** @brief Função que insere a primeira string na estrutura
*   @param STR_pair 
*   @param char* string
*/
void free_str_pair(STR_pair pair) {
  if(pair) {
    free(pair->fst);
    free(pair->snd);
    free(pair);
  }
}


/** @brief Função que insere a primeira string na estrutura
*   @param STR_pair 
*   @param char* string
*/
void print_pair (STR_pair pair) {
  if (pair==NULL) return;
	if (get_fst_str(pair)!=NULL) printf("Primeiro elemento : %s\n",get_fst_str(pair));
	else printf("NULL\n");
  if (get_snd_str(pair)!=NULL) printf("Segundo elemento : %s\n",get_snd_str(pair));
  else (printf("NULL\n"));
}


struct long_pair {
  long fst;
  long snd;
};


/** @brief Função que um par de longs
*   @param long primeiro
*   @param long segundo
*   @return LONG_pair
*/
LONG_pair create_long_pair(long fst, long snd) {
  LONG_pair p = malloc(sizeof(struct long_pair));
  p->fst = fst; 
  p->snd = snd;
  return p;
}


/** @brief Função que insere o primeiro long na estrutura
*   @param LONG_pair 
*   @param long primeiro
*/
void set_fst_long(LONG_pair pair, long l) {
  pair->fst = l;
}


/** @brief Função que insere o segundo long na estrutura
*   @param LONG_pair 
*   @param long segundo
*/
void set_snd_long(LONG_pair pair, long l) {
  pair->snd = l;
}


/** @brief Função que extrai o primeiro long da estrutura
*   @param LONG_pair 
*   @return long primeiro
*/
long get_fst_long(LONG_pair pair) {
  return pair->fst;
}


/** @brief Função que extrai o segundo long da estrutura
*   @param LONG_pair 
*   @return long segundo
*/
long get_snd_long(LONG_pair pair) {
  return pair->snd;
}


/** @brief Função que liberta o espaço utilizado da estrutura
*   @param LONG_pair 
*/
void free_long_pair(LONG_pair pair) {
    free(pair);
}


/** @brief Função que faz os printf 
*   @param LONG_pair 
*/
void print_long_pair(LONG_pair pair) {
  printf("Questões : %li\n",get_fst_long(pair));
  printf("Respostas : %li\n",get_snd_long(pair));
}

