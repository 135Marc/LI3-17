 #ifndef PARSER_H_
    
    #define PARSER_H_
	#include <stdlib.h>
	#include <stdio.h>
	#include <libxml/xmlmemory.h>
	#include <libxml/parser.h>
	#include <libxml/tree.h>
	#include "./interface.h"
	TAD_community load_user (TAD_community com, char* dump_path);
	TAD_community load_post (TAD_community com, char* dump_path);
	TAD_community load_tag (TAD_community com, char* dump_path);

#endif