#include <stdio.h>
#include "../errors.h"
#include "../ngramstruct.h"

int main( int argc, char ** argv) {
    /* example char * strings */
    char first[100] = "Jestem";
    char second[100] = "Agnieszka";
    char third[100] = "która";
    char fourth[100] = "tutaj";
    char fifth[100] = "juz nie mieszka";

    address_arr * temp = address_arr_init();

    address_arr_add(temp, first);
    address_arr_add(temp, second);
    address_arr_add(temp, third);
    address_arr_add(temp, fourth);
    address_arr_add(temp, fifth);
    
    /* print this array */
    

}
