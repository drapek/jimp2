/* This module generete statistic to a file. The statistic will be contain 
 * teoretical problaity (product of number of word apperances divide by amount of all 
 words for each word in input stirng) and real probality (hom many times appeared whole 
 string in text) for given string */
#ifndef STATISTIC_H
#define STATISTIC_H

#include <stdio.h>
#include "ngramstruct.h"
#include "errors.h"

int statistics(ngram * ngramstack, char * fraza);

#endif
