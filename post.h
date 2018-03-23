 #ifndef POST_H_
    #define POST_H_
	#include <stdlib.h>
	#include <stdio.h>
	#include <string.h>
	typedef struct Posts *Post;
	#include "date.h"
	#include "common.h"

	Post nPost (long id,long ownerid,int typeid,int score,int answercount,char* title,char* date,char* tags);
	void freePost (Post p);
#endif