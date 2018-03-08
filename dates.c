#include "date.h"

typedef struct dates {
	int day;
	int month;
	int year;
}Dates;

Date nDate (int day,int month,int year) {
	Date new = malloc(sizeof(Dates));
	new -> day = day;
	new -> month= month;
	new -> year = year;
	return new;
}

void freeDate (Date d) {
	free(d);
}

int getDay (Date d) {
	return d -> day;
}

int getMonth (Date d) {
	return d -> month;
}

int getYear (Date d) {
	return d -> year;
}

int cmpVal (int a,int b) {
	if (a==b) return 0;
	return (a>b) ? -1 : 1;
}

int cmpDate (Date d1, Date d2) {
	if (cmpVal(d1->year,d2->year)==1) return 1;
		else if (cmpVal(d1->year,d2->year)==-1) return -1;
	if (cmpVal(d1->year,d2->year) == 0 && cmpVal(d1->month,d2->month) == 1) return 1;
		else if (cmpVal(d1->year,d2->year) == 0 && cmpVal(d1->month,d2->month) == -1) return -1;
	if (cmpVal(d1->year,d2->year) == 0 && cmpVal(d1->month,d2->month) == 0 && cmpVal(d1->day,d2->day)==1) return 1;
		else if (cmpVal(d1->year,d2->year) == 0 && cmpVal(d1->month,d2->month) == 0 && cmpVal(d1->day,d2->day)) return -1;	
	return 0;
}

int main () {
	Date d1 = nDate(6,3,2018);
	Date d2 = nDate(7,3,2018);
	printf("%d\n",cmpDate(d1,d2));
	return 0;
}