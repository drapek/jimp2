/* This module serve ngram databases */
#include "database.h"
#include "errors.h"
#include "ngramstruct.h"
#include <string.h>
#include <stdlib.h>
#include <time.h>

/*save dynamic array of chars to string in binary mode (nedded because normaly it's 
save memory adress of pointer instead string */
static int save_arr_char_to_file(char * string, FILE * output) {
   char c;
   int i = 0;

   while( 1 ) {
	   c = napis[i];
	   fwrite(&c, sizeof c, 1, output);
	   if(napis[i] == '\0')
		  break;
	   i++;
   }	   
    return 0;
}

/* save active database of ngrams to a file */
int save_ngram(ngram * ngramstack, char * file_path) {
    char current_filename[1024];
    strcpy( current_filename, file_path );

    int num_of_checks = 0;
    srand( time(NULL));

    /*check if file of this name is alredy exist */
    FILE * check = fopen(file_path, "r");
    while( check != NULL ) {
	   if( num_of_checks == 10 ) {
		  program_error(ERR_NORMAL, ERR_DB_HANDL, "Zmieniono nazwę pliku 10 krotnie, lecz za każdym razem zajęta była nazwa, dlatego zapisanie bazy danych do pliku zostało pominięte.");
		  return 1;
	   }
	   char message[1024] = "Plik o tej nazwie już istnieje! Zmieniono wyjściową nazwę pliku bazy danych na ";
	    /*random letter */
	   char rnd[3];
	   rnd[0] = '_';
	   rnd[1] = rand % 25 + 65;
	   rnd[2] = '\0';

	   strcat(current_filename, rnd);
	   strcat(message, current_filename);
	   program_error(ERR_NORMAL, ERR_DB_HANDL, message); 

	   num_of_checks++;
	   fclose( check );
	   check = fopen(file_path, "r");

    }
    fclose( check );

    /* open the proper file */
    FILE * db_output = fopen( current_filename, "w" );
    if( db_output == NULL ) {
	   program_error(ERR_NORMAL, ERR_DB_HANDL, "Nie mogłem utorzyć pliku, być może nie mam praw do tego folder. Baza danych nie została zapisana.");
	   fclose( db_output );
	   return 1;
    }
    
    int num_of_words = 0;
    int i;
    for (i = 0; i < ngramstack->ngram_elem; i++) {
	   num_of_words += ngramstack->one_file[i].num_words;
    }
    /* the structure of db file is as follows: first is int number which says how many word is in inside, and after him are not spereted words */
    fwrite(&num_of_words, sizeof (num_of_words), 1, db_output);
    
    /*[IMPORTANT] here should be a loop for each word_collect structure from ngram, and iside this loop should be a loop to get each word from it, and save it to db*/
    
    fclose( db_output );
    return 0;
}

/* read array chars to dynamic array (nedded for the same reason as function save_arr_char_to_file */
static char * read_arr_char_from_file( FILE * from ) { 
   char * c = malloc(10 * sizeof *c);
   int akt_size = 10;
   char sign;

   int i = 0;

   while( 1 ) {
	   /*resize array if needed*/
	   if( i + 1 == akt_rozm ) {
		  char * tmp = realloc(c, (akt_rozm + 10) * sizeof tmp);
		  akt_size += 10;
		  c = tmp;
	   }
	   
	   /*read char by char and add it to array*/
	   fread(&sign, sizeof lit, 1, plik_we);
	   c[i] = sign;

	   if(c[i] == '\0')
		  break;
	   i++;
	   
   }	   
   
   return c;
}

/*read form binary database file a ngrams and save it to and of ngramstack, return number of readed ngrams */
int read_ngrams(ngram * ngramstack, file_path * db_path) {
    int i;
    int numb_readed_ngrams = 0;
    /*the main loop - switch next filepaths*/
    for( i = 0; i < db_path->num_path; i++ ) {
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

	   /*loop with read ngrams */


	   word_collect_add( words_from_file, tmpword );	   
    /*do not forget about free memeory, after you assign it to dynamic array... because word_collect_array make it own alloc for it */

	   /*the end of the loop*/

	   word_collect_list( words_from_file, 10 );
	   printf("\n");
	   
	   /*if number of readed words is less than ngram length do not assign this to database*/
	   if (words_from_file->num_words < n_gram_type) {
		  word_collect_free(words_from_file);
	   } else {
		  ngram_add(ngramstack, words_from_file);
		  numb_readed_ngrams++;
	   }
	    
	   close( operations );
    }

    return 0;
}
