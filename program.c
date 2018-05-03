#include "./interface.h"

int main () {
	TAD_community ht=NULL;
	ht=init(ht);
	ht=load(ht,"../dump exemplo/ubuntu/"); 
	LONG_list l=contains_word(ht,"kde",10);
	print_LONG_list(l);
	return 0;
}