#include "date.h"

typedef struct date {
	int day;
	int month;
	int year;
} Dates;

Date createDate (int day,int month,int year) {
	Date new = malloc(sizeof(Dates));
	new -> day = day;
	new -> month= month;
	new -> year = year;
	return new;
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

void freeDate (Date d) {
	free(d);
}