#include <stdlib.h>

/* it's store ponters to char arrays, it made for quick managing collections of strings */
typedef struct str {
    char * field;
    struct str * next;
} string_stock;


/* this functions describes string_stack which store dynamic arrays of string. */
void string_stock_push(string_stock where, char * what );

/* take last string from stock */
char * string_stock_pop(string_stock from);

/* initial new string stock and return pointer to this stock*/
string_stock * string_stock_init();

/* free the memory which string_stock take */
int string_stock_free(string_stock what);

/*structure which store ngrams */
typedef struct {
    char * **one_ngram; /* array of arrays (which are collecion of ngram words) which store array of char (one word) :D */
    int ngram_size; /*allocated size for n ngrams */
    int ngram_elem; /* actual number of stored ngrams */
} ngram;

/*create and initiaze new ngram and return a pointer to them*/
ngram * ngram_init();

/*search in ngram word collection which are the same, start searching in ngram by word number <search_start_position>, and compare <num_collect> elements of vector <word_collect>, and <instace> descirbe which isntance it serach (nedded for seraching the same ngrams).  Function return pointer to  whole ngram converted to dynamic char array. If null returned it means thath ngram was not found.*/
char * ngram_search(ngram * this, char ** word_collect, int num_collect, int search_start_position,  int instance);

/*add at end of stucture */
int ngram_add(ngram * this, char * what);

/* */
int ngram_free(ngram * this);
