#include <stdio.h>
#include "../errors.h"

int main() {
    int i;
    for( i = 0; i < 10; i++) {
	   program_error(0, i, "test testowania testowanego");
    }
}
