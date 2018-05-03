#ifndef TAG_H_

	#define TAG_H_
	#include <stdlib.h>
	#include <stdio.h>
	#include "./common.h"
	typedef struct Tags *Tag;
	Tag new_Tag (long id,char* name);
	long getTagID (Tag t);
	char* getTagName (Tag t);
	int get_TagCounter(Tag t);
	void freeTag (Tag t);
	void printTag (Tag t);
	void add_Tag_Count(Tag t);
	int cmpCounter (Tag t1,Tag t2);

#endif