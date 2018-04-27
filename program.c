#include "./interface.h"

int main () {
	TAD_community ht=NULL;
	ht=init(ht);
	ht=load(ht,"../dump exemplo/ubuntu/");
	long l = better_answer(ht,30334);
	printf("%li\n",l);
	return 0;
}