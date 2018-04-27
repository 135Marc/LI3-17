#include "users.h"

typedef struct Users {
	int reputation;
	long id;
	char* displayname;
	char* shortbio;
	int postcount;
} Users;

User new_User(int reputation, long id,char* displayname,char* shortbio) {
	User new = malloc(sizeof(Users));
	new->reputation=reputation;
	new->id=id;
	new->displayname = mystrdup(displayname);
	new->shortbio= mystrdup(shortbio);
	new->postcount=0;
	return new;
}

void freeUser (User u) {
	if (u) {
		free(u->displayname);
		free(u->shortbio);
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

void printUser (User u) {
	printf("Display do utilizador : %s\n",getDisplayName(u));
	printf("ID do utilizador : %li\n",getIDUser(u));
	printf("Reputação : %d\n",getRep(u));
	printf("About me: %s\n",getShortBio(u));
	printf("PostCount : %d\n",getPostCount(u));
}

int cmpUserID (User u1, User u2) {
	long id1 = getIDUser(u1);
	long id2 = getIDUser(u2);
	return (id1>id2) ? -1 : 1;
}

int cmpRep (User u1, User u2) {
	int r1 = getRep(u1);
	int r2 = getRep(u2);
	if (r1==r2) return cmpUserID(u1,u2);
	return (r1>r2) ? -1 : 1;
}

int cmpPostCount (User u1, User u2) {
	int r1 = getPostCount(u1);
	int r2 = getPostCount(u2);
	if (r1==r2) return cmpUserID(u1,u2);
	return (r1>r2) ? -1 : 1;
}

void add_Post(User u) {
	u->postcount+=1;
}