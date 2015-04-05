/* This module analize text file with exmaple text and make and add ngrams to current program database */
#include <string.h>
#include "textfile_analize.h"
#include "ngramstruct.h"
#include "errors.h"

/* main function of checking and analizing file*/
int analize(ngram * ngramstack, file_paths * file_path)  {  
    int i;
    /*the main loop - switch next filepaths*/
    for( i = 0; i < file_path->num_path; i++ ) {
	   /*check and eventualy delete colon from the last position*/
		  /* [IMPORTANT] add colon remover */

	   FILE * operations = fopen( file_path->file_path[i],"r");
	   if( operations == NULL ) {
		  char warning[1024] = "Błąd w wczytywaniu pliku, prawdopodobnie źle podana nazwa bądź plik jest aktualnie używany przez inny program. Nazwa wczytywanego pliku: ";
		  program_error(ERR_NORMAL, ERR_TXT_ANALIZ, strcat( warning, file_path->file_path[i] ) );  
		  continue;
	   }

        /* for now simply read and print one line from each file */
	   char * tmpline;
	   int limiter = 10;

	   while( fscanf( operations, "%s\n", tmpline ) != EOF) {
		  if( !limiter ) break;
		  printf("%s : %p\n", tmpline, &tmpline);
		  limiter--;
	   }

	   close( operations );
    }
    return 0;
}

/* auxiliary funcion to interprete 1 line of input file, return 1 if End Of File is redded, otherwise return 0 */
static int line_anal(string_stock interpreted_line, FILE * input) {
    return 0;
}
