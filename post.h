 #ifndef POST_H_
    
    #define POST_H_
	#include <stdlib.h>
	#include <stdio.h>
	typedef struct Posts *Post;
	Post nPost (long id,long ownerid,int typeid,int score,int answercount,char* title,char* date,char* tags);
	void freePost (Post p);
	long getID (Post p);
	long getOwnerID (Post p);
	int getTypeID (Post p);
	int getScore (Post p);
	int getAnswerCount (Post p);
	char* getTitle (Post p);
	char* getDate (Post p);
	char* getTags (Post p);
	int isQuestion (Post p);
	void printPost (Post p);
	int cmpPostScore (Post u1, Post u2);


#endif