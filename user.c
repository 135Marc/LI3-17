#include "user.h"

typedef struct Users {
	int reputation;
	long id;
	char* displayname;
	char* shortbio;
	int postcount;
	LONG_list list10;
} Users;

User new_User(int reputation, long id,char* displayname,char* shortbio) {
	User new = malloc(sizeof(Users));
	new->reputation=reputation;
	new->id=id;
	new->displayname = displayname;
	new->shortbio=shortbio;
	new->postcount=0;
	new->list10 = NULL;
	return new;
}

void freeUser (User u) {
	if (u) {
		free(u->displayname);
		free(u->shortbio);
		free_list(u->list10);
		free(u);
	}
}

int getRep (User u) {
	return u->reputation;
}

long getIDUser (User u) {
	return u->id;
}

int getPostCount (User u) {
	return u->postcount;
}

char* getDisplayName (User u) {
	return u->displayname;
}

char* getShortBio (User u) {
	return u->shortbio;
}

LONG_list getList10 (User u) {
	return u->list10;
}

void setList10 (User u,LONG_list l) {
	u->list10=l;
}

void printUser (User u) {
	printf("Display do utilizador : %s\n",getDisplayName(u));
	printf("ID do utilizador : %li\n",getIDUser(u));
	printf("Reputação : %d\n",getRep(u));
	printf("About me: %s\n",getShortBio(u));
	printf("PostCount : %d\n",getPostCount(u));
	if (getList10(u))print_LONG_list(getList10(u)); 
}

long cmpUserID (User u1, User u2) {
	long r1 = getIDUser(u1);
	long r2 = getIDUser(u2);
	if (r1==r2) return 0;
	return (r1>r2) ? -1 : 1;
}

void add_Post(User u) {
	u->postcount+=1;
}

int cmpPostCount (User u1, User u2) {
	int r1 = getPostCount(u1);
	int r2 = getPostCount(u2);
	if (r1==r2) return 0;
	return (r1>r2) ? -1 : 1;
}
