	#ifndef COMMON_H_
	#define COMMON_H_
	#include <stdio.h>
	#include <string.h>
	#include <stdlib.h>
	#include <glib.h>
	#include <gmodule.h>
	#include "./date.h"
	char * mystrdup (const char *s);
	int cmpfunci (const void * a, const void * b);
	char* stringTill(char* string, char c);
	char* sortDate (char* date);
	int elemChar (char* string, char c);
	char* stringBetween (char* string, char c);
	char* stringAfter (char* string, char c);
	Date dateFromPost (char* date);
	

#endif
