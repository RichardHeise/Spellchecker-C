/**
 * Author: Richard Fernando Heise Ferreira 
 * GRR20191053
 */

#include "dicionario.h"

int main () {

    if (! setlocale(LC_CTYPE, LOCALE)) {
        printf("Couldn't set the program locale to %s \n", LOCALE);
        exit(-3);
    }

    // we gonna work with this dictionary in ISO-8859-1
    setlocale(LC_CTYPE, LOCALE);
    
    // Pointer to a file and declaration of a dict variable
    FILE *arq;
    dictionary pt_dict;

    // Dictionary operations.
    start_dict(&pt_dict);
    open_file(&arq);
    load_dict(&arq, &pt_dict);
  
    unsigned char input_char;
    while ( (input_char = getchar()) && (! feof(stdin)) ) {

        while ( !(is_character(input_char)) && (! feof(stdin)) ) {  
            printf("%c", input_char);
            input_char = getchar();
        }

        unsigned char word[50] = {0};
        int w_size = 0;
        while ( (is_character(input_char)) && (! feof(stdin)) ) {
            word[w_size] = input_char;
            w_size++;
            input_char = getchar();
        }

        if (dict_binary_search(&pt_dict, word, w_size) || (feof(stdin))) {
            printf("%s" , word);
        } else {
            printf("[%s]", word);
        }
        
        if (! feof(stdin)) {
            printf("%c", input_char);
        }
    }

    free_dict(&pt_dict);

    printf("\n");
    return 1;
}
