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
static file_paths text_files; /*store pointer to argv where text files paths starts */
static file_paths db_files; /*store pointer to argv where database files paths starts */
static file_paths start_words; /*brutal but esay way to store starts words, because this structure fit perfect for this purpose*/

static int check_flags(int argc, char *argv[]);
static void list_all_flags();
static void read_file_paths(int argc, char ** argv, char * flag);
static int find_start_wrd(int argc, char** argv);

void main(int argc, char * argv[]) {
    
    /*it is possible that getopt is't work because it neede full parametrs of argc and argv*/
    //check_flags(argc-1, ++argv);
    check_flags(argc, argv);

} 

/*recognize flags and set approprate variables*/
static int check_flags(int argc, char * argv[] ){
	int opt;
	int tmp;
	int is_db = 0; /*if it dabase is readen */
	int is_file = 0; /*if it text file is readen */
	extern char * optarg;
     char * usage = 
	"Krótki opis wywołania programu\n"
	"koniec krótkiego opisu programu \n\n";
    
    /*initializing file paths sturctures */
    text_files.file_path = NULL;
    text_files.num_path = 0;
    db_files.file_path = NULL;
    db_files.num_path = 0;
    start_words.file_path = NULL;
    start_words.num_path = 0;

    while((opt = getopt(argc, argv, "p:b:n:d:z:x:t:")) != -1) {
	   switch (opt) {
		  case 'p': //read filepath of text-pattern files
			 if(is_file)
				program_error(ERR_CRITIC, ERR_FLAG_INTERPRET, "Podałeś dwa razy paramter -p! co jest nie dopuszczalne.");

			 is_file = 1;
			 read_file_paths(argc, argv, "-p");
			 break;

		  case 'b': //read filepath of databases 
			 if( is_db )
				program_error(ERR_CRITIC, ERR_FLAG_INTERPRET, "Podałeś dwa razy paramter -b! co jest nie dopuszczalne.");

			 is_db = 1;
			 read_file_paths(argc, argv, "-b");
			 break;

		  case 'n': //digit indicating used n-grams
			 tmp = atoi( optarg );
			 if(tmp > 1 && tmp <= 20)
				FNGRAM = tmp;
			 else {
				program_error( ERR_CRITIC, ERR_FLAG_INTERPRET, "Niepoprawnie podany ngram, dopszuczalne są z zakresu od 1 do 20.");
			 }
			 break;

		  case 'd': //maximum quantity of produced word by text generator
			 tmp = atoi( optarg );
			 if(tmp > 0 && tmp <= MAXINT) 
				FQUAWORD = tmp;
			 else {
				program_error( ERR_CRITIC, ERR_FLAG_INTERPRET, "Niepoprawnie podana liczba słów, dopszuczalna ilość słów waha się pomiędzy 1 a 32767.");
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
			 char tmp_mode[10] = "";
			 strcpy(tmp_mode, optarg);

			 if( tmp_mode[0] == 'p' ) 
				;
			 else if( tmp_mode[0] == 's')
				FMODE = MODE_STATISTIC;
			 else {
				program_error( ERR_CRITIC, ERR_FLAG_INTERPRET, "Podałeś niepoprawny tryb programu, doposzczalne to s dla statystyki, oraz p dla produkcji (domyślnie)");
			 }
			 break;

		  default:
			 /*[IMPORTANT] add information about using program (which flags are allowed etc) */
			 program_error( ERR_CRITIC, ERR_FLAG_INTERPRET, "Invalid parametr has been used! Check documentation before using!");
			 break;
			 
		  }
	   }
	  
	   /*finds statring words */
	   find_start_wrd(argc, argv);
	   /*check if at least one input file is readed*/
	   if(!is_db && !is_file) {
		  printf("%s", usage);
		  program_error(ERR_CRITIC, ERR_FLAG_INTERPRET, "Nie podałeś pliku z bazą danych lub pliku z tekstem wejściowym! A musi choć jedna z nich zostać wczytana."); 
	   }

	#ifdef debug
	/*listing all readed parametrs*/
	list_all_flags(argc, argv); 
     #endif

	return 0;
} 

/*function which finds a start word to generator at the and of argv and return pointer to array with words, but if it impossible to find it's only return NULL pointer */
static int find_start_wrd(int argc, char** argv) {
    argc--; /*because argv[argc] is null pointer */
    int wrd_start = argc;
    int isMinus = 0;
    while( argv[wrd_start][0] != '@' ) {
	   if( argv[wrd_start][0] == '-' ) {
		  isMinus = 1;
		  break;
	   }
	   wrd_start--;
	   if(wrd_start == 0 )
		  return 1; /* because argv[0] is alway the name of program */
	   
    }
    
    wrd_start++; /* to point one cell after "-..." or "@" */
    if( isMinus )
	   wrd_start++; /*because flgas "-..." has one argument after them */

    int num_of_wrd = argc - wrd_start + 1;
    if( num_of_wrd <= 0 )
	   return 1; /*return that start word can't be find */

    char ** new = malloc( sizeof( *new ) * num_of_wrd);
    if( new == NULL ) 
	  program_error(ERR_CRITIC, ERR_FLAG_INTERPRET, "Brak pamięci dla stworzenia tablicy przechowującej słowa startowe (funk find_start_wrd)");
    
    int i;
    for( i = 0; i < num_of_wrd; i++ ) {
	   size_t size = dyn_arr_size( argv[wrd_start + i] ) + 1;
	   new[i] = malloc( ( size = sizeof( char ) * size ) );
	   if( new[i] == NULL)
		  program_error(ERR_CRITIC, ERR_FLAG_INTERPRET, "Brak pamięci dla zallokowania dla zapisania słów startowych w pamięci (funk find_start_wrd)");
	   memcpy(new[i], argv[wrd_start + i], size);
    }

    start_words.file_path = new;
    start_words.num_path = num_of_wrd;
    return 0;
}

static void list_all_flags() {
    int i;
    printf("FNGRAM      \t= %i \n"
       "FMODE   \t= %i \n" 
	  "FQUAWORD \t= %i\n"
	  "FDBEXIT \t= \"%s\" \n"
       "FFILEEXITPATH \t= \"%s\" \n" 
	  , FNGRAM, FMODE, FQUAWORD, FDBEXIT, FFILEEXITPATH);

    printf("text_files \t= [ ");
    for( i = 0; i < text_files.num_path; i++ )
	  printf("%s\"%s\"", (i == 0) ? "" : ", ", text_files.file_path[i]);
    printf(" ]\n");

    printf("db_files \t= [ ");
    for( i = 0; i < db_files.num_path; i++ )
	  printf("%s\"%s\"", (i == 0) ? "" : ", ", db_files.file_path[i]);
    printf(" ]\n");
    
    printf("start words \t= [ ");
    for( i = 0; i < start_words.num_path; i++ )
	  printf("%s\"%s\"", (i == 0) ? "" : ", ", start_words.file_path[i]);
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

	   /* change to assign to a new array not argv*/
	   if( strcmp("-p", flag) == 0 ) {
		  text_files.file_path = new;
		  text_files.num_path = num_of_paths;
	   }
	   
	   if( strcmp("-b", flag) == 0 ) {
		  db_files.file_path = new;
		  db_files.num_path = num_of_paths;

	   }
	   
}
