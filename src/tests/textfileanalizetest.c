#include <stdio.h>
#include <string.h>
#include "../errors.h"
#include "../ngramstruct.h"
#include "../textfile_analize.h"

static void argv_to_file_paths(file_paths * global, int argc, char ** argv);

void main( int argc, char ** argv) {
    if( argc < 2 ) {
	   printf("Jako argumenty podaj ścieżki plików z tekstem\n");
	   exit(1);
    }

    file_paths global;
    argv_to_file_paths(&global, argc, argv);

    printf("Readed file_paths: ");
    file_paths_list(global);
    printf("\n");
    
    ngram * global_ngram;
    analize(global_ngram, &global );

}

/* return the size of dynamic char array */
int dyn_arr_size(char * arr) {
    int i = 0;
    while( *(arr++) != '\0') 
	   i++;
    return i;
}
/*this function serach in argv for file paths and assign it to aproprate file structure. By now argument flag can be "-p" for text file paths or "-b" for database paths */
static void argv_to_file_paths(file_paths * global, int argc, char ** argv) {
    /* determines position of flag  in argv array */
    int argv_position = 1; 
    int num_of_paths = argc - 1;
	   
   /*weird things happen with argv array, so it is better to allocate private memory instead assign argv values */
   char ** new = malloc( sizeof( *new ) * num_of_paths);
   if( new == NULL ) 
	  program_error(ERR_CRITIC, ERR_FLAG_INTERPRET, "Brak pamięci dla stworzenia tablicy przechowującej ścieżki plików (funk read_file_path)");
   
   int i;
   for( i = 0; i < num_of_paths; i++ ) {
	  size_t size = dyn_arr_size( argv[argv_position + i] ) + 1;
	  new[i] = malloc( ( size = sizeof( char ) * size ) );
	  if( new[i] == NULL)
		 program_error(ERR_CRITIC, ERR_FLAG_INTERPRET, "Brak pamięci dla zallokowania dla ścieżek plików (funkcja read_file_path)");
	  memcpy(new[i], argv[argv_position + i], size);
    }

    global->file_path = new;
    global->num_path = num_of_paths;
}
