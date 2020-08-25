/**
 * Author: Richard Fernando Heise Ferreira 
 * GRR20191053
 */

#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include <stdio.h>

#ifndef _dicionario_
#define _dicionario_

/** Path to the system dictionary to be used as the main dict. */
#define BRAZILIAN_DICT_ABSOLUTE_PATH "/usr/share/dict/brazilian"

/** Amount of lines to be allocate by malloc. */
#define ALLOCATION_AMOUNT 20000

/** Amount of lines to be reallocate by realloc. 
 *  Keep in mind realloc is costly, so it's suggest
 *  that you use big numbers.
 */
#define REALLOCATION_AMOUNT 20000

/*
    A dictionary struct.
    The unsigned char matrix is the proper dictionary.
    The lines is the number of lines this dictionary has.
*/
typedef struct s_dict {
    unsigned char **dict;
    int lines;
} dictionary;

/** 
 * Function to open a file.
 * It receives a FILE pointer by reference (&file_pointer).
 */
void open_file (FILE **file_pointer);

/** 
 * Function to dinamicly allocate a dictionary.
 * It receives a dictionary address by reference (&dict).
 */ 
void dict_allocation (dictionary *dict_pointer);

/**
 * Function to dinamicly reallocate a dictionary.
 * It receives a dictionary address by reference (&dict).
 */ 
void dict_reallocation (dictionary *dict_pointer);

/**
 * Funtion to load file into a dictionary.
 * First param receives a file pointer by reference (&filep).
 * Second param is a dictionary address by reference (&dict).
 */
void load_dict (FILE **file_pointer, dictionary *dict_pointer);

/**
 * Function to initialize a dictionary.
 * It receives a dictionary address by reference (&dict).
 * This function sets the lines to 0 and calls for dict_allocation. 
 */
void start_dict (dictionary *dict_pointer);

/**
 * Funtion to transform a char into a lower case char
 * It receives a value by copy (value).
 * Returns a lower case char.
 */
unsigned char lower_case (unsigned char value);

/**
 * Funtion to check if a value is a char.
 * It receives a value by copy (value).
 * Returns 1 if value is a char, 0 otherwise.
 */
int is_character (unsigned char value);

/**
 * Funtion to search for a word in a dictionary.
 * First param is a dictionary address by reference (&dict).
 * Second param is a string.
 * Third param is the string's size by copy.
 */
int dict_binary_search(dictionary *dict_pointer, unsigned char *str, int s_size);

/**
 * Function to lower case a string
 * Essentially it's the lower_case() function
 * applied in every element of the unsgined char array.
 * Receives a unsigned char pointer.
 */
void lower_string (unsigned char **value);

#endif