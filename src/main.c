/*******************************************************************
**   Program which genereate text based on provided text files    **
** or databases. Made for university project purposes.            **
**                                                                **
** autor: Paweł Drapiewski, SEM II, wydz. Elektryczny PW 2014/2015**
** contact: drapiewki.pawel@wp.pl                                 **
** program right owner: Politechnika Warszawska                   **
*******************************************************************/

#include <string.h>
#include <stdio.h>
#include <unistd.h> /*for functions which serve input arguments */
#include "errors.h" /* to send errors into log file */
#include "ngramstruct.h"

#define MAXINT 32767

static enum PROGRAM_MODES {
    MODE_GENERETE, /* genereate text and some statistics*/
    MODE_STATISTIC /*generete only statistic of input text */
};

/*golbal flags, visible only inside this file*/
static int FNGRAM = 2; 		/*says which ngrams we will be using (2 is default) */
static int FMODE = MODE_GENERETE; 		/* determine mode of program, 0 - generete text (default), 1- generet statistics*/
static int FQUAWORD = 1024;	/*says how many word can product generator */
static char FDBEXIT[1024] = "";    /* path of file where our dabase will be sotored */
static char FFILEEXITPATH[1024] = "prodtekst_wynik.txt";   /* datermine path of exit file for generator or statistic creator*/
static char FFILEEXITSTATISTICS[1024] = ""; /*output filepath where statistic will be stored */
static char FSTRWORD[4096] = "";	/* determine starting word/fraze for generetor or sttistic creator */
static file_paths text_files; /*store pointer to argv where text files paths starts */
static file_paths db_files; /*store pointer to argv where database files paths starts */

static int check_flags(int argc, char *argv[]);
static void list_all_flags();
static void read_file_paths(int argc, char ** argv, char * flag);

void main(int argc, char * argv[]) {
    
    /*it is possible that getopt is't work because it neede full parametrs of argc and argv*/
    //check_flags(argc-1, ++argv);
    check_flags(argc, argv);

} 

/*recognize flags and set approprate variables*/
static int check_flags(int argc, char * argv[] ){
	int opt;
	int tmp;
	int is_db_or_file = 0; //is readen at least one databes or one textfile
	extern char * optarg;
     char * usage = 
	"Krótki opis wywołania programu\n"
	"koniec krótkiego opisu programu \n\n";
    
    /*initializing file paths sturctures */
    text_files.file_path = NULL;
    text_files.num_path = 0;
    db_files.file_path = NULL;
    db_files.num_path = 0;

    while((opt = getopt(argc, argv, "p:b:n:d:z:x:t:")) != -1) {
	   switch (opt) {
		  case 'p': //read filepath of text-pattern files
			 is_db_or_file = 1;
			 read_file_paths(argc, argv, "-p");
			 break;

		  case 'b': //read filepath of databases 
			 is_db_or_file = 1;
			 read_file_paths(argc, argv, "-b");
			 break;

		  case 'n': //digit indicating used n-grams
			 tmp = atoi( optarg );
			 if(tmp > 1 && tmp <= 20)
				FNGRAM = tmp;
			 else {
				program_error( 1, 0, strcat("Niepoprawnie podany ngram, dopszuczalne są z zakresu od 1 do 20, a podany został: ", optarg ));
			 }
			 break;

		  case 'd': //maximum quantity of produced word by text generator
			 tmp = atoi( optarg );
			 if(tmp > 0 && tmp <= MAXINT) 
				FQUAWORD = tmp;
			 else {
				program_error( 1, 0, strcat("Niepoprawnie podana liczba słów, dopszuczalne ilość słów waha się od 1 do MAXINT, a przez ciebie podana liczba to: ", optarg ));
			 }
			 break;

		  case 'z': //determine the path of file which contain the program result 
			 strcpy(FFILEEXITPATH, optarg);
			 break;

		  case 'x': //determine the path of file for database
			 strcpy(FDBEXIT, optarg);
			 break;

		  case 't'://determine mode of program
			 ; /*beacasue in C is not allowed to put declaration after label ('t':) */
			 /*because strcmp is not working with optarg*/
			 char tmp_mode[10] = "AdamMalys\0";
			 strcpy(tmp_mode, optarg);

			 if( tmp_mode[0] == 'p' ) 
				;
			 else if( tmp_mode[0] == 's')
				FMODE = MODE_STATISTIC;
			 else {
				program_error( 1, 0, "Podałeś niepoprawny tryb programu, doposzczalne to s dla statystyki, oraz p dla produkcji (domyślnie)");
			 }
			 break;

		  default:
			 /*[IMPORTANT] add information about using program (which flags are allowed etc) */
			 program_error( 1, 0, "Invalid parametr has been used! Check documentation before using!");
			 break;
			 
		  }
	   }
	   
	   /*check if at least one input file is readed*/
	   if(!is_db_or_file) {
		  printf("%s", usage);
		  program_error(ERR_CRITIC, ERR_FLAG_INTERPRET, "Nie podałeś pliku z bazą danych lub pliku z tekstem wejściowym!"); 
	   }

	#ifdef debug
	/*listing all readed parametrs*/
	list_all_flags(); 
     #endif

	return 0;
} 

static void list_all_flags() {
    int i;
    printf("FNGRAM      \t= %i \n"
       "FMODE   \t= %i \n" 
	  "FQUAWORD \t= %i\n"
	  "FDBEXIT \t= \"%s\" \n"
       "FFILEEXITPATH \t= \"%s\" \n" 
       "FSTRWORD \t= \"%s\"\n"
	  , FNGRAM, FMODE, FQUAWORD, FDBEXIT, FFILEEXITPATH, FSTRWORD);

    printf("text_files: \t= [ ");
    for( i = 0; i < text_files.num_path; i++ )
	  printf("%s\"%s\"", (i == 0) ? "" : ", ", text_files.file_path[i]);
    printf(" ]\n");

    printf("db_files: \t= [ ");
    for( i = 0; i < db_files.num_path; i++ )
	  printf("%s\"%s\"", (i == 0) ? "" : ", ", db_files.file_path[i]);
    printf(" ]\n");
 
    printf("\n");
}

/* return the size of dynamic char array */
int dyn_arr_size(char * arr) {
    int i = 0;
    while( *(arr++) != '\0') 
	   i++;
    return i;
}
/*this function serach in argv for file paths and assign it to aproprate file structure. By now argument flag can be "-p" for text file paths or "-b" for database paths */
static void read_file_paths(int argc, char ** argv, char * flag) {
    /* determines position of flag  in argv array */
    int argv_position = 0;
    while( strstr(argv[argv_position], flag) == NULL ) 
	   argv_position++;
    argv_position++;
			 
    /*search the end of filepaths*/
    int num_of_paths = 0;
    while( ( argv[argv_position + num_of_paths][0] != '-' ) && ( argv[argv_position + num_of_paths][0] != '@' ) ) {
	   num_of_paths++;
	   /*check if this parametr has end, because if it is a last flag in order, it must be ended byi @, in another way it dispaly error */
	   if( argc <= ( argv_position + num_of_paths ) )
		  program_error(ERR_CRITIC, ERR_FLAG_INTERPRET, "Gdy scieżki plików są wczytywane jako ostatni argument, to muszą być zakończone poprzez znak \"@\", ponieważ w innym przypadku program nie mógłby znaleźć początku kolejnego parametru, jakim jest ciąg znaków przedstawiajacy startowy tekst dla generatora.\n np. prodtek [...] -p plik1.txt plik2.txt @ początek tekstu do generowania");
	   }   
			 
	   /*chec if the next argument in argv is not a another flag (which starts by "-")*/
	   if( num_of_paths == 0 )
		  program_error(ERR_CRITIC, ERR_FLAG_INTERPRET, "Nie podano ścieżek plików za paramterem -p lub -b! ");
	   
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

	   if( strcmp("-p", flag) == 0 ) {
		  text_files.file_path = new;
		  text_files.num_path = num_of_paths;
	   }
	   
	   if( strcmp("-b", flag) == 0 ) {
		  db_files.file_path = new;
		  db_files.num_path = num_of_paths;

	   }
	   
}
