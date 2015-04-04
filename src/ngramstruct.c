#include "ngramstruct.h"
#include "errors.h"

#define NGRAM_STRUCT_LIMIT 40

/*[IMPORTANT] string_stock functions aren't working! */

/* this functions describes string_stack which store dynamic arrays of string. */
void string_stock_push(string_stock * where, char * what ) {
    string_stock * new = malloc( sizeof * new );
    new->field = what;
    new->prev = where;

    /*[IMPORTANT] the addres is assigned, but somehow when program go out this function,
    the where have non stop the same address*/
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
    ngram * new = malloc( sizeof(* new));
    new->one_file = malloc( sizeof( new->one_file ) * 10);
    if( new->one_file == NULL )
	   program_error(ERR_CRITIC, ERR_NGRAM_STRUCT, "brak pamięci operacyjnej, by stworzyć strukturę przechowującą ngramy (ngram_init)");

    new->ngram_size = 10;
    new->ngram_elem = 0;

    return new;
}

/*add at end of stucture */
int ngram_add(ngram * this, char ** words_collect, int num_words, char * file_name) {
    /*check if there is space to add*/
    if( (this->ngram_size) <= (this->ngram_elem) ) {
	   /*resize double*/
	   /*limit readed ngrams because to few can cause realloc errors */
	   if( this->ngram_size >= NGRAM_STRUCT_LIMIT ) {
		  program_error(ERR_CRITIC, ERR_NGRAM_STRUCT, "Zbyt duża liczba wczytanych plików, maksymalnie jest to NGRAM_STRUCT_LIMIT"); 
		  return 0;
		  }

	   void * new =  realloc( this->one_file, sizeof( *new ) * this->ngram_size * 2);
	   if( new == NULL )
		  program_error(ERR_CRITIC, ERR_NGRAM_STRUCT, "brak pamięci operacyjnej, by powiększyć strukturę przechowującą ngramy (ngram_add function error)");
	   else {
		  this->one_file = new;
		  this->ngram_size *= 2;
	   }
    }

    this->one_file[this->ngram_elem].num_words = num_words;
    this->one_file[this->ngram_elem].name_file = file_name;
    this->one_file[this->ngram_elem].words = words_collect;
    this->ngram_elem++;
}

/* [ABONDED] search in ngram word collection which are the same, start searching in ngram by word number <search_start_position>, and compare <num_collect> elements of vector <word_collect>, and <instace> descirbe which isntance it serach (nedded for seraching the same ngrams).  Function return pointer to  whole ngram converted to dynamic char array. If null returned it means thath ngram was not found.
char * ngram_search(ngram * this, char ** word_collect, int num_collect, int search_start_position,  int instance) {
    return NULL;
} */

/*finds sufix in all ngram structure */
char ** ngram_find_sufixs(ngram structure, char ** prefix, int num_prefix) {
	return NULL;
}


/*free all memory which sturct ngram takes*/
int ngram_free(ngram * this) {
    return 0;
}
