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


int main () {
	char* input = "2010-09-13T19:17:17.917";
	char* res = sortDate(input);
	char* year = stringTill(res,'-');
	char* month = stringBetween(res,'-');
	char* day = stringAfter(res,'-');
	printf("%s\n",res);
	printf("Year : %s\n",year);
	printf("Month : %s\n",month);
	printf("Day : %s\n",day);
	char* tag = "&lt;2.2-froyo&gt;&lt;sms&gt;&lt;notifications&gt;&lt;handcent-sms&gt";
	return 0;
}