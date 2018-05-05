#include <stdlib.h>
#include "list.h"

struct llist {
  int size;
  long * list;
};


/** @brief Função que cria uma lista 
*   @param int tamanho
*   @return LONG_list 
*/
LONG_list create_list(int size) {
    if(size <= 0) return NULL;
    LONG_list l = malloc(sizeof(struct llist));
    l->size = size;
    l->list = malloc(sizeof(long) * size);
    return l;
}


/** @brief Função que extrai o elemento da lista que esta num certo indice
*   @param LONG_list 
*   @param int indice
*   @return long 
*/
long get_list(LONG_list l, int index) {
    return l->list[index]; 
}


/** @brief Função que insere o elemento com um dado valor, numa lista, num certo indice
*   @param LONG_list 
*   @param int indice
*   @param long valor
*/
void set_list(LONG_list l, int index, long value) {
    l->list[index] = value;
}


/** @brief Função que liberta o espaço que ja foi utilizado na estrutura
*   @param LONG_list 
*   @param int indice
*   @param long valor
*/
void free_list(LONG_list l) {
    if(l) {
        free(l->list);
        free(l);
    }
}



/** @brief Função que faz printf
*   @param LONG_list 
*/
void print_LONG_list (LONG_list l) {
    int i,size=l->size;
    for (i=0;i<size;i++) printf("%li\n",l->list[i]);
}


