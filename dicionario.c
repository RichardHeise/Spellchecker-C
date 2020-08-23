/**
 * Author: Richard Fernando Heise Ferreira 
 * GRR20191053
 */

#include "dicionario.h"

void open_file (FILE **file_pointer) {

    // Open a file in read mode
    (*file_pointer) = fopen(BRAZILIAN_DICT_ABSOLUTE_PATH, "r");

    if (!(*file_pointer)) {
        printf("Error: couldn't open file.");
        exit(-1);
    }
}

void dict_allocation (dictionary *dict_pointer) {

    // Allocates 20000 lines.
    dict_pointer->dict = (unsigned char **)malloc(20000 * sizeof(unsigned char *));
    if (dict_pointer->dict == NULL) {
        printf("Error: couldn't allocate memory.");
        exit(-2);
    }

    int i;
    for (i = 0; i < 20000; i++) {
        // Allocates only the first element of each string
        // C can deal with string sizes alone

        dict_pointer->dict[i] = (unsigned char *)malloc(sizeof(unsigned char));
        if (dict_pointer->dict == NULL) {
            printf("Error: couldn't allocate memory.");
            exit(-2);
        }
    }
}

void dict_reallocation (dictionary *dict_pointer) {

    // Increases the maximum amount of lines by 20000
    dict_pointer->dict = realloc(dict_pointer->dict, (20000 + dict_pointer->lines) * sizeof(unsigned char *));
    if (dict_pointer->dict == NULL) {
        printf("Error: couldn't allocate memory.");
        exit(-2);
    }

    int i;
    for (i = dict_pointer->lines; i < (20000 + dict_pointer->lines); i++) {
        dict_pointer->dict[i] = (unsigned char *)malloc(sizeof(unsigned char));
        if (dict_pointer->dict == NULL) {
            printf("Error: couldn't allocate memory.");
            exit(-2);
        }
    }
}

unsigned char lower_case (unsigned char value) {
    // Char values based on ISO-8859-1 table
    // "Hardcoded" so it's less buggy
    if ( (value >= 65 && value <= 90) ||
        (value >= 192 && value <= 220) ) {

        value += 32;
    }
    // if the reader found this obscure,
    // have a look at the ISO table mentioned
    
    return value;

}

void lower_string (unsigned char **value) {
    int i;
    for (i = 0; (*value)[i] != '\0'; i++) {
        (*value)[i] = lower_case((*value)[i]);
    }
    return;
}

int compare_strs (const void* str_a, const void* str_b ) {
    const unsigned char *pointer_a = *(const unsigned char**)str_a;
    const unsigned char *pointer_b = *(const unsigned char**)str_b;

    return strcmp(pointer_a,pointer_b);
}

void load_dict (FILE **file_pointer, dictionary *dict_pointer) {

    int i;
    for (i = 0; ! feof((*file_pointer)); i++ ) {

        // Copy each word from the file dict into the program dict
        fscanf((*file_pointer), "%s", dict_pointer->dict[i]);
        lower_string(&dict_pointer->dict[i]);

        dict_pointer->lines++;

        // When it's needed the amount of lines increases
        if ( dict_pointer->lines % 19999 == 0) {
            dict_reallocation(dict_pointer);
        }
    
    }

    // sorts the program dict 
    qsort(dict_pointer->dict, dict_pointer->lines, sizeof(unsigned char *), compare_strs);

    // Closes file for good.
    fclose((*file_pointer));
}

void start_dict (dictionary *dict_pointer) {
    dict_pointer->lines = 0;
    dict_allocation(dict_pointer);
}

int is_character (unsigned char value) {
    value = lower_case(value);
    if ((value >=  97 && value <= 122) ||
        (value == 231) ||
        (value >= 192 && value <= 252)) {

        return 1;
    } 
    // if the reader found this obscure,
    // have a look at the ISO table mentioned

    return 0;
}

int dict_binary_search(dictionary *dict_pointer, unsigned char *str, int tam) {
    int start = 0;
    int end = dict_pointer->lines-1;

    int i;
    // Temporary buffer initialized with 0 in all positions
    unsigned char tmp[50] = {0};

    // lower cases the temporary buffer so search can be done
    for (i = 0; i <= tam; i++) {
        tmp[i] = lower_case(str[i]);
    }

    while( start <= end ) {
        int mid = (start + end)/2;

        if ( strcmp((char*)tmp, (char*)dict_pointer->dict[mid]) == 0) {
            return mid;

        } else if( strcmp((char*)tmp, (char*)dict_pointer->dict[mid]) < 0) {
            end = mid-1;

        } else {
            start = mid+1;
        }
    }
   return 0;
}