#include "date.h"

typedef struct dates {
	int day;
	int month;
	int year;
}Dates;


/**	@brief Função que cria uma data
*   @param int dia
*   @param int mes
*   @param int ano
*	@return Date 
*/
Date nDate (int day,int month,int year) {
	Date new = malloc(sizeof(Dates));
	new -> day = day;
	new -> month= month;
	new -> year = year;
	return new;
}


/**	@brief Função que cria uma data
*   @param int dia
*   @param int mes
*   @param int ano
*	@return Date 
*/
void freeDate (Date d) {
	free(d);
}


/**	@brief Função que extrai um dia
*   @param Date
*	@return int dia
*/
int get_Day (Date d) {
	return d -> day;
}


/**	@brief Função que extrai um mes
*   @param Date
*	@return int mes 
*/
int get_Month (Date d) {
	return d -> month;
}


/**	@brief Função que extrai um mes
*   @param Date
*	@return int ano
*/
int get_Year (Date d) {
	return d -> year;
}


/**	@brief Função que faz printf 
*   @param Date 
*/
void printDate (Date d) {
	if (d){
	printf("Year : %d\n",d->year);
	printf("Month : %d\n",d->month);
	printf("Day: %d\n",d->day);
	printf("\n");
}
}
