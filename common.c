#include "common.h"

char * mystrdup (const char *s) {
    if(s == NULL) return NULL;          
    char *d = malloc (strlen (s) + 1); 
    if (d == NULL) return NULL;       
    strcpy (d,s);                    
    return d;                       
}

int cmpVal (int a,int b) {
	if (a==b) return 0;
	return (a>b) ? -1 : 1;
}

char* split_string (char* s,int i) {
	int size = strlen(s);
	char* buff=malloc(size);
	int j=0;
	for (i=i;s[i]!='\0' && s[i]!=' ';i++) buff[j++]=s[i];
	buff[j]='\0';
	return buff;
}

int inTitle (char* s1, char* s2) {
	int i;
	char* buff;
	for (i=0;s1[i]!='\0';i++) {
		if (s1[i]==' ' || i==0) {
			if (i==0) buff=split_string(s1,i);
			else buff = split_string(s1,i+1);
			if (!strcmp(buff,s2)) return 1;
		}
	}
	return 0;
}

// Compara dois ints de forma inversa

int cmpfunci (const void * a, const void * b) {
   return ( *(int*)b - *(int*)a );
}

int inTag (char* tags, char* tag) {
	int i,j,c1,size;
	size = strlen(tag);
	c1=j=0;
	for(i=0;tags[i]!='\0';i++) {
		if (tags[i]!='<' && tags[i]!='>') {
			if (tags[i]==tag[j++]) c1++;
			else c1=j=0;
		}
		else if (c1==size) return 1;
		else c1=j=0;
}	
	return (c1==size) ? 1 : 0; 
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

int cmpDates (Date d1, Date d2) {
	int year1 = get_Year(d1);
	int year2 = get_Year(d2);
	int month1 = get_Month(d1);
	int month2 = get_Month(d2);
	int day1 = get_Day(d1);
	int day2 = get_Day(d2);
	if (cmpVal(year1,year2)==1) return 1;
		else if (cmpVal(year1,year2)==-1) return -1;
	if (cmpVal(year1,year2) == 0 && cmpVal(month1,month2) == 1) return 1;
		else if (cmpVal(year1,year2) == 0 && cmpVal(month1,month2) == -1) return -1;
	if (cmpVal(year1,year2) == 0 && cmpVal(month1,month2) == 0 && cmpVal(day1,day2)==1) return 1;
		else if (cmpVal(year1,year2) == 0 && cmpVal(month1,month2) == 0 && cmpVal(day1,day2)==-1) return -1;
	return 0;
}

// Verifica se uma data está entre um dado intervalo de datas.
int betweenDate (Date d,Date x,Date y) {
	return (cmpDates(d,x) <= 0 && cmpDates(d,y) >= 0) ? 1 : 0;
}


