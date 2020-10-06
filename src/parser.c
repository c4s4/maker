#include <regexp.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define REGEXP "^([\\w-_]+):"
#define MAX_GROUPS 100

// Find makefile and return its path, or empty string if not found
char* find_makefile() {
    char* candidates[] = {"Makefile", "makefile"};
    for (int i = 0; i < 2; i++) {
        if (access(candidates[i], F_OK) != -1) {
            return candidates[i];
        }
    };
    return "";
}

// Read file and return its contents as a string
char* read_file(char* filename) {
    char* buffer = NULL;
    int string_size, read_size;
    FILE* handler = fopen(filename, "r");
    if (handler) {
        fseek(handler, 0, SEEK_END);
        string_size = ftell(handler);
        rewind(handler);
        buffer = (char*)malloc(sizeof(char) * (string_size + 1));
        read_size = fread(buffer, sizeof(char), string_size, handler);
        buffer[string_size] = '\0';
        if (string_size != read_size) {
            free(buffer);
            buffer = NULL;
        }
        fclose(handler);
    }
    return buffer;
}

char** parse_makefile(char* source) {
    regex_t regexp;
    regmatch_t groups[MAX_GROUPS];
    if (regcomp(&regexp, REGEXP, REG_EXTENDED)) {
        printf("Could not compile regular expression.\n");
        return NULL;
    };
    if (regexec(&regexp, source, MAX_GROUPS, groups, 0) == 0) {
        unsigned int g = 0;
        for (g = 0; g < MAX_GROUPS; g++) {
            if (groups[g].rm_so == (size_t)-1)
                break;  // No more groups
            char copy[strlen(source) + 1];
            strcpy(copy, source);
            copy[groups[g].rm_eo] = 0;
            printf("Group %u: [%2u-%2u]: %s\n", g, groupArray[g].rm_so,
                   groupArray[g].rm_eo, sourceCopy + groupArray[g].rm_so);
        }
    }
    regfree(&regexCompiled);
}