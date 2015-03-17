#ifndef ERRORS_H
#define ERRORS_H

#include <stdlib>

/* serv errors by displaing inforamtion on screen and write its to log file, and exit program if needed*/
void error(int err_type, int err_code, char err_content[], int argc, char ** argv);

#endif
