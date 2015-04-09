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
    address_arr_list( temp, 0);

    address_arr_free( temp );

    /*this should be empty */
    address_arr_list( temp, 0); 

    /*but this should be such as at start*/
    printf("Start elements: [ ");
    printf("%s ", first);
    printf("%s ", second);
    printf("%s ", third);
    printf("%s ", fourth);
    printf("%s ", fifth);
    printf("]\n");
    
    /* test to overflow size given in init, to test malloc in address_arr_addi */
    address_arr * from_argv = address_arr_init();
    int i;
    for( i = 0; i < argc; i++ )
	   address_arr_add(from_argv, argv[i]);

    address_arr_list( from_argv, 0);
    address_arr_free( from_argv );
    
    return 0;
}
