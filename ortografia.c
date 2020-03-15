#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void open_file (FILE **file_pointer) {
    (*file_pointer) = fopen("brazilian", "r+");

    if (!(*file_pointer)) {
        printf("Error: couldn't open file.");
        exit(1);
    }
}

void matrix_allocantion (unsigned char ***matrix) {
    *matrix = (unsigned char **)malloc(sizeof(unsigned char *));
    if ((*matrix) == NULL) {
        printf("Error: couldn't allocate memory.");
        exit(2);
    }

    (*matrix)[0] = (unsigned char *)malloc(sizeof(unsigned char));
    if ((*matrix) == NULL) {
        printf("Error: couldn't allocate memory.");
        exit(2);
    }
}

void matrix_reallocation (unsigned char ***matrix) {
    *matrix = realloc(*matrix,  50 * sizeof(unsigned char *));
    if ((*matrix) == NULL) {
        printf("Error: couldn't allocate memory.");
        exit(2);
    }
}

void load_dict (FILE *file_pointer, char unsigned **dict_pointer) {
    
}

int main () {
    
    FILE *arq;
    unsigned char **dict;

    matrix_allocantion(&dict);
    open_file(&arq);
    


    fclose(arq);
    return 1;
}
