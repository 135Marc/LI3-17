#ifndef LONG_LIST__

	#define LONG_LIST__
	#include <stdlib.h>
	#include <stdio.h>
	typedef struct llist * LONG_list;
	LONG_list create_list(int size);
	long get_list(LONG_list l, int index);
	void set_list(LONG_list l, int index, long value);
	void free_list(LONG_list l);
	void print_LONG_list (LONG_list l);

#endif
