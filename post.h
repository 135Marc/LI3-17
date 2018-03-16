 #ifndef post_h_
    #define post_h_
	#include <stdlib.h>
	#include <stdio.h>
	#include <string.h>
	#include "date.h"
	typedef struct Posts *Post;
	typedef struct Posts p;

	Post nPost (long id,long ownerid,int typeid,int score,int answercount,char* title,char* date,char* tags);
	void freePost (Post p);
	int postcount (Post p,long oid);
	Date postDate (char* date);
#endif