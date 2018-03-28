#include "pair.h"
#include <string.h>

typedef struct strpair {
	char* s1;
	char* s2;
} STRPAIR;

STR_pair create_pair(char* fst, char* snd) {
	STR_PAIR res = malloc(sizeof(STRPAIR));
	res->s1 = malloc(sizeof(char*));
	res->s1 = strcpy(res->s1,fst);
	res->s2 = malloc(sizeof(char*));
	res->s2= strcpy(res->s2,snd);
	return res;
}

void set_fst(STR_pair pair, char* str) {
	free(pair->s1);
	pair->s1 = malloc(sizeof(char*));
	pair->s1 = strcpy(pair->s1,str);
}

void set_snd(STR_pair pair, char* str) {
	free(pair->s2);
	pair->s2 = malloc(sizeof(char*));
	pair->s2 = strcpy(pair->s2,str);
}

char* get_fst(STR_pair pair) {
	return pair->s1;
}

char* get_snd(STR_pair pair) {
	return pair->s2;
}

void free_pair(STR_pair pair) {
	free(pair->s1);
	free(pair->s2);
	free(pair);
}