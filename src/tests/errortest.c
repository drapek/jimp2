#include "../errors.h"
#include <stdio.h>

int main() {
    
    printf("Testowy tekst... testowy tekst... \n");

    printf("Błąd standardowy (bez zakończenia programu) \n");
    program_error(0, 0, "Testowy Error standardowy");
  
    printf("Testowy tekst... testowy tekst... \n");
    
    printf("Błąd krytyczny (z zakończeniem programu) \n");
    program_error(1, 0, "Krytyczny Error");

    printf("Tekst znajdujący się w funkcji po błędzie krytycznym (nie powinien się pojawić) \n");

    return 0;
}
