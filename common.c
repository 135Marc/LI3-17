#include "common.h"

/*

	FALTAM AS FUNÇÕES PARA METER AS TAGS NO FORMATO CORRECTO!

*/

//Retorna a string resultante até um caracter específico.

char* stringTill(char* string, char c) {
	int i;
	char* res = malloc(sizeof(char*));
	for(i=0;string[i]!=c ;i++) {
		res[i]=string[i];
	}
	return res;
}

char* sortDate (char* date) {
	char *res = stringTill(date,'T');
	return res;
}

// Retorna a string resultante entre um caracter especifico.
int elemChar (char* string, char c) {
	int i,r=0;
	for(i=0;string[i]!='\0';i++) {
		if (string[i]==c) r=1;
	}
	return r;
}

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

int main () {
	Post p = nPost(1,2,1,10,3,"Why do i suck at this shit?","2015-10-13T19:17:17.917","fuckyoumodafokaz");
	/*char* res = sortDate(input);
	char* year = stringTill(res,'-');
	char* month = stringBetween(res,'-');
	char* day = stringAfter(res,'-');*/
	Date d = dateFromPost(p);
	printDate(d);
	//char* tag = "<2.2-froyo><sms><notifications><handcent-sms>";
	return 0;
}