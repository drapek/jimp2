#ifndef GENERATOR_H
#define GENERATOR_H

#include <stdio.h>
#include "ngramstruct.h"
#include "errors.h"

/*generete ngrams to file using Marov chains saved in struct ngramstack*/
int generate(ngram * ngramstack, file_paths * start_word, int ngram_type, int max_word, char * file_path);

/* rand ngram from whole ngram structure */
static void rand_start(ngram * ngramstack, file_paths * start_word, int ngram_type);

/* make array of addresses of sufix, addreses are copied from ngram structure */
static adress_arr * make_sufix_arr(ngram * ngramstack, char ** actual_ngram, int ngram_type );

/* update actual_ngram variable by deleting first element, moving rest by one position to front and add new sufix at the and */
static void act_ngram_update(char ** actual_ngram, int ngram_type, char * sufix);

#endif
