#ifndef ERRORS_H
#define ERRORS_H

#include <stdlib.h>
#include <stdio.h>

/*nedded to log file, says where error ocurrs*/
enum ERRORS_CODES {
    ERR_FLAG_INTERPRET, /*error occurs in check_flags function */
    ERR_NGRAM_STRUCT, /*errors occurs in ngramstruct module */
    ERR_TXT_ANALIZ /* .. in text_analizator */
};

enum ERRORS_TYPES {
    ERR_NORMAL, /* only print errors */
    ERR_CRITIC /* close program */
};

/* serv errors by displaing inforamtion on screen and write its to log file, and exit program if needed*/
void program_error(int err_type, int err_code, char * err_content);

#endif
