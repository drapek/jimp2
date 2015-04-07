#include <stdio.h>
#include "../ngramstruct.h"
#include "../database.h"

int main (int argc, char **argv) { 
    word_collect * arguments = word_collect_init("argv");

    int i;
    for( i = 0; i < argc; i++ )
	   word_collect_add( arguments, argv[i]);
 
    ngram * global = ngram_init();
    ngram_add( global, arguments );
    
    word_collect * imiona = word_collect_init("imiona");
    word_collect_add(imiona, "Basia");
    word_collect_add(imiona, "Kasia");
    word_collect_add(imiona, "Marysia");
    word_collect_add(imiona, "Robert");
    word_collect_add(imiona, "Grześ");
    word_collect_add(imiona, "Mariusz");

    ngram_add( global, imiona);

    printf("Ngram który jest zapisywany do pliku: \n");
    ngram_list( global, 0);
    printf("\n");

    /*here start proper testing database */

    save_ngram(global, "db_files/dbtest_saved.db");

    /*there is no functions to adding and initializig filepaths, because writing its to use it only 2 times has been a wast of time */
    ngram * readed = ngram_init();
    file_paths * wsadowe  = malloc( sizeof( *wsadowe));
    wsadowe->file_path = malloc( sizeof( wsadowe->file_path ) * 1);
    char db_in_path[100] = "db_files/dbtest_saved.db"; 
    wsadowe->num_path = 1;
    wsadowe->file_path[0] = db_in_path;

    read_ngrams(readed, wsadowe);
    
    printf("Ngram odczytany z pliku wcześniej zapisanego: \n");
    ngram_list( readed, 0);
    printf("\n");


}
