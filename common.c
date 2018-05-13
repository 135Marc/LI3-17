#include "common.h"

/**
* @file common.c
* @brief Estrutura dos utilizadores
*/

/** @brief Função que duplica uma string;
*
* @param s     		String a ser duplicada;     
* @return char*    	String duplicada;
*
*/
char * mystrdup (const char *s) {
    if(s == NULL) return NULL;          
    char *d = malloc (strlen (s) + 1); 
    if (d == NULL) return NULL;       
    strcpy (d,s);                    
    return d;                       
}

/** @brief Função que compara dois inteiros de forma inversa;
*
* @param a     		Inteiro;
* @param b 			Inteiro;     
* @return int    	-1 se a > b , 1 se b > a , 0 caso contrário;
*
*/

int cmpVal (int a,int b) {
	if (a==b) return 0;
	return (a>b) ? -1 : 1;
}

/** @brief Função que divide uma string;
*
* @param s     		String a ser dividida;
* @param i 			Indice onde a string vai começar a ser percorrida;     
* @return char*    	String dividida;
*
*/

char* split_string (char* s,int i) {
	int size = strlen(s);
	char* buff=malloc(size);
	int j=0;
	for (i=i;s[i]!='\0' && s[i]!=' ';i++) buff[j++]=s[i];
	buff[j]='\0';
	return buff;
}

/** @brief Função que verifica se uma string está contida noutra;
*
* @param s1     	String maior;
* @param s2 		String menor;     
* @return int    	1 caso s2 esteja contida em s1,0 caso contrário;
*
*/

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


/** @brief Função que verifica se uma string está contida noutra;
*
* @param tags     	String em formato de tag;
* @param tag 		String a comparar;     
* @return int    	1 caso s2 esteja contida em s1,0 caso contrário;
*
*/

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

/** @brief Função que Retorna a string resultante até um caracter específico.
*
* @param string     String a ser percorrida;
* @param c 			Caracter onde a string para;     
* @return char*    	String obtida até ao caracter especificado;
*
*/

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

/** @brief Função que normaliza o formato de uma string (que contém uma data)
*
* @param s1     	String maior;
* @param s2 		String menor;     
* @return int    	1 caso s2 esteja contida em s1,0 caso contrário;
*
*/

char* sortDate (char* date) {
	char *res = stringTill(date,'T');
	return res;
}


/** @brief Função que verifica se um caracter pertence a uma string
*
* @param string     	String maior;
* @param c 				Caracter a encontrar;     
* @return int    		1 caso o caracter esteja contido na string,0 caso contrário;
*
*/

int elemChar (char* string, char c) {
	int i,r=0;
	for(i=0;string[i]!='\0';i++) {
		if (string[i]==c) r=1;
	}
	return r;
}

/** @brief Função que retorna a string resultante entre um caracter especifico.
*
* @param string     	String a ser percorrida;
* @param c 				Caracter delimitador;     
* @return char*    		String contida entre o delimitador;
*
*/
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

/** @brief Função que retorna a string resultante após n ocorrências de um caracter específico.
*
* @param string     	String a ser percorrida;
* @param c 				Caracter delimitador;     
* @return char*    		String contida após o delimitador;
*
*/

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

/** @brief Função que obtém a data de um post (string) e converte-a no formato Date
*
* @param date    		String a converter;     
* @return Date    		Apontador da estrutura Date;
*
*/

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

/** @brief Função que obtém a data de um post (string) e converte-a no formato Date
*
* @param date    		String a converter;     
* @return Date    		Apontador da estrutura Date;
*
*/

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

/** @brief Função que verifica se uma data está entre um dado intervalo de datas.
*
* @param d    			Data a comparar;
* @param x 				Data inicial;
* @param y 				Data final;     
* @return int    		1 se está contida, 0 caso contrário;
*
*/

int betweenDate (Date d,Date x,Date y) {
	return (cmpDates(d,x) <= 0 && cmpDates(d,y) >= 0) ? 1 : 0;
}
