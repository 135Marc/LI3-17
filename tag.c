#include "tag.h"
#include <stdio.h>
#include <string.h>
typedef struct Tags {
	char* name;
	struct Tags* next;
} Tags;

char* getTag(Tag t) {
	return t->name;
}

int elemTag (Tag t,char* t1) {
	for (t;t!=NULL;t=t->next) if (strcmp(t->name,t1) == 0) return 1;
		return 0;
}

Tag nTag (char* tag) {
	Tag new = malloc(sizeof(Tags));
	new->name=malloc(sizeof(char*));
	new->name=tag;
	new->next=NULL;
	return new;
}

int main () {
	Tag res = nTag("C");
	res->next = nTag("Java");
	res->next->next = nTag("iOS");
	char* look = "C";
	printf ("%d\n",elemTag(res,"Java"));
}
/* Todas as merdas para as Tags serão feitas aqui */
