/* This module analize text file with exmaple text and make and add ngrams to current program database */
#include <string.h>
#include "textfile_analize.h"
#include "ngramstruct.h"
#include "errors.h"

/* main function of checking and analizing file*/
int analize(ngram * ngramstack, file_paths * file_path, int n_gram_type)  {  
    int i;
    /*the main loop - switch next filepaths*/
    for( i = 0; i < file_path->num_path; i++ ) {
	   /*check and eventualy delete comma from the last position*/
	   delete_comma_from_path( file_path->file_path[i] );

	   FILE * operations = fopen( file_path->file_path[i],"r");
	   if( operations == NULL ) {
		  char warning[1024] = "Błąd w wczytywaniu pliku, prawdopodobnie źle podana nazwa bądź plik jest aktualnie używany przez inny program. Nazwa wczytywanego pliku: ";
		  program_error(ERR_NORMAL, ERR_TXT_ANALIZ, strcat( warning, file_path->file_path[i] ) );
		  close( operations );
		  continue;
	   }

	   word_collect * words_from_file = word_collect_init(file_path->file_path[i]);

	   char tmpword[1024];
	   int isNotValid = 0;

	   /*[IMPORTANT] The limiter is only for testing purposes, delete it in furhter time! */ 
	   int limiter = 1024;

	   while( fscanf( operations, "%s\n", tmpword ) != EOF) {
		  if( !limiter ) break;

		  isNotValid = word_validator( tmpword );
		  if( isNotValid ) {
			 continue;
		  }

		  word_collect_add( words_from_file, tmpword );
		  limiter--;
	   }

	   word_collect_list( words_from_file, 10 );
	   printf("\n");
	   
	   /*if number of readed words is less than ngram length do not assign this to database*/
	   if (words_from_file->num_words < n_gram_type) {
		  word_collect_free(words_from_file);
	   } else {
		  ngram_add(ngramstack, words_from_file);
	   }
	   
	   close( operations );
    }
    return 0;
}

/* auxiliary funcion to interprete 1 line of input file, return 1 if End Of File is redded, otherwise return 0 */
static int line_anal(string_stock interpreted_line, FILE * input) {
    return 0;
}

/*check words, if satisfies the conditions */
static int word_validator(char * word) {
    if( strcmp(word, "-") == 0)
	   return 1;
    if( strcmp(word, " ") == 0)
	   return 1;
    if( strcmp(word, ".") == 0)
	   return 1;
    if( strcmp(word, "") == 0)
	   return 1;
    /* dash used in poems
    if( strcmp(word, "—") == 0)
	   return 1; */
    return 0;
}

