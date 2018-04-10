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

int get_Day (Date d) {
	return d -> day;
}

int get_Month (Date d) {
	return d -> month;
}

int get_Year (Date d) {
	return d -> year;
}

void printDate (Date d) {
	if (d){
	printf("Year : %d\n",d->year);
	printf("Month : %d\n",d->month);
	printf("Day: %d\n",d->day);
	printf("\n");
}
}
