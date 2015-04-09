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

    srand( time(NULL) );

    /*if user not give start words radnom some */
    if( start_word->num_path == 0 ) 
	   rand_start(ngramstack, start_word, ngram_type);
    
    /*check if given num path is enought length */
    if( ( start_word->num_path - ngram_type ) < 0 )
	   program_error(ERR_CRITIC, ERR_GENERAT, "Podany ciąg wejściowy jest zbyt krótki w porównaniu do ngramu, przez co nie mogę wygenerować tekstu! Porada: zmiejsz typ ngramu.");
    address_arr * actual_ngram = address_arr_init();
    set_actual_ngram( actual_ngram, start_word, ngram_type);

    int i;
    /* printf start wrods to a file, and if needed to stdout */
    for( i = 0; i < start_word->num_path; i++) {
	   fprintf( output, "%s ", start_word->file_path[i] );
	   if( flag_verbose )
	   	   printf( "%s ", start_word->file_path[i] );}

    
    /* the main loop of the generator*/
    for(i = 0; i < ( max_word - start_word->num_path); i++ ) {
    address_arr * sufixs = make_sufix_arr(ngramstack, actual_ngram, ngram_type);
    
    /* check if make_sufix find some sufix */
    if( sufixs->num_elem == 0 ) {
	   /*if not, end generating */
	   printf("\n[INFO] Nie mogłem znaleźć dalszych wzorćów dla ngramów, więc wygenerowałem tylko %i słów, z %i przez ciebie oczekiwanych.", i + start_word->num_path, max_word );
	   break;
    }

    /* rand one sufix from sufix arr */
    int rand_sufix = (rand() % sufixs->num_elem);

    fprintf(output, "%s ", sufixs->arr[rand_sufix] );
    if( flag_verbose )
        printf("%s ", sufixs->arr[rand_sufix]);

    act_ngram_update(actual_ngram, ngram_type, sufixs->arr[rand_sufix]);

    address_arr_free( sufixs );
    }
    if( flag_verbose )
	   printf("\n\n");

    fclose( output );
    return 0; 
}

/* rand start ngram, if user not set by themself */
void rand_start(ngram * ngramstack, file_paths * start_word, int ngram_type) {
    /* rand from which file in ngram stucture */
    int i = rand() % ngramstack->ngram_elem;
    /* rand word from randed file, and it produce only arguments, which not allow to go beyond words array border */
    int j = rand() % (ngramstack->one_file[i].num_words - ngram_type + 1);
    
    start_word->file_path = malloc( sizeof( start_word->file_path ) * ngram_type );
    int k;
    for( k = 0; k < ngram_type; k++ ) 
	   start_word->file_path[k] = ngramstack->one_file[i].words[j + k];

    start_word->num_path = ngram_type;
}

/* make array of addresses of sufix, addreses are copied from ngram structure */
address_arr * make_sufix_arr(ngram * ngramstack, address_arr * actual_ngram, int ngram_type ) {
    /* it musn't malloc new memory, it is enough to assign addresses from ngram sturcture */
    int i,j, k;
    address_arr * sufixs = address_arr_init();

    /* in every files store in ngram structure */
    for( i = 0; i < ngramstack->ngram_elem; i++ ) {
	   /*for every ngram in given file */
	   for( j = 0; j <  (ngramstack->one_file[i].num_words - (ngram_type - 1)); j++ ) {
		  int isEqual = 1;
		  for( k = 0; k < ngram_type - 1; k++ ) {
			 if( strcmp(ngramstack->one_file[i].words[j + k], actual_ngram->arr[k + 1]) != 0 ) {
				isEqual = 0;
				break;
			 }
		  }
		  if( isEqual ) {
			 address_arr_add( sufixs, ngramstack->one_file[i].words[j + k]);
		  }
	   }
    }

    return sufixs;
}

/* update actual_ngram variable by deleting first element, moving rest by one position to front and add new sufix at the and */
void act_ngram_update(address_arr * actual_ngram, int ngram_type, char * sufix) {
    int i;
    for( i = 0; i < ngram_type - 1; i++) 
	   actual_ngram->arr[i] = actual_ngram->arr[i+1];
    /* the last positon of ngram */
    actual_ngram->arr[i] = sufix;

    if( actual_ngram->num_elem != ngram_type )
	   program_error(ERR_CRITIC, ERR_GENERAT, "Przy odnawianiu ngramu odkryto że nie jest on tego typu co powinien... Gdzieś nastąpił poważny błąd (funk act_ngram_update )");
}

/* set actual_ngram to start ngram given by start_word */
void set_actual_ngram(address_arr * actual_ngram, file_paths * start_word, int ngram_type) {
    int i;
    if( actual_ngram->num_elem != 0 )
	   program_error(ERR_CRITIC, ERR_GENERAT, "By ustawić actual ngram, to powinein być on wpierw pusty! (funk set_actual_ngram)");
    for( i = ( start_word->num_path - ngram_type ); i < start_word->num_path; i++)
	   address_arr_add(actual_ngram, start_word->file_path[i]);
}

