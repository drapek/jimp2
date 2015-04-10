#include <stdio.h>
#include "../ngramstruct.h"
#include "../errors.h"

int main( int argc, char ** argv ) {
    if( argc < 2 ) {
	   printf("Podaj jakieś argumenty, i najlepiej jak będa to bigramy które będą się powtarzać. A następnie przy pomocy gdb (debbugera) sprawdź jak wygląda zapisana struktura!");
    }
    
    stats * input_stat = stats_init( 2 );

    int i;
    /*add argv arguments to stats structure*/
    for( i = 1; i < argc - 1; i ++) {
	   stats_add(input_stat, ++argv, 2);
    }
    argv -= (i - 1);

    printf("Tak wygląda struktra stats dla bigramów: \n");
    stats_list( input_stat );
    printf("\n");
    stats_free( input_stat );

/* trigrams */
    stats * tri_stat = stats_init( 3 );

    /*add argv arguments to stats structure*/
    for( i = 1; i < argc - 2; i ++) {
	   stats_add(tri_stat, ++argv, 3);
    }
    argv -= (i - 1);

    printf("Tak wygląda struktra stats dla trigramów: \n");
    stats_list( tri_stat );
    printf("\n");
    stats_free( tri_stat );

/* quadrograms */
    stats * quadro_stat = stats_init( 4 );

    /*add argv arguments to stats structure*/
    for( i = 1; i < argc - 3; i ++) {
	   stats_add(quadro_stat, ++argv, 4);
    }
    argv -= (i - 1);

    printf("Tak wygląda struktra stats dla quadrogramów: \n");
    stats_list( quadro_stat );
    printf("\n");
    stats_free( quadro_stat );

    return 0;
}
