/* This module generete statistic to a file. The statistic will be contain 
 * teoretical problaity (product of number of word apperances divide by amount of all 
 words for each word in input stirng) and real probality (hom many times appeared whole 
 string in text) for given string */

#include "statistic.h"
#include <string.h>
#include "errors.h"

int statistics(ngram * ngramstack, char * phrase, char * file_path) {
    return 0;
}

/* it make statistics based only on genered text, not the whole database*/
void gener_stats(stats * readed_ngrams);


/* to count PMI for some ngram we need counted ngrams, and counted anagrams (words) */
static PMI(stats * db_ngrams,  stats * db_anagrams, char ** checked_ngram, int ngram_type);
#endif
