#include <stdlib.h>
#include "list.h"

struct llist {
  int size;
  long * list;
};

LONG_list create_list(int size) {
    if(size <= 0) return NULL;
    LONG_list l = malloc(sizeof(struct llist));
    l->size = size;
    l->list = malloc(sizeof(long) * size);
    return l;
}

long get_list(LONG_list l, int index) {
    return l->list[index]; 
}

void set_list(LONG_list l, int index, long value) {
    l->list[index] = value;
}
void free_list(LONG_list l) {
    if(l) {
        free(l->list);
        free(l);
    }
}

void print_LONG_list (LONG_list l) {
    int i,size=l->size;
    for (i=0;i<size;i++) printf("%li\n",l->list[i]);
}


