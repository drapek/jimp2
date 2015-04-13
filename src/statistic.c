/* This module generete statistic to a file. The statistic will be contain 
 * teoretical problaity (product of number of word apperances divide by amount of all 
 words for each word in input stirng) and real probality (hom many times appeared whole 
 string in text) for given string */

#include "statistic.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "errors.h"
#include "ngramstruct.h"
#include <limits.h>

int statistics(ngram * ngramstack, char * phrase, char * file_path) {
    printf("Opcja ta zostanie udostępniona w kolejnej wersji programu! Aby być na bierząco śledź nas na: https://github.com/drapek/jimp2 i\n");
}

/* it make statistics based only on genered text, not the whole database*/
void gener_stats(stats * readed_anagrams, stats * readed_ngrams, char *file_path, int nmb_of_top_ngrams) {
    char stat_path[1024] = "";
    strcpy( stat_path, file_path );
    strcat( stat_path, "_stats");
    FILE * output = fopen( stat_path , "w");
    if ( output == NULL ) {
	   program_error(ERR_CRITIC, ERR_GENERAT, "Nie mogę utworzyć pliku w tym miejscu, może nie mam praw do tego katalogu?");   
    }   
    
/* [IMPORTANT] delete later */
    fprintf(output, "Przeczytane anagramy: \n");
    stats_list(readed_anagrams );
    printf("Przeczytane ngramy: \n");
    stats_list(readed_ngrams );
    
    fprintf(output,"TOP %i ngramów wyprodukowanych przez generator: \n", nmb_of_top_ngrams);
    printf("TOP %i ngramów wyprodukowanych przez generator: \n", nmb_of_top_ngrams);
    list_top_ngrams(readed_ngrams, nmb_of_top_ngrams, output);
	
    fprintf(output, "TOP %i słów wyprodukowanych przez generator: \n", nmb_of_top_ngrams);
    printf("TOP %i słów wyprodukowanych przez generator: \n", nmb_of_top_ngrams);
    list_top_ngrams(readed_anagrams, nmb_of_top_ngrams, output);
    
    printf("\n\n");
    fprintf(output, "\n\n");

    PMI(readed_ngrams, readed_anagrams, output);

    fclose( output );
}


/* to count PMI for some ngram we need counted ngrams, and counted anagrams (words) */
void PMI(stats * db_ngrams,  stats * db_anagrams,  FILE * where_print) {
    fprintf(where_print, "Wskaźniki PMI dla produkowanego tekstu wyglądają nastepująco: \n");
    printf("Wskaźniki PMI dla produkowanego tekstu wyglądają nastepująco: \n");
    
    /*check if there is no empty pointers */
    if( db_ngrams == NULL || db_ngrams->arr_of_ngrams == NULL || where_print == NULL || db_anagrams == NULL || db_anagrams->arr_of_ngrams == NULL) {
	   program_error(ERR_NORMAL, ERR_STATS, "Nie mogę obliczyć PMI ngramów, bo struktra którą dostałem jest pusta! Sprawdź przekazywane parametry do funkcji PMI (moduł statistic)!");
	   return;
    }

    if( db_ngrams->num_of_elem == 0) {
	   fprintf(where_print, "BRAK NGRAMÓW \n");
	   printf("BRAK NGRAMÓW \n"); 
	   return;
    }

    int i;
    int whole_ngram_nmb = 0;
    for( i = 0; i < db_ngrams->num_of_elem; i++) 
	   whole_ngram_nmb += db_ngrams->arr_of_ngrams[i].num_of_occur;

    int whole_words_nmb = 0;
    for( i = 0; i < db_anagrams->num_of_elem; i++) 
	   whole_words_nmb += db_anagrams->arr_of_ngrams[i].num_of_occur;

    for( i = 0; i < db_ngrams->num_of_elem; i++) {
	   double ngram_prob = (double) (db_ngrams->arr_of_ngrams[i].num_of_occur) / whole_ngram_nmb;
	   double prod_of_words_prob = 1;
	   int j;
	   for(j = 0; j < db_ngrams->ngram_type; j++) {
		  int k;
		  for(k = 0; k < db_anagrams->num_of_elem; k++) {
			 if( strcmp(db_ngrams->arr_of_ngrams[i].ptr_to_words[j], db_anagrams->arr_of_ngrams[k].ptr_to_words[0]) == 0 ) {
			 prod_of_words_prob *= ( (double)(db_anagrams->arr_of_ngrams[k].num_of_occur) / whole_words_nmb);
			 break;
			 }
		  }
	   }
	   
	   /*printf result to stdout and file*/
	   fprintf(where_print, "\tPMI = %g dla ngramu =\"", (double) ngram_prob / prod_of_words_prob);
	   printf("\tPMI = %g dla ngramu =\"", (double) ngram_prob / prod_of_words_prob);
	   for( j = 0; j < db_ngrams->ngram_type; j++) { 
		  fprintf(where_print, "%s%s", (j == 0) ? "" : " ",  db_ngrams->arr_of_ngrams[i].ptr_to_words[j]);
		  printf("%s%s", (j == 0) ? "" : " ",  db_ngrams->arr_of_ngrams[i].ptr_to_words[j]); 
	   }
	   fprintf(where_print, "\"\n");
	   printf("\"\n");

    }
}




/*list n most frequent ngram*/
void list_top_ngrams(stats * readed_ngrams, int nmb_of_top_ngrams, FILE * where_print) {
    if( nmb_of_top_ngrams > readed_ngrams->num_of_elem ) 
	   nmb_of_top_ngrams = readed_ngrams->num_of_elem;
    
    /*check if there is no empty pointers */
    if( readed_ngrams == NULL || readed_ngrams->arr_of_ngrams == NULL || where_print == NULL) {
	   program_error(ERR_NORMAL, ERR_STATS, "Nie mogę znaleźć ngramów z największą liczbą wystąpień, bo struktrę którą dostałem jest pusta! Sprawdź przekazywane parametry do list_top_ngrams!");
	   return;
    }

    if( readed_ngrams->num_of_elem == 0) {
	   fprintf(where_print, "BRAK NGRAMÓW \n");
	   printf("BRAK NGRAMÓW \n"); 
	   return;
    }

    int i, j, last_max = INT_MAX; /*beacasue it is unpossible to get higher value*/
    for( i = 0; i < nmb_of_top_ngrams;) {
	   int local_max = -1;
	   /*find max value*/
	   for(j = 0; j < readed_ngrams->num_of_elem; j++) {
		  if( ( readed_ngrams->arr_of_ngrams[j].num_of_occur > local_max ) && ( readed_ngrams->arr_of_ngrams[j].num_of_occur < last_max ) ) 
			 local_max = readed_ngrams->arr_of_ngrams[j].num_of_occur; 
	   }

	   if(local_max == -1 ) {
		  program_error(ERR_NORMAL, ERR_STATS, "Szukałem maksymalnej liczby ngramów, lecz okazało się iż nie mogę więcej ich znaleźć! (funk list_top_ngrams)");
		  return;
	   }

	   /*print all elements with nmb of local_max*/
	   for( j = 0; j < readed_ngrams->num_of_elem; j++ ) {
		  if( readed_ngrams->arr_of_ngrams[j].num_of_occur == local_max ) {
			 int k;
			 fprintf(where_print, "\t Wystąpił %i razy, i wygląda następująco: \"", readed_ngrams->arr_of_ngrams[j].num_of_occur);
			 printf("\t Wystąpił %i razy, i wygląda następująco: \"", readed_ngrams->arr_of_ngrams[j].num_of_occur);
			 for(k = 0; k < readed_ngrams->ngram_type; k++) {
				fprintf(where_print, "%s%s", (k == 0) ? "" : " ",  readed_ngrams->arr_of_ngrams[j].ptr_to_words[k]);
				printf("%s%s", (k == 0) ? "" : " ",  readed_ngrams->arr_of_ngrams[j].ptr_to_words[k]);
			 }
			 fprintf(where_print, "\"\n");
			 printf("\"\n");
			 
			 i++;
			 /* becase if there are few ngrams with the same number of occurs, and this number is for example maximal, then function can print more ngrams than it would */
			 if ( !(i <  nmb_of_top_ngrams) )
				break;
		  }
	   }

	   last_max = local_max;
    }
    
}
