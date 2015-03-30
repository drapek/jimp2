#include "errors.h"
#include <time.h>

static char * del_eol(char * where); 

void program_error(int err_type, int err_code, char * err_content) {
    /*[IMPORTANT] add saving to logfile */
    FILE * logfile = fopen("logfile.csv", "a+");
    
    /*for time and date which will be saved in log file*/
    time_t rawtime;
    struct tm * timeinfo;
    time(&rawtime);
    timeinfo = localtime( &rawtime );
    
    fprintf(logfile, "\"%s\";%i;%i;\"%s\"\n", del_eol(asctime( timeinfo )), err_type, err_code, err_content);

    fclose(logfile);

    fprintf(stderr, "[ERROR] type: %s, err_code: %d, problem: \"%s\"\n", (err_type == 0) ? "standardowy" : "krytyczny", err_code, err_content );
  
   
   /*[IMPORTANT] add free memory */
   if( err_type == 1 ) {
	   exit(EXIT_FAILURE);
   }

}

/* remove end of line charakter - nedded to timeinfo */
static char * del_eol(char * where) {
    int i = 0;
    while( where[i] != '\0') {
	   if( where[i] == '\n' ) 
		  where[i] = '\0';
	   i++;
    }
    return where;
}

