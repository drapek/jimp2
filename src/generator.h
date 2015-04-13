#ifndef GENERATOR_H
#define GENERATOR_H

#include <stdio.h>
#include "ngramstruct.h"
#include "errors.h"

/*generete ngrams to file using Marov chains saved in struct ngramstack*/
int generate_text(ngram * ngramstack, file_paths * start_word, int ngram_type, int max_word, char * file_path);

/* rand start ngram, if user not set by themself */
void rand_start(ngram * ngramstack, file_paths * start_word, int ngram_type);

/* make array of addresses of sufix, addreses are copied from ngram structure */
address_arr * make_sufix_arr(ngram * ngramstack, address_arr * actual_ngram, int ngram_type );

/* update actual_ngram variable by deleting first element, moving rest by one position to front and add new sufix at the and */
void act_ngram_update(address_arr * actual_ngram, int ngram_type, char * sufix);

/* set actual_ngram to start ngram given by start_word */
void set_actual_ngram(address_arr * actual_ngram, file_paths * start_word, int ngram_type);

#endif
