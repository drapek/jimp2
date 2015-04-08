#include "generator.h"
#include "errors.h"
#include <stdlib.h>

/* this is the furure, which will be added in short time to main*/
int flag_verbose = 1;


/* First open file to wirte text, next generete step by step words using Marokov chains, and save it to file */
int generate(ngram * ngramstack, file_paths * start_word, int ngram_type, int max_word, char * file_path) {
    /* first check if check if file exist, and if so, then write information about this */
    FILE * check = fopen( file_path, "r" );
    if( check != NULL) {
	   program_error(ERR_NORMAL, ERR_GENERAT, "Nadpisałem plik wyjściowy!");
	   fclose( check );
    }

    FILE * output = fopen( file_path , "w");
    if ( output == NULL ) {
	   program_error(ERR_CRITIC, ERR_GENERAT, "Nie mogę utworzyć pliku w tym miejscu, może nie mam praw do tego katalogu?");
    }

    /*if user not give start words radnom some */
    if( start_word->num_path == 0 ) 
	   rand_start(start_word, ngram_type);
    
    /*sets atual ngram to start_ngram */
    int pos_of_ngram_in_str_wrd = start_word->num_path - ngram_type;
    if( pos_of_ngram_in_str_wrd < 0 )
	   program_error(ERR_CRITIC, ERR_GENERAT, "Podany ciąg wejściowy jest zbyt krótki w porównaniu do ngramu, przez co nie mogę wygenerować tekstu! Porada: zmiejsz typ ngramu.");
    char ** actual_ngram = start_word->file_path + pos_of_ngram_in_str_wrd;

    int i;
    /* printf start wrods to a file, and if needed to stdout */
    for( i = 0; i < start_word->num_path; i++) {
	   fprintf( output, "%s ", start_word->file_path[i] );
	   if( flag_verbose )
	   	   printf( "%s ", start_word->file_path[i] );
    }

    srand( time(NULL) );
    
    /* the main loop of the generator*/
    for(i = 0; i < ( max_word - start_word->num_path); i++ ) {
    address_arr * sufixs = make_sufix_arr(ngramstack, actual_ngram, ngram_type);
    
    /* check if make_sufix find some sufix */
    if( sufixs->num_elem == 0 ) {
	   /*if not, end generating */
	   break;
    }

    /* rand one sufix from sufix arr */
    int rand_sufix = (rand() % sufix->num_elem);

    fprintf(output, "%s ", sufix->arr[rand_sufix] );
    if( flag_verbose )
        printf("%s ", sufix->arr[rand_sufix]);

    act_ngram_update(actual_ngram, ngram_type, sufix->arr[rand_sufix]);
    address_arr_free( sufixs );
    }

    fclose( output );
    return 0; 
}

static void rand_start(ngram * ngramstack, file_paths * start_word, int ngram_type) {

}

/* make array of addresses of sufix, addreses are copied from ngram structure */
static adress_arr * make_sufix_arr(ngram * ngramstack, char ** actual_ngram, int ngram_type ) {
    /* it musn't malloc new memory, it is enough to assign addresses from ngram sturcture */
}

/* update actual_ngram variable by deleting first element, moving rest by one position to front and add new sufix at the and */
static void act_ngram_update(char ** actual_ngram, int ngram_type, char * sufix);
