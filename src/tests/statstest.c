#include <stdio.h>
#include "../statistic.h"

int main(int argc, char **argv) {
    int i;

/*anagrams*/
    stats * ana_stat = stats_init( 1 );

    /*add argv arguments to stats structure*/
    for( i = 1; i < argc; i ++) {
	   char ** tmp = ++argv;
	   stats_add(ana_stat, &tmp, 1);
    }
    argv -= (i - 1);

    printf("Tak wygląda struktra stats dla anagramów: \n");
    stats_list( ana_stat );
    printf("\n");

/* bigrams */
    stats * input_stat = stats_init( 2 );

    /*add argv arguments to stats structure*/
    for( i = 1; i < argc - 1; i ++) {
	   argv++;
	   stats_add(input_stat, &argv, 2);
    }
    argv -= (i - 1);

    printf("Tak wygląda struktra stats dla bigramów: \n");
    stats_list( input_stat );
    printf("\n");

/* trigrams */
    stats * tri_stat = stats_init( 3 );

    /*add argv arguments to stats structure*/
    for( i = 1; i < argc - 2; i ++) {
	   argv++;
	   stats_add(tri_stat, &argv, 3);
    }
    argv -= (i - 1);

    printf("Tak wygląda struktra stats dla trigramów: \n");
    stats_list( tri_stat );
    printf("\n");

    /*testing of list_top_ngrams*/
    printf("############ TESTING list_top_ngrams: \n");
    FILE * bigrams_otp = fopen("outputs/statstest_bigram_top", "w");
    printf("Top 5 trigramów: \n");
    list_top_ngrams( tri_stat, 5, bigrams_otp);

    printf("Top 5 bigramów: \n");
    list_top_ngrams( input_stat, 5, bigrams_otp);

    printf("Top 5 anagramów (słów): \n");
    list_top_ngrams( ana_stat, 5, bigrams_otp);

    /*testing of PMI function*/
    printf("############ TESTING PMI: \n");
    printf("PMI trigramów: \n");
    PMI( tri_stat, ana_stat, bigrams_otp );
    printf("\n");


    printf("PMI bigramów: \n");
    PMI( input_stat, ana_stat, bigrams_otp );
    printf("\n");

    printf("PMI anagramów: \n");
    PMI( ana_stat, ana_stat, bigrams_otp );
    printf("\n");

    fclose( bigrams_otp );

/* test gener_stats which are the main funciotns for generating stats */
    printf("############ TESTING main functions of generating stats: gener_stats: \n");
    gener_stats(ana_stat, input_stat, "outputs/statstest_gener_stats", 10);

    stats_free( input_stat );
    stats_free( tri_stat );
    stats_free( ana_stat );

    return 0;
}

