#ifndef GENERATOR_H
#define GENERATOR_H

#include <stdio.h>
#include "ngramstruct.h"
#include "errors.h"

/*generete ngrams to file using Marov chains saved in struct ngramstack*/
int generate(ngram * ngramstack, char * start_word, int max_word, char * file_path);
#endif
