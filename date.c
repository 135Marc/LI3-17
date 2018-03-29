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
	if (cmpVal(getYear(d1),getYear(d2))==1) return 1;
		else if (cmpVal(getYear(d1),getYear(d2))==-1) return -1;
	if (cmpVal(getYear(d1),getYear(d2)) == 0 && cmpVal(getMonth(d1),getMonth(d2)) == 1) return 1;
		else if (cmpVal(getYear(d1),getYear(d2)) == 0 && cmpVal(getMonth(d1),getMonth(d2)) == -1) return -1;
	if (cmpVal(getYear(d1),getYear(d2)) == 0 && cmpVal(getMonth(d1),getMonth(d2)) == 0 && cmpVal(getDay(d1),getDay(d2))==1) return 1;
		else if (cmpVal(getYear(d1),getYear(d2)) == 0 && cmpVal(getMonth(d1),getMonth(d2)) == 0 && cmpVal(getDay(d1),getDay(d2))==-1) return -1;	
	return 0;
}

void printDate (Date d) {
	printf("Year : %d\n",d->year);
	printf("Month : %d\n",d->month);
	printf("Day: %d\n",d->day);
	printf("\n");
}
/*
int main () {
	Date d 	= nDate(6,3,2018);
	Date d1 = nDate(7,3,2018);
	Date d2	= nDate(7,3,2017);
	Date d3	= nDate(17,4,2018);
	Date d4	= nDate(18,3,2008);
	GList* lista = NULL;
	lista = g_list_insert_sorted(lista,d,(GCompareFunc) cmpDate);
	lista = g_list_insert_sorted(lista,d1,(GCompareFunc) cmpDate);
	lista= g_list_insert_sorted(lista,d2,(GCompareFunc) cmpDate);
	lista = g_list_insert_sorted(lista,d3,(GCompareFunc) cmpDate);
	lista = g_list_insert_sorted(lista,d4,(GCompareFunc) cmpDate);
	g_list_foreach(lista , (GFunc) printDate , (Date)lista->data);
	return 0;
}*/