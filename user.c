#include <string.h>
#include <stdlib.h>
#include "user.h"
#include "common.h"

/**
* @file user.c
* @brief Estrutura USER;
*/


struct user {
  char* bio;
  long posts[10];
};


/** @brief Função que cria um user
*   @param char* bio
*   @param long* historico de posts
*   @return USER 
*/
USER create_user(char* bio, long* post_history) {
  USER u = malloc(sizeof(struct user)); 
  u->bio = mystrdup(bio);
  memcpy(u->posts, post_history, sizeof(long) * 10);
  return u;
}


/** @brief Função que extrai a bio de um user
*   @param USER
*   @return char* 
*/
char* get_bio(USER u) {
  if(u)
    return u->bio;
  return NULL;
}


/** @brief Função que extrai os 10 ultimos posts do user
*   @param USER
*   @return long*
*/
long* get_10_latest_posts(USER u) {
  long* r = malloc(sizeof(long)*10);
  memcpy(r, u->posts, sizeof(long)*10);
  return r;
}


/** @brief Função que liberta o espaço utilizado na estrutura
*   @param USER
*/
void free_user(USER u) {
  if(u) {
    free(u->bio);
    free(u);
  }
}


/** @brief Função que faz os printf
*   @param USER
*/
void print_USER (USER u) {
    int i;
    long* l = get_10_latest_posts(u);
    char* shit = get_bio(u);
    printf("%s\n",shit);
    for (i=0;i<10;i++) printf("%li\n",l[i]);
}
