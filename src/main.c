#include <stdio.h>

/*golbal flags*/
int 	FNGRAM = 2; 		/*says which ngrams we will be using (2 is default) */
int 	FMODE = 0; 		/* determine mode of program, 0 - generete text (default), 1- generet statistics*/
int 	FQUAWORD = 1024;	/*says how many word can product generator */
char 	FFILEEXITPATH[] = "";   /* datermine path of exit file for generator or statistic creator*/
char  	FDBEXIT[] = ""; 	/* determine path of dbexit path*/
char 	FSTRWORD[] = "";	/* determine starting word/fraze for generetor or sttistic creator */

int check_flags(int argc, char *argv[]);

void main(int argc, char * argv[]) {
	
	check_flags(argc-1, ++argv);

} 

/*recognize flags and set approprate variables*/
int check_flags(int argc, char *argv[] ){
	
	/*[IMPORTANT] switch with proper interpretetor!*/
	int i = 0;
	for(; i < argc; i++) 
		printf("%s\n", argv[i]); 


	return 0;
} 
