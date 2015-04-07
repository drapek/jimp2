/* This module serve ngram databases */
#ifndef DATABASE_H
#define DATABASE_H

#include <stdio.h>
#include <stdlib.h>
#include "ngramstruct.h"
#include "errors.h"

/*save dynamic array of chars to string in binary mode (nedded because normaly it's 
save memory adress of pointer instead string) */
static int save_arr_char_to_file(char * string, FILE * output);

/* save active database of ngrams to a file */
int save_ngram(ngram * ngramstack, char * file_path);

/* read array chars to dynamic array (nedded for the same reason as function save_arr_char_to_file */
static char * read_arr_char_from_file( FILE * from );

/*read form binary database file a ngrams and save it to and of ngramstack */
int read_ngrams(ngram * ngramstack, file_paths * db_path);

#endif
