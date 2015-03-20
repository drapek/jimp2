#include "errors.h"

void error(int err_type, int err_code, char err_content[]) {
    /*[IMPORTANT] add saving to logfile */
    fprintf(stderr, "[ERROR] type: %s, err_code: %d, problem: %s", (err_type == 0) ? "standardowy" : "krytyczny", err_code, err_content );

}

