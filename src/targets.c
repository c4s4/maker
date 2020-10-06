#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/parser.h"

void error(char* message) {
    printf(message);
    printf("\n");
    exit(1);
}

int main() {
    char* file = find_makefile();
    if (strlen(file) == 0) {
        error("No makefile found");
    }
    char* source = read_file(file);
    printf("Makefile: %s\n", source);
    return 0;
}
