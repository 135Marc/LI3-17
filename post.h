 #ifndef POST_H_
    
    #define POST_H_
	#include <stdlib.h>
	#include <stdio.h>
	#include <string.h>
	#include "./common.h"
	#include "./date.h"
	typedef struct Posts *Post;
	Post nPost (long id,long ownerid,long parentid,int typeid,int score,int answercount,int commentcount,char* title,char* date,char* tags);
	void freePost (Post p);
	long getID (Post p);
	long getOwnerID (Post p);
	long getParentID (Post p);
	int getTypeID (Post p);
	int getScore (Post p);
	int getAnswerCount (Post p);
	int getCommentCount (Post p);
	char* getTitle (Post p);
	char* getDate (Post p);
	char* getTags (Post p);
	void set_Date(Post p);
	Date get_DDate (Post p);
	int isQuestion (Post p);
	int isAnswer (Post p);
	void printPost (Post p);
	int cmpPostScore (Post u1, Post u2);
	int cmpAnswerCount (Post p1, Post p2);
	int cmpDate (Post p1, Post p2);


#endif