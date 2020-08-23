/**
 * Author: Richard Fernando Heise Ferreira 
 * GRR20191053
 */

#include "dicionario.h"

int main () {

    setlocale(LC_CTYPE, "pt_BR.iso88591");
    
    FILE *arq;
    dictionary pt_dict;

    start_dict(&pt_dict);
    open_file(&arq);
    load_dict(&arq, &pt_dict);
  
    unsigned char c;
    while ( ((c = getchar()) != 255 ) ){

        while ( !(is_character(c)) && (c != 255) ) {  
            printf("%c", c);
            c = getchar();
        }

        unsigned char str[50] = {0};
        int tam = 0;
        while ( (is_character(c)) && (c != 255) ) {
            str[tam] = c;
            tam++;
            c = getchar();
        }

        if (dict_binary_search(&pt_dict, str, tam) || (c == 255)) {
            printf("%s" , str);
        } else {
            printf("[%s]", str);
        }
        
        if (c != 255) {
            printf("%c", c);
        }
    }

    printf("\n");
    return 1;
}
