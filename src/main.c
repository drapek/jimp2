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

/*golbal flags*/
int FNGRAM = 2; 		/*says which ngrams we will be using (2 is default) */
int FMODE = 0; 		/* determine mode of program, 0 - generete text (default), 1- generet statistics*/
int FQUAWORD = 1024;	/*says how many word can product generator */
char FDBEXIT[] = "";
char FFILEEXITPATH[] = "prodtekst_wynik.txt";   /* datermine path of exit file for generator or statistic creator*/
char FSTRWORD[] = "";	/* determine starting word/fraze for generetor or sttistic creator */

int check_flags(int argc, char *argv[]);

void main(int argc, char * argv[]) {
	
	check_flags(argc-1, ++argv);

} 

/*recognize flags and set approprate variables*/
int check_flags(int argc, char * argv[] ){
	int opt;
	int tmp;
	int is_db_or_file = 0; //is readen at least one databes or one textfile

	/*[IMPORTANT] switch with proper interpretetor!*/
     while((opt = getopt(argc, argv, "p:b:n:d:z:x:t")) != -1) {
	   switch (opt) {
		  case 'p': //read filepath of text-pattern files
			 
			 is_db_or_file = 1;
			 break;

		  case 'b': //read filepath of databases 
			 
			 is_db_or_file = 1;
			 break;

		  case 'n': //digit indicating used n-grams
			 tmp = atoi( optarg );
			 if(tmp > 0 && tmp <= 20)
				FNGRAM = tmp;
			 else {
				// [DELETE] char * information[] = "Niepoprawnie podany ngram, dopszuczalne są z zakresu od 1 do 20, a podany został: ";
				error( 1, 0, strcat("Niepoprawnie podany ngram, dopszuczalne są z zakresu od 1 do 20, a podany został: ", optarg ));
			 }
			 break;

		  case 'd': //maximum quantity of produced word by text generator
			 tmp = atoi( optarg );
			 if(tmp > 0 && tmp <= MAXINT) 
				FQUAWORD = tmp;
			 else {
				//[DELETE] char * information[] = "Niepoprawnie podana liczba słów, dopszuczalne ilość słów waha się od 1 do 32767, a przez ciebie podana liczba to: ";
				error( 1, 0, strcat("Niepoprawnie podana liczba słów, dopszuczalne ilość słów waha się od 1 do 32767, a przez ciebie podana liczba to: ", optarg ));
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
			 if( optarg[0] == 'p' ) 
				;
			 else if( optarg[0] == 's')
				FMODE = 1;
			 else {
					//[DELETE] char * information[] = "Podałeś niepoprawny tryb programu, doposzczalne to s dla statystyki, oraz p dla produkcji (domyślnie),a ty podałeś: ";
				error( 1, 0,  strcat("Podałeś niepoprawny tryb programu, doposzczalne to s dla statystyki, oraz p dla produkcji (domyślnie),a ty podałeś: ", optarg ));
			 }
			 break;

		  default:
			 /*[IMPORTANT] add information about using program (which flags are allowed etc) */
			 //[DELETE] char * information[] = "Invalid parametr has been used! Check documentation before using!
			 error( 1, 0, "Invalid parametr has been used! Check documentation before using!");
			 break;
 
		  }
	   }

	#ifdef debug
	/*listing all readed parametrs*/
	int i = 0;
	for(; i < argc; i++) 
		printf("%s\n", argv[i]); 
     #endif

	return 0;
} 
