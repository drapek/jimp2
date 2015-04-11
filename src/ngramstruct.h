#ifndef NGRAMSTRUCT_H
#define NGRAMSTRUCT_H

#include <stdlib.h>

/* stors pointer to dynamic array (argv) where the filepaths starts */
typedef struct {
    char ** file_path;
    int num_path; /*the number of paths in this sturcture */
} file_paths;

/* print to stdout the content of given file_path */
void file_paths_list( file_paths this);

/* it's store ponters to char arrays, it made for quick managing collections of strings */
typedef struct str {
    char * field;
    struct str * prev;
} string_stock;


/* this functions describes string_stack which store dynamic arrays of string. */
void string_stock_push(string_stock **where, char * what );

/* take last string from stock */
char * string_stock_pop(string_stock **from);

/* initial new string stock and return pointer to this stock*/
string_stock * string_stock_init();

/* free the memory which string_stock take */
int string_stock_free(string_stock * what);

/* struct describinig instance of words from one input file */
typedef struct {
    char ** words;
    char * name_file; //file name where the words comes from
    int num_words; //number of readed words
    int size_words;
} word_collect;  

/* chec the size of dynamic array, it is not count \0 char */
static int dyn_arr_size(char * arr);

/*init structure word_collect by size of 200 elements and return pointer to them */
word_collect * word_collect_init(char * file_name);

/*add word to a structure, and when it neede it can resize themself by 200 elements */
void word_collect_add(word_collect * where, char * what);

/*list to stdout the content of given word_collect struct */
void word_collect_list(word_collect * what, int how_many);

/* free the memory after it is not needed, mostly at the end of the program */
void word_collect_free();

/*structure which store collection of structurs, which store readed words */
typedef struct {
    word_collect * one_file; /* array of words from one file  */
    int ngram_size; /*allocated size for n ngrams */
    int ngram_elem; /* actual number of stored ngrams */
} ngram;

/*create and initiaze new ngram and return a pointer to them*/
ngram * ngram_init();

/*search in ngram word collection which are the same, start searching in ngram by word number <search_start_position>, and compare <num_collect> elements of vector <word_collect>, and <instace> descirbe which isntance it serach (nedded for seraching the same ngrams).  Function return pointer to  whole ngram converted to dynamic char array. If null returned it means thath ngram was not found.*/
char * ngram_search(ngram * this, char ** word_collect, int num_collect, int search_start_position,  int instance);

/*add at end of stucture */
int ngram_add(ngram * this, word_collect * what);

/*finds sufix in all ngram structure */
char ** ngram_find_sufixs(ngram structure, char ** prefix, int num_prefix);

/*list content of all ngram structure, limit says how many words will be printed, when it is equal to 0, then there is no limit */
void ngram_list( ngram * this, int limit);

/* */
int ngram_free(ngram * this);

/*delete comma from last position of file paths (only if it exit here of coure) */
void delete_comma_from_path(char * text);

/* structure to store addreses from strings array -> need to make_prefix_arr from generate.c */
typedef struct {
    char ** arr;
    int num_elem;
    int size_of_arr;
} address_arr;

/* init the array of char ** adresses */
address_arr * address_arr_init();

/*add address of what to where structure */
void address_arr_add(address_arr * where, char * what);

/*free memory of pointers, but not free memory where words are stored! */
void address_arr_free(address_arr * );

/* list all elements from this sturcture */
void address_arr_list(address_arr * what, int limit);

/*struture to store the numer of occurrences of given ngram*/
typedef struct {
    char ** ptr_to_words; /*size of this is describe by ngram_type from stats struct*/
    int num_of_occur; /*how many times this ngram occurs*/
} one_ngram;

typedef struct {
    one_ngram * arr_of_ngrams;
    int ngram_type; /* the type of stored ngrams */
    int num_of_elem;
    int size_of_arr;
} stats;

/*init sturt for 50 elements*/
stats * stats_init(int ngram_type);

/*add ngram to a structure, byt when it alredy exit it increment porper value*/
void stats_add(stats * where, char *** actual_ngram, int ngram_type);

void stats_free(stats * what);

/*list whole given stats structure */
void stats_list(stats * what);


#endif
