#include <stdio.h>
#include "../ngramstruct.h"

int main(int argc, char ** argv) {

    
    string_stock * stosik = string_stock_init();
    
    int i;
    for(i = 1; i < argc; i++) {
	   string_stock_push(stosik, argv[i]);
    }

    char * temp;
    while( (temp = string_stock_pop(stosik) ) != NULL );
    

    return 0;
}
