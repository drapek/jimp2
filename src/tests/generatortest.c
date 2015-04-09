#include <stdio.h>
#include "../ngramstruct.h"
#include "../generator.h"
#include "../ngramstruct.h"

#include <stdlib.h>
#include <time.h>

#define MAX_WORDS 100

int main (int argc, char **argv) { 
    if( argc < 2 ) {
	   printf("Podaj conajmiej jeden argument, ponieważ chcę losować bigram, dlatego potrzebuje minimum 2 słów!\n");
	   exit(1);
    }
    
    word_collect * arguments = word_collect_init("argv");
    
    /*first make ngram from argv*/
    int i;
    for( i = 0; i < argc; i++ )
	   word_collect_add( arguments, argv[i]);
     
    ngram * global = ngram_init();
    ngram_add( global, arguments );
    
    word_collect * internal = word_collect_init("internal");
    word_collect_add(internal, "Adaś");
    word_collect_add(internal, "nie");
    word_collect_add(internal, "ma");
    word_collect_add(internal, "ochoty");
    word_collect_add(internal, "siedzieć");
    word_collect_add(internal, "i");
    word_collect_add(internal, "ma");
    word_collect_add(internal, "raka");
    ngram_add( global, internal);

    printf("Ngram który jest zapisywany do pliku: \n");
    ngram_list( global, 0);
    printf("\n");
    
    /* test randomizing start ngram */
    file_paths * rand_me = malloc (sizeof( * rand_me));
    rand_me->num_path = 0;
    srand( time(NULL) );
    rand_start(global, rand_me, 2);
    
    /* test of rewriting start_word from file_paths structure to address_arr structure*/
    address_arr * rewrited = address_arr_init();
    set_actual_ngram( rewrited, rand_me, 2 );
    address_arr_list( rewrited, 0 );


    /* test of updating acutal ngram */
    act_ngram_update( rewrited, 2, "ZAMIANA1");
    address_arr_list( rewrited, 0);

    act_ngram_update( rewrited, 2, "ZAMIANA2");
    address_arr_list( rewrited, 0);

    act_ngram_update( rewrited, 2, "ZAMIANA3");
    address_arr_list( rewrited, 0);
    
    address_arr_free( rewrited );

    /* testing functions which search sufixs, when as argument we give: "Ala ma kota i ala ma psa." as a result we should get array with "kota" and "psa." */
    address_arr * actual_ngram = address_arr_init();
    char ala[] = "Ala";
    char ma[] = "ma";
    address_arr_add( actual_ngram, ala);
    address_arr_add( actual_ngram, ma);
    address_arr * sufixs = make_sufix_arr(global, actual_ngram, 2);
    printf("Jak podasz na wejście \"Ala ma kota i ala ma psa.\" to powinna poniższa struktra przyjąć dwa argumenty: \"kota\" i \"psa.\" \n");
    address_arr_list( sufixs, 0); 
    address_arr_free(sufixs);
    address_arr_free(actual_ngram);
    printf("\n");

    /* test for trigrams */
    address_arr * tri_ngram = address_arr_init();
    char Adam[] = "Adam";
    char nie[] = "nie";
    //char ma[] = "ma"; commeted because it was alredy defined in line 58 */
    address_arr_add( tri_ngram, Adam);
    address_arr_add( tri_ngram, nie);
    address_arr_add( tri_ngram, ma);
    printf("Jak podasz na wejście \"Andrzej nie ma zębów, a Asia nie ma pieniędzy, za to Krzyś nie ma zupy.\" to powinna poniższa struktra przyjąć trzy argumenty: \"zębów\", \"pieniędzy\" i \"zupy.\" \n");
    sufixs = make_sufix_arr(global, tri_ngram, 3);
    address_arr_list( sufixs, 0); 
    address_arr_free(sufixs);
    address_arr_free(tri_ngram);
    printf("\n");


    /* test for quadorgrams */
    address_arr * quadrogram = address_arr_init();
    address_arr_add( quadrogram, Adam );
    address_arr_add( quadrogram, nie );
    address_arr_add( quadrogram, ma );
    char ochoty[] = "ochoty";
    address_arr_add( quadrogram, ochoty );
    printf("Jak podasz na wejście tekst zaiwerający sekwencję \"nie ma ochoty\" to powinna poniższa struktra przyjąć takie argumenty jakie słowa następują po tej skewnecji w podawanym tekście \n");
    sufixs = make_sufix_arr(global, quadrogram, 4);
    address_arr_list( sufixs, 0); 
    address_arr_free(sufixs);
    address_arr_free(quadrogram);
    printf("\n");


    printf("\n######################Testowanie całego generatora######################\n\n");

    /*there is no functions to adding and initializig filepaths, because writing its to use it only 2 times has been a wast of time */
    file_paths * start_words  = malloc( sizeof( *start_words));
    start_words->num_path = 0;
    
    generate(global, start_words, 2, MAX_WORDS, "outputs/generator-wynik.txt"); 


}
