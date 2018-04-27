#include "common.h"

char * mystrdup (const char *s) {
    if(s == NULL) return NULL;          
    char *d = malloc (strlen (s) + 1); 
    if (d == NULL) return NULL;       
    strcpy (d,s);                    
    return d;                       
}
// Compara dois ints de forma inversa

int cmpfunci (const void * a, const void * b) {
   return ( *(int*)b - *(int*)a );
}

//Retorna a string resultante até um caracter específico.

char* stringTill(char* string, char c) {
	int i,size;
	size = strlen(string);
	char* res = malloc(size);
	for(i=0;string[i]!=c ;i++) {
		res[i]=string[i];
	}
	res[i]='\0';
	return res;
}

// Normaliza o formato de uma string (que contém uma data)

char* sortDate (char* date) {
	char *res = stringTill(date,'T');
	return res;
}


// Verifica se um caractere pertence a uma string

int elemChar (char* string, char c) {
	int i,r=0;
	for(i=0;string[i]!='\0';i++) {
		if (string[i]==c) r=1;
	}
	return r;
}

// Retorna a string resultante entre um caracter especifico.

char* stringBetween (char* string, char c) {
	int i,count,size;
	i=count=0;
	size = strlen(string);
	char* res = malloc(size);
	while (string[i]!='\0' && count < 1) {
		if (string[i]==c) count+=1; 
		i+=1;
	}
	res=strcpy(res,string+i);
	res=stringTill(res,c);
	return res;
}

//Retorna a string resultante após n ocorrências de um caracter específico.

char* stringAfter (char* string, char c) {
	int i,count,size;
	i=count=0;
	size = strlen(string);
	char* res = malloc(size);
	while(string[i]!='\0' && elemChar(string+i,'-')!=0){
		i+=1;
	}
		strcpy(res,string+i);
	return res;
}

// Obtém a data de um post (string) e converte-a no formato Date

Date dateFromPost (char* date) {
	char* res = sortDate(date);
	char* year = stringTill(res,'-');
	char* month = stringBetween(res,'-');
	char* day = stringAfter(res,'-');
	free(res);
	int y = atoi(year);
	int m = atoi(month);
	int dd = atoi(day);
	free(year);
	free(month);
	free(day);
	Date d = nDate(dd,m,y);
	return d;
}