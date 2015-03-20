#include "ngramstruct.h"

/*[IMPORTANT] WRITE THESE FUNCTIONS! */

/* this functions describes string_stack which store dynamic arrays of string. */
void string_stock_push(string_stock where, char * what ) {

}

/* take last string from stock */
char * string_stock_pop(string_stock from) {
    return NULL;
}

/* initial new string stock and return pointer to this stock*/
string_stock * string_stock_init() {
    return NULL;
}

/* free the memory which string_stock take */
int string_stock_free(string_stock what) {
    return 0;
}


/*create and initiaze new ngram and return a pointer to them*/
ngram * ngram_init() {
    return NULL;
}

/*search in ngram word collection which are the same, start searching in ngram by word number <search_start_position>, and compare <num_collect> elements of vector <word_collect>, and <instace> descirbe which isntance it serach (nedded for seraching the same ngrams).  Function return pointer to  whole ngram converted to dynamic char array. If null returned it means thath ngram was not found.*/
char * ngram_search(ngram * this, char ** word_collect, int num_collect, int search_start_position,  int instance) {
    return NULL;
}

/*add at end of stucture */
int ngram_add(ngram * this, char * what) {
    return 0;
}

/*free all memory which sturct ngram takes*/
int ngram_free(ngram * this) {
    return 0;
}
