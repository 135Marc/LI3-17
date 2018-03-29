	#ifndef COMMON_H_
	#define COMMON_H_
	#include <stdio.h>
	#include <string.h>
	#include <stdlib.h>
	#include "date.h"
	#include "post.h"
	char* stringTill(char* string, char c);
	char* sortDate (char* date);
	int elemChar (char* string, char c);
	char* stringBetween (char* string, char c);
	char* stringAfter (char* string, char c);
	Date dateFromPost (Post p);
	

#endif
