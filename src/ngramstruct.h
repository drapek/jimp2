#ifndef NGRAMSTRUCT_H
#define NGRAMSTRUCT_H

#include <stdlib.h>

/* it's store ponters to char arrays, it made for quick managing collections of strings */
typedef struct str {
    char * field;
    struct str * prev;
} string_stock;


/* this functions describes string_stack which store dynamic arrays of string. */
void string_stock_push(string_stock * where, char * what );

/* take last string from stock */
char * string_stock_pop(string_stock * from);

/* initial new string stock and return pointer to this stock*/
string_stock * string_stock_init();

/* free the memory which string_stock take */
int string_stock_free(string_stock * what);

/* struct describinig instance of words from one input file */
struct word_collect {
    char ** words;
    char * name_file; //file name where the words comes from
    int * num_words; //number of readed words
};   

/*structure which store collection of structurs, which store readed words */
typedef struct {
    struct word_collect * one_file; /* array of words from one file  */
    int ngram_size; /*allocated size for n ngrams */
    int ngram_elem; /* actual number of stored ngrams */
} ngram;

/*create and initiaze new ngram and return a pointer to them*/
ngram * ngram_init();

/*search in ngram word collection which are the same, start searching in ngram by word number <search_start_position>, and compare <num_collect> elements of vector <word_collect>, and <instace> descirbe which isntance it serach (nedded for seraching the same ngrams).  Function return pointer to  whole ngram converted to dynamic char array. If null returned it means thath ngram was not found.*/
char * ngram_search(ngram * this, char ** word_collect, int num_collect, int search_start_position,  int instance);

/*add at end of stucture */
int ngram_add(ngram * this, char ** words_collect, int num_words, char * file_name);

/*finds sufix in all ngram structure */
char ** ngram_find_sufixs(ngram structure, char ** prefix, int num_prefix);

/* */
int ngram_free(ngram * this);

#endif
