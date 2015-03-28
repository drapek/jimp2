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

/*nedded to log file, says where error ocurrs*/
enum ERRORS_CODES {
    ERR_FLAG_INTERPRET /*error occurs in check_flags function */
};

enum ERRORS_TYPES {
    ERR_NORMAL, /* only print errors */
    ERR_CRITIC /* close program */
};

/*golbal flags, visible only inside this file*/
static int FNGRAM = 2; 		/*says which ngrams we will be using (2 is default) */
static int FMODE = 0; 		/* determine mode of program, 0 - generete text (default), 1- generet statistics*/
static int FQUAWORD = 1024;	/*says how many word can product generator */
static char FDBEXIT[1024] = "";    /* path of file where our dabase will be sotored */
static char FFILEEXITPATH[1024] = "prodtekst_wynik.txt";   /* datermine path of exit file for generator or statistic creator*/
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

     while((opt = getopt(argc, argv, "p:b:n:d:z:x:t")) != -1) {
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
				program_error( 1, 0, strcat("Niepoprawnie podana liczba słów, dopszuczalne ilość słów waha się od 1 do 32767, a przez ciebie podana liczba to: ", optarg ));
			 }
			 break;

		  case 'z': //determine the path of file which contain the program result 
			 strcpy(FFILEEXITPATH, optarg);
			 break;

		  case 'x': //determine the path of file for database
			 strcpy(FDBEXIT, optarg);
			 break;

		  case 't': //determine mode of program
			 /*gdy wybrany tryb to produkcja*/
			 if( strcmp(optarg, "p") == 0 ) 
				;
			 else if( optarg == "s")
				FMODE = 1;
			 else {
				program_error( 1, 0,  strcat("Podałeś niepoprawny tryb programu, doposzczalne to s dla statystyki, oraz p dla produkcji (domyślnie),a ty podałeś: ", optarg ));
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
