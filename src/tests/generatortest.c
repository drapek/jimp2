#include <stdio.h>
#include "../ngramstruct.h"
#include "../generator.h"

#define MAX_WORDS 100

int main (int argc, char **argv) { 
    word_collect * arguments = word_collect_init("argv");

    int i;
    for( i = 0; i < argc; i++ )
	   word_collect_add( arguments, argv[i]);
 
    ngram * global = ngram_init();
    ngram_add( global, arguments );
    
    printf("Ngram który jest zapisywany do pliku: \n");
    ngram_list( global, 0);
    printf("\n");
    
    /*there is no functions to adding and initializig filepaths, because writing its to use it only 2 times has been a wast of time */
    file_paths * start_words  = malloc( sizeof( *start_words));
    start_words->file_path = malloc( sizeof( start_words->file_path ) * 2);
    char first_word[50] = "Adam"; 
    start_words->file_path[0] = first_word;
    char second_word[50] = "Mickiewicz";
    start_words->file_path[1] = second_word;
    start_words->num_path = 2;
    
    generate(global, start_words, 2, MAX_WORDS, "outputs/generator-wynik.txt"); 
}
