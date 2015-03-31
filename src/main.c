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

static int check_flags(int argc, char *argv[]);
void list_all_flags(); 

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

     while((opt = getopt(argc, argv, "p:b:n:d:z:x:t:")) != -1) {
	   switch (opt) {
		  case 'p': //read filepath of text-pattern files
			 is_db_or_file = 1;
			 /*[IMPORTANT] If after this parametrs is not specyfied another starred with "-", make warring which says to put "#" after last paramter */
			 break;

		  case 'b': //read filepath of databases 
			 is_db_or_file = 1;
			 /*[IMPORTANT] The same as it is in 'p'*/

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

void list_all_flags() {

printf("FNGRAM \t= %i \n"
       "FMODE \t= %i \n" 
	  "FQUAWORD \t= %i\n"
	  "FDBEXIT \t= \"%s\" \n"
       "FFILEEXITPATH \t= \"%s\" \n" 
       "FSTRWORD \t= \"%s\"\n\n"
	  , FNGRAM, FMODE, FQUAWORD, FDBEXIT, FFILEEXITPATH, FSTRWORD);


}
