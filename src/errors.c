#include "errors.h"

void program_error(int err_type, int err_code, char * err_content) {
    /*[IMPORTANT] add saving to logfile */
   fprintf(stderr, "[ERROR] type: %s, err_code: %d, problem: \"%s\"\n", (err_type == 0) ? "standardowy" : "krytyczny", err_code, err_content );
   
   /*[IMPORTANT] add free memory */
   if( err_type == 1 ) {
	   exit(EXIT_FAILURE);
   }

}

