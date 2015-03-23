/* This module serve ngram databases */
#include "database.h"

/*save dynamic array of chars to string in binary mode (nedded because normaly it's 
save memory adress of pointer instead string */
static int save_arr_char_to_file(char * string, FILE * output) {
    return 0;
}

/* save active database of ngrams to a file */
int save_ngram(ngram * ngramstack, char * file_path) {
    return 0;
}

/* read array chars to dynamic array (nedded for the same reason as function save_arr_char_to_file */
static char * read_arr_char_from_file(FILE * input) {
    return NULL;
}

/*read form binary database file a ngrams and save it to and of ngramstack */
int read_ngram(ngram * ngramstack, char * file_path) {
    return 0;
}
