	#ifndef COMMON_H_
	#define COMMON_H_
	#include <stdio.h>
	#include <string.h>
	#include <stdlib.h>
	#include <glib.h>
	#include <gmodule.h>
	#include "./date.h"
	char* split_string (char* s,int i);
	int inTitle (char* s1, char* s2);
	int cmpVal (int a,int b);
	char * mystrdup (const char *s);
	int cmpfunci (const void * a, const void * b);
	int inTag (char* tags, char* tag);
	char* stringTill(char* string, char c);
	char* sortDate (char* date);
	int elemChar (char* string, char c);
	char* stringBetween (char* string, char c);
	char* stringAfter (char* string, char c);
	Date dateFromPost (char* date);
	int cmpDates (Date d1, Date d2);
	int betweenDate (Date d,Date x,Date y);

#endif
