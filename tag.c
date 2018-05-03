#include "tag.h"
typedef struct Tags {
	long id;
	char* name;
	int counter;
}Tags;

Tag new_Tag (long id,char* name) {
	Tag t = malloc(sizeof(Tags));
	t->id = id;
	t->name = mystrdup(name);
	t->counter=0;
	return t;
}

long getTagID (Tag t) {
	return t->id;
}

char* getTagName (Tag t) {
	return t->name;
}

int get_TagCounter(Tag t) {
	return t->counter;
}

void freeTag (Tag t) {
	if (t) {
		free(t->name);
		t->counter=0;
		free(t);
	}
}

void printTag (Tag t) {
	if (t) {
		printf("ID : %li\n",getTagID(t));
		printf("Name : %s\n",getTagName(t));
		printf("Count : %d\n",get_TagCounter(t));
	}
}

void add_Tag_Count(Tag t) {
	t->counter+=1;
}

int cmpTagID (Tag t1,Tag t2) {
	long r1 = getTagID(t1);
	long r2 = getTagID(t2);
	return (r1>r2) ? 1 : -1;
}

int cmpCounter (Tag t1,Tag t2) {
	int r1 = get_TagCounter(t1);
	int r2 = get_TagCounter(t2);
	if (r1==r2) return cmpTagID(t1,t2);
	return (r1>r2) ? -1 : 1;
}