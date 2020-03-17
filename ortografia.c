#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>

typedef struct s_dict {
    unsigned char **dict;
    int lines;
} dictionary;

void open_file (FILE **file_pointer) {
    (*file_pointer) = fopen("/usr/share/dict/brazilian", "r");

    if (!(*file_pointer)) {
        printf("Error: couldn't open file.");
        exit(1);
    }
}

void dict_allocation (dictionary *dict_pointer) {
    dict_pointer->dict = (unsigned char **)malloc(10000 * sizeof(unsigned char *));
    if (dict_pointer->dict == NULL) {
        printf("Error: couldn't allocate memory.");
        exit(2);
    }
    int i;
    for (i = 0; i < 10000; i++) {
        dict_pointer->dict[i] = (unsigned char *)malloc(sizeof(unsigned char));
        if (dict_pointer->dict == NULL) {
            printf("Error: couldn't allocate memory.");
            exit(2);
        }
    }
}

void dict_reallocation (dictionary *dict_pointer) {
    dict_pointer->dict = realloc(dict_pointer->dict,  (10000 + dict_pointer->lines) * sizeof(unsigned char *));
    if (dict_pointer->dict == NULL) {
        printf("Error: couldn't allocate memory.");
        exit(2);
    }
    int i;
    for (i = dict_pointer->lines; i < (10000 + dict_pointer->lines); i++) {
        dict_pointer->dict[i] = (unsigned char *)malloc(sizeof(unsigned char));
        if (dict_pointer->dict == NULL) {
            printf("Error: couldn't allocate memory.");
            exit(2);
        }
    }
}

void load_dict (FILE **file_pointer, dictionary *dict_pointer) {
    int i;
    for (i = 0; ! feof((*file_pointer)); i++ ) {
        fscanf((*file_pointer), "%s", dict_pointer->dict[i]);
        
        dict_pointer->lines++;
    
        if ( dict_pointer->lines % 9999 == 0) {
            dict_reallocation(dict_pointer);
        }
    
    }

    fclose((*file_pointer));
}

void start_dict (dictionary *dict_pointer) {
    dict_pointer->lines = 0;
    dict_allocation(dict_pointer);
}

unsigned char lower_case (unsigned char value) {
    if ( (value >= 'A' && value <= 'Z') ||
        (value >= 'À' && value <= 'Ü') ) {

        value += 32;
    }

    return value;

}

int is_character (unsigned char value) {
    value = lower_case(value);
    if ((value >= 'a' && value <= 'z') ||
        (value == 'ç') ||
        (value >= 192 && value <= 252)) {

        return 1;
    } 

    return 0;
}

int dict_binary_search(dictionary *dict_pointer, unsigned char *str, int tam) {
    int start = 0;
    int end = dict_pointer->lines-1;

    int i;
    unsigned char tmp[50];
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

int main () {
    setlocale(LC_CTYPE, "pt_BR.iso88591");
    
    FILE *arq;
    dictionary pt_dict;

    start_dict(&pt_dict);
    open_file(&arq);
    load_dict(&arq, &pt_dict);

    
    unsigned char c;
    while ( ((c = getchar()) != 255) ) {

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

        if (dict_binary_search(&pt_dict, str, tam) && c != 255) {
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
