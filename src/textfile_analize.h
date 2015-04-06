/* This module analize text file with exmaple text and make and add ngrams to current program database */
#ifndef TEXTFILE_ANALIZE
#define TEXTFILE_ANALIZE

#include <stdio.h>
#include "errors.h"
#include "ngramstruct.h"

/* main function of checking and analizing file*/
int analize(ngram * ngramstack, file_paths * file_path, int n_gram_type);

/* auxiliary funcion to interprete 1 line of input file, return 1 if End Of File is redded, otherwise return 0 */
static int line_anal(string_stock interpreted_line, FILE * input);

/* check given word if it is valid to add to database */
static int word_validator(char * word);

/*delete comma from last position of given text (nedded to file paths) */
static void delete_comma_from_path(char * text);

#endif
