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

int cmpYear (int year1,int year2) {
	if (year1==year2) return 0;
	return (year1>year2) ? -1 : 1;
}

int cmpMonth (int Month1, int Month2) {
	if (Month1==Month2) return 0;
	return (Month1>Month2) ? -1 : 1;
}

int cmpDay (int Day1, int Day2) {
	if (Day1==Day2) return 0;
	return (Day1>Day2) ? -1 : 1;
}

int cmpDate (Date d1, Date d2) {
	if (cmpYear(d1->year,d2->year)==1) return 1;
		else if (cmpYear(d1->year,d2->year)==-1) return -1;
	if (cmpYear(d1->year,d2->year) == 0 && cmpMonth(d1->month,d2->month) == 1) return 1;
		else if (cmpYear(d1->year,d2->year) == 0 && cmpMonth(d1->month,d2->month) == -1) return -1;
	if (cmpYear(d1->year,d2->year) == 0 && cmpMonth(d1->month,d2->month) == 0 && cmpDay(d1->day,d2->day)==1) return 1;
		else if (cmpYear(d1->year,d2->year) == 0 && cmpMonth(d1->month,d2->month) == 0 && cmpDay(d1->day,d2->day)) return -1;	
	return 0;
}

int main () {
	Date d1 = nDate(4,4,2017);
	Date d2 = nDate(5,4,2017);
	printf("%d\n",cmpDate(d1,d2));
	return 0;
}