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
	int i;
	char* res = malloc(sizeof(char*));
	for(i=0;string[i]!=c ;i++) {
		res[i]=string[i];
	}
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
	int i,count;
	i=count=0;
	char* res = malloc(sizeof(char*));
	while (string[i]!='\0' && count < 1) {
		if (string[i]==c) count+=1; 
		i+=1;
	}
	res=strcpy(res,string+i);
	res=stringTill(res,'-');
	return res;
}

//Retorna a string resultante após n ocorrências de um caracter específico.

char* stringAfter (char* string, char c) {
	int i,count;
	i=count=0;
	char* res = malloc(sizeof(char*));
	while(string[i]!='\0' && elemChar(string+i,'-')!=0){
		i+=1;
	}
		strcpy(res,string+i);
	return res;
}

// Obtém a data de um post (string) e converte-a no formato Date

Date dateFromPost (Post p) {
	char* date = getDate(p);
	char* res = sortDate(date);
	char* year = stringTill(res,'-');
	char* month = stringBetween(res,'-');
	char* day = stringAfter(res,'-');
	int y = atoi(year);
	int m = atoi(month);
	int dd = atoi(day);
	Date d = nDate(dd,m,y);
	return d;
}

// Verifica se uma data está entre um dado intervalo de datas.

int betweenDate (Date d,Date x,Date y) {
	return (cmpDate(d,x) <= 0 || cmpDate(d,y) >= 0) ? 1 : 0;
}

// Retorna o número de questões presentes numa lista ligada de posts
/*
int questionCount (GList* list) {
	int r=0;
	for(list;list!=NULL;list=list->next) {
		if(isQuestion((User)list->data)) r++;
	}
	return r;
}*/
/*
int main () {
	Post p = nPost(1,2,1,10,3,"Titulo teste","2015-10-13T19:17:17.917","$lt;lalala;&gt");
	Date d = dateFromPost(p);
	printDate(d);
	return 0;
}*/