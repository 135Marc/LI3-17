#include "user.h"

typedef struct Users {
	int reputation;
	long id;
	char* displayname;
	char* shortbio;
	LONG_LIST latestposts;
} Users;

User nUser(int reputation, long id,char* display,char* shortbio) {
	User new = malloc(sizeof(Users));
	new->reputation=reputation;
	new->id=id;
	new->displayname = malloc(sizeof(char*));
	new->displayname = display;
	new->shortbio = malloc(sizeof(char*));
	new->shortbio=shortbio;
	new->latestposts= create_list(10);
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

char* getDisplayName (User u) {
	return u->displayname;
}

char* getShortBio (User u) {
	return u->shortbio;
}
void printUser (User u) {
	printf("Display do utilizador : %s\n",getDisplayName(u));
	printf("ID do utilizador : %li\n",getID(u));
	printf("Reputação : %d\n",getRep(u));
	printf("About me: %s\n",getShortBio(u))
}