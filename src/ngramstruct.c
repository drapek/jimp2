#include "ngramstruct.h"
#include "errors.h"
#include <string.h>
#include <stdlib.h>

#define NGRAM_STRUCT_LIMIT 40

/* function to list all data from struct file_path */
void file_paths_list( file_paths this) {
    int i;
    printf(" [ ");
    for( i = 0; i < this.num_path; i++ )
	  printf("%s\"%s\"", (i == 0) ? "" : ", ", this.file_path[i]);
    printf(" ]");

}

/* this functions describes string_stack which store dynamic arrays of string. */
void string_stock_push(string_stock ** where, char * what ) {
    if( what == NULL ) 
	   program_error(ERR_CRITIC, ERR_NGRAM_STRUCT, "Nastąpiła próba dodania pustego wskaźnika na string_stoss (funkcja string_stock_push)");
    string_stock * new = malloc( sizeof * new );
    new->field = what;
    new->prev = *where;

    *where = new;
}

/* take last string from stock */
char * string_stock_pop(string_stock ** from) {
    if(*from != NULL) {
	   char * temp_addr = (**from).field;
	   void * del = *from;
	   *from = (**from).prev;
	   free(del);
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
    /*[IMPORTANT] not working, fix it in later time! */
	   return 0;
    string_stock * temp = what;
    string_stock * temp2 = NULL;
    while(temp->prev != NULL) {
	   free(temp->field);
	   if(temp2 != NULL) 
		  free(temp2);
	   temp2 = temp;
	   temp = temp->prev;
    }
    /*clear the last element*/
    free(temp->field);
    free(temp->prev);
    free(temp);
    free(temp2);

    return 0;
}

/*init structure word_collect by size of 200 elements and return pointer to them */
word_collect * word_collect_init(char * file_name) {
    word_collect * new = malloc( sizeof(* new));
    new->words = malloc( sizeof( new->words ) * 200);
    if( new->words == NULL )
	   program_error(ERR_CRITIC, ERR_NGRAM_STRUCT, "brak pamięci operacyjnej, by stworzyć strukturę przechowującą slowa (word_collect_init)");
	   
    new->name_file = file_name;
    new->size_words = 200;
    new->num_words = 0;

    return new;
   
}

/* return the size of char dynamic array, this function is nedded in word_collect_add */
static int dyn_arr_size(char * arr) {
    int i = 0;
    while( *(arr++) != '\0') 
	   i++;
    return i;
}
/*add word to a structure, and when it neede it can resize themself by 200 elements */
void word_collect_add(word_collect * where, char * what) {
    if( where->num_words >= where->size_words ) {
	   void * new =  realloc( where->words, sizeof( where->words ) * (where->size_words + 200));
	   if( new == NULL )
		  program_error(ERR_CRITIC, ERR_NGRAM_STRUCT, "brak pamięci operacyjnej, by powiększyć strukturę przechowującą słowa (funk word_collect_add)");
	   else {
		  where->words = new;
		  where->size_words += 200;
	   }
   }
	   
	   size_t size = dyn_arr_size( what ) + 1;
	   where->words[where->num_words] = malloc( ( size = sizeof( char ) * size ) );
	   if( where->words[where->num_words] == NULL)
		  program_error(ERR_CRITIC, ERR_FLAG_INTERPRET, "Brak pamięci dla zallokowania pamięci dla wczytanego słowa z pliku (funk word_collect_add)");
	   memcpy(where->words[where->num_words], what, size);

	   where->num_words++;
}

/*list to stdout the content of given word_collect struct */
void word_collect_list(word_collect * what, int how_many) {
    int i;
    int isLimited = 1;
    if (how_many == 0) isLimited = 0; 
    printf(" [ ");
    for(i = 0; i < what->num_words; i++ ) {
	   printf("%s%s", (i == 0) ? "":", ", what->words[i]);
	   if( isLimited )
		  if (i == how_many) break;
	   
    }
    printf(" ] ");
}

/* free the memory after it is not needed, mostly at the end of the program */
void word_collect_free() {

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

/* [IMPORANT] rewrite this function, so it can take word_collect structure and assing it to ngram handler*/
/*add at end of stucture */
int ngram_add(ngram * this, word_collect * what) {
    /*check if there is space to add*/
    if( (this->ngram_size) <= (this->ngram_elem) ) {
	   /*limit readed ngrams because to few can cause realloc errors */
	   if( this->ngram_size >= NGRAM_STRUCT_LIMIT ) {
		  program_error(ERR_CRITIC, ERR_NGRAM_STRUCT, "Zbyt duża liczba wczytanych plików, maksymalnie jest to 40."); 
		  }

	   /*resize double*/
	   word_collect * new =  realloc( this->one_file, sizeof( *new ) * this->ngram_size * 2);
	   if( new == NULL )
		  program_error(ERR_CRITIC, ERR_NGRAM_STRUCT, "brak pamięci operacyjnej, by powiększyć strukturę przechowującą ngramy (ngram_add function error)");
	   else {
		  this->one_file = new;
		  this->ngram_size *= 2;
	   }
    }

    this->one_file[this->ngram_elem].num_words = what->num_words;
    this->one_file[this->ngram_elem].name_file = what->name_file;
    this->one_file[this->ngram_elem].words = what->words;
    this->one_file[this->ngram_elem].size_words = what->size_words;

    this->ngram_elem++;
    return 0;
}

/* [ABONDED] search in ngram word collection which are the same, start searching in ngram by word number <search_start_position>, and compare <num_collect> elements of vector <word_collect>, and <instace> descirbe which isntance it serach (nedded for seraching the same ngrams).  Function return pointer to  whole ngram converted to dynamic char array. If null returned it means thath ngram was not found.
char * ngram_search(ngram * this, char ** word_collect, int num_collect, int search_start_position,  int instance) {
    return NULL;
} */

/*finds sufix in all ngram structure */
char ** ngram_find_sufixs(ngram structure, char ** prefix, int num_prefix) {
	return NULL;
}

/*list content of every ngram stored in memory */
void ngram_list( ngram * this, int limit) {
    int i;

    int isLimited = 1;
    if ( limit == 0) isLimited = 0;

    if( this->ngram_elem == 0 )
	   printf("stos ngram jest pusty\n");
    else {
	   for( i = 0; i < this->ngram_elem; i++) {
		  printf("\t element nr %i:\t nazwa pliku: %s, ilość słów: %i, wczytane słowa: ", i, this->one_file[i].name_file, this->one_file[i].num_words);
		  if( this->one_file[i].num_words < 1 ) 
			 printf(" [brak słów] ");
		  else {
			 int num_words = this->one_file[i].num_words;
			 if( isLimited )
				if( num_words > limit ) 
				    num_words = limit;

			 /*print words*/
			 int j;
			 printf("[ ");
			 for( j = 0; j < num_words; j++ ) {
				printf("%s\"%s\"", (j == 0) ? "" : ", ", this->one_file[i].words[j]);
			 }
			 if( num_words < this->one_file[i].num_words) 
				printf(", ... ");
			 printf("]");
		  }
		  printf("\n");
	   }
    }
}

/*free all memory which sturct ngram takes*/
int ngram_free(ngram * this) {
    return 0;
}

/*delete comma from last position of file paths (only if it exit here of coure) */
void delete_comma_from_path(char * text) {
    int i = 0;
    while( *text++ != '\0' ) i++;
    text -= 2;
    if( *text == ',')
	   *text = '\0';
}

/* init the array of char ** adresses */
address_arr * address_arr_init() {
    address_arr * new = malloc (sizeof * new);
    if( new == NULL )
	   program_error(ERR_CRITIC, ERR_NGRAM_STRUCT, "Brak pamięci by utworzyć tablicę dyn dla sufixów");

    new->arr = malloc( sizeof *(new->arr) * 10);
    if( new->arr == NULL)
	   program_error(ERR_CRITIC, ERR_NGRAM_STRUCT, "Brak pamięci by utworzyć tablicę wskaźników dla adresów sufixów");

    new->num_elem = 0;
    new->size_of_arr = 10;

    return new;

}

/*add address of what to where structure */
void address_arr_add(address_arr * where, char * what) {
    if( where->num_elem >= where->size_of_arr ) {
	   char ** new = realloc(where->arr, sizeof( *new ) * where->size_of_arr + sizeof( *new) * 10);
	   if( new == NULL ) {
		  program_error(ERR_CRITIC, ERR_NGRAM_STRUCT, "Brak pamięci by powiększyć tablicę wskaźników dla sufixów!");
	   } 
	   else {
		  where->arr = new;
		  where->size_of_arr += 10;
	   }
    }

    where->arr[where->num_elem] = what;
    where->num_elem++;
}

/*free memory of pointers, but not free memory where words are stored! */
void address_arr_free(address_arr * what) {
    free( what->arr );
    free( what );
}

/* list all elements from this sturcture */
void address_arr_list(address_arr * what, int limit) {
    int isLimit = 1;
    /*if we give 0 at the second argument, that means we don't want limit printing */
    if( limit == 0)
	   isLimit = 0;

    if( what == NULL ) {
	   program_error(ERR_NORMAL, ERR_NGRAM_STRUCT, "Podana struktura jest pusta!");
	   return;
    } else {
	   if( what->arr == NULL ) {
		  program_error(ERR_NORMAL, ERR_NGRAM_STRUCT, "W strukturze addres_arr tablica argumentów jest pusta!");
	   	  return;
	   } else {
		  printf("Struktura address_arr, jej rozmiar to: %i, a ilość wczytanych elementów to: %i, elementy wczytane są następujące: \n [ ", what->size_of_arr, what->num_elem);
		  int i;
	       for( i = 0; i < what->num_elem; i++) {
	   	  if( isLimit )
			 if( limit == 0 ) break;
	   	  printf("\"%s\" addr: %p\t ", what->arr[i], &(what->arr[i])); 
	   	  limit--;
		  }
	       printf("] \n");
	   }
    }
}

/*init struct for 50 elements*/
stats * stats_init(int ngram_type) {
    stats * new = malloc (sizeof * new);
    if( new == NULL )
	   program_error(ERR_CRITIC, ERR_NGRAM_STRUCT, "Brak pamięci by utworzyć tablicę dla statystyk");

    new->arr_of_ngrams = malloc( sizeof *(new->arr_of_ngrams) * 50);
    if( new->arr_of_ngrams == NULL)
	   program_error(ERR_CRITIC, ERR_NGRAM_STRUCT, "Brak pamięci by utworzyć tablicę wskaźników dla adresów sufixów");

    new->num_of_elem = 0;
    new->size_of_arr = 50;
    new->ngram_type = ngram_type;

    return new;
}

/*add ngram to a structure, byt when it alredy exit it increment porper value*/
void stats_add(stats * where, char *** actual_ngram, int ngram_type) {
    if( where->num_of_elem >= where->size_of_arr ) {
	   one_ngram * new = realloc(where->arr_of_ngrams, sizeof( *new ) * where->size_of_arr + sizeof( *new) * 50);
	   if( new == NULL ) {
		  program_error(ERR_CRITIC, ERR_NGRAM_STRUCT, "Brak pamięci by powiększyć tablicę statystyk");
	   } 
	   else {
		  where->arr_of_ngrams = new;
		  where->size_of_arr += 50;
	   }
    }

    if( where->ngram_type != ngram_type ) {
	   program_error(ERR_NORMAL, ERR_STATS, "Podany ngram nie zgadza się z tymi odłożonymi w struturze stats! Dlatego przerwałem dodawanie!");
	   return;
    }

    /*serch this ngram in stats collection */
    int i, j, isFound = 0;
    for( i = 0; i < where->num_of_elem; i++) {
	  int isEqual = 1;
	  for( j = 0; j < where->ngram_type; j++ ) {
		  if( strcmp(where->arr_of_ngrams[i].ptr_to_words[j], actual_ngram[0][j]) != 0 ) {
			 isEqual = 0;
			 break;
		  }
	  }

	  if( isEqual ) {
		  isFound = 1;
		  where->arr_of_ngrams[i].num_of_occur++;
		  break;
	  }
    }

    if(!isFound) {
	   where->arr_of_ngrams[where->num_of_elem].ptr_to_words = *actual_ngram;
	   where->arr_of_ngrams[where->num_of_elem].num_of_occur = 1;
	   where->num_of_elem++;
    }
}

void stats_free(stats * what) {
    free( what->arr_of_ngrams );
    free( what );
}

void stats_list(stats * what) {
    printf("Strutra ma wczytanych %i ngramów, gdzie n= %i. A pamięć jest zaalokowana na %i ngramów. \n", what->num_of_elem, what->ngram_type, what->size_of_arr);
    int i,j;
    for( i = 0; i < what->num_of_elem; i++) {
	   printf("\t Ngram %i, wystąpił %i razy = \"", i, what->arr_of_ngrams[i].num_of_occur);
	   for(j = 0; j < what->ngram_type; j++)
		  printf("%s%s", (j == 0) ? "" : " ",  what->arr_of_ngrams[i].ptr_to_words[j]);
	   printf("\"\n");
    }
    printf("\n");
}
