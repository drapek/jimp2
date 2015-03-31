#include <stdio.h>
#include "../ngramstruct.h"
#include "../errors.h"

int main(int argc, char ** argv) {

    if(argc < 2 ) {
	   printf("Podaj jakieś słowa a zostanie z nich stworzona struktura ngramów\n");
	   exit(1);
    }
          
    ngram * baza_ngramow = ngram_init();
    ngram_add( baza_ngramow, argv, argc, "argumenty wywołania");
    ngram_free( baza_ngramow );
	   
}
