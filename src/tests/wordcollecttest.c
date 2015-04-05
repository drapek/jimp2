#include <stdio.h>
#include <stdlib.h>
#include "../ngramstruct.h"

void main( int argc, char **argv ) {
    if( argc < 2 ) {
    printf("Jako argumenty podaj słowa, które zostaną dodane do word_collect\n");
    exit(1);
    }
    
    word_collect * handler = word_collect_init( "argv" );

    int i;
    for(i = 0; i < argc; i++) {
	   word_collect_add(handler, argv[i]);
    }
    
    word_collect_list(handler, 0);
    printf("\n");

    /* try to put more than 200 elements */
    word_collect * challange = word_collect_init( "chalange" );

    for(i = 0; i < 32000; i++ ) {
	   char tmp[128] = "";
	   sprintf(tmp, "%i", i);
	   word_collect_add(challange, tmp);
    }

    word_collect_list( challange, 0 );
    printf("\n");
}
