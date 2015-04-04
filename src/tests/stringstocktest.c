#include <stdio.h>
#include "../ngramstruct.h"

int main(int argc, char ** argv) {

    
    string_stock * stosik = string_stock_init();
   
   /*put argv arguments on stock */
    int i;
    for(i = 1; i < argc; i++) {
	   string_stock_push(&stosik, argv[i]);
    }

    char * temp;
    /* get arguments from stock */
    while( (temp = string_stock_pop(&stosik) ) != NULL )
	   printf("%s\n", temp);
    
    string_stock_free(stosik);

    return 0;
}
