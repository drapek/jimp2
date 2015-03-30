#include "ngramstruct.h"

/*[IMPORTANT] WRITE THESE FUNCTIONS! */

/* this functions describes string_stack which store dynamic arrays of string. */
void string_stock_push(string_stock * where, char * what ) {
    string_stock * new = malloc( sizeof * new );
    new->field = what;
    new->prev = where;

    where = new;


}

/* take last string from stock */
char * string_stock_pop(string_stock * from) {
    if(from != NULL) {
	   char * temp_addr = from->field;
	   string_stock * temp = from;
	   free(temp);
	   from = from->prev;
	   return temp_addr;
    } else 
	   return NULL;
}

/* initial new string stock and return pointer to this stock*/
string_stock * string_stock_init() {
    string_stock * new = malloc(sizeof * new);
    new->field = NULL;
    new->prev = NULL;
    return new;
}


/* free the memory which string_stock take */
int string_stock_free(string_stock * what) {
    string_stock * temp = what;
    string_stock * temp2 = NULL;
    while(temp->prev != NULL) {
	   free(temp->field);
	   if(temp2 != NULL) 
		  free(temp2);
	   temp2 = temp;
	   temp = temp->prev;
    }
    /*czyści ostatni element*/
    free(temp->field);
    free(temp->prev);
    free(temp);
    free(temp2);

    return 0;
}


/*create and initiaze new ngram and return a pointer to them*/
ngram * ngram_init() {
    return NULL;
}

/* [ABONDED] search in ngram word collection which are the same, start searching in ngram by word number <search_start_position>, and compare <num_collect> elements of vector <word_collect>, and <instace> descirbe which isntance it serach (nedded for seraching the same ngrams).  Function return pointer to  whole ngram converted to dynamic char array. If null returned it means thath ngram was not found.
char * ngram_search(ngram * this, char ** word_collect, int num_collect, int search_start_position,  int instance) {
    return NULL;
} */

/*finds sufix in all ngram structure */
char ** ngram_find_sufixs(ngram structure, char ** prefix, int num_prefix) {
	return NULL;
}

/*add at end of stucture */
int ngram_add(ngram * this, char ** words_collect, int num_words, char * file_name) {
    return 0;
}

char ** ngram_find_sufixs(ngram structure, char ** prefix, int num_prefix);

/*free all memory which sturct ngram takes*/
int ngram_free(ngram * this) {
    return 0;
}
