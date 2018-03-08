#ifndef __DATE_H__
#define __DATE_H__

	#include <stdlib.h>
	#include <stdio.h>
	typedef struct dates *Date;

	Date nDate(int day, int month, int year);
	void freeDate(Date d);
	int get_Day(Date d);
	int get_Month(Date d); // must return a value between 0 and 11 
	int get_Year(Date d);
	int cmpDate (Date d1, Date d2);
	

#endif