/* This module generete statistic to a file. The statistic will be contain 
 * teoretical problaity (product of number of word apperances divide by amount of all 
 words for each word in input stirng) and real probality (hom many times appeared whole 
 string in text) for given string */
#ifndef STATISTIC_H
#define STATISTIC_H

#include "ngramstruct.h"
#include <stdio.h>

/*generete statistic of input words if flag statistic is set, it make statitic for whole database*/
int statistics(ngram * ngramstack, char * phrase, char * file_path);

/* it make statistics based only on genered text, not the whole database*/
void gener_stats(stats * readed_anagrams, stats * readed_ngrams, char * file_path, int nmb_of_top_ngrams);

/* to count PMI for all ngram from db_ngrams */
void PMI(stats * db_ngrams,  stats * db_anagrams, FILE * where_print);

/*list n most frequent ngram*/
void list_top_ngrams(stats * readed_ngrams, int nmb_of_top_ngrams, FILE * where_print);
 
#endif
