#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct s_dict {
    unsigned char **dict;
    int lines;
} dictionary;

void open_file (FILE **file_pointer) {
    (*file_pointer) = fopen("brazilian", "r+");

    if (!(*file_pointer)) {
        printf("Error: couldn't open file.");
        exit(1);
    }
}

void dict_allocation (dictionary *dict_pointer) {
    dict_pointer->dict = (unsigned char **)malloc(100 * sizeof(unsigned char *));
    if (dict_pointer->dict == NULL) {
        printf("Error: couldn't allocate memory.");
        exit(2);
    }
    int i;
    for (i = 0; i < 100; i++) {
        dict_pointer->dict[i] = (unsigned char *)malloc(sizeof(unsigned char));
        if (dict_pointer->dict == NULL) {
            printf("Error: couldn't allocate memory.");
            exit(2);
        }
    }
}

void dict_reallocation (dictionary *dict_pointer) {
    dict_pointer->dict = realloc(dict_pointer->dict,  (100 + dict_pointer->lines) * sizeof(unsigned char *));
    if (dict_pointer->dict == NULL) {
        printf("Error: couldn't allocate memory.");
        exit(2);
    }
    int i;
    for (i = dict_pointer->lines; i < (100 + dict_pointer->lines); i++) {
        dict_pointer->dict[i] = (unsigned char *)malloc(sizeof(unsigned char));
        if (dict_pointer->dict == NULL) {
            printf("Error: couldn't allocate memory.");
            exit(2);
        }
    }
}

int cmpfunc (const void * a, const void * b) {
   return( strcmp( *((const char **)a), *((const char **)b)));
}

void load_dict (FILE **file_pointer,dictionary *dict_pointer) {
    int i;
    for (i = 0; ! feof((*file_pointer)); i++ ) {
        fscanf((*file_pointer), "%s", dict_pointer->dict[i]);
        
        if ( dict_pointer->lines % 98 == 0) {
            dict_reallocation(dict_pointer);
        }

        dict_pointer->lines++;
    }

    qsort(dict_pointer->dict, dict_pointer->lines, sizeof(unsigned char *), cmpfunc);
    fclose((*file_pointer));
}

void start_dict (dictionary *dict_pointer) {
    dict_pointer->lines = 0;
    dict_allocation(dict_pointer);
}

void lower_case (unsigned char *value) {
    if (((*value) >= 'A' && (*value) <= 'Z')) {
        value -= 32;
    } else if ((*value) >= 'À' && (*value) <= 'Ü') {
        value += 32;
    }
}

int is_character (unsigned char value) {
    if ((value >= 'a' && value <= 'z') ||
        (value == 'ç') ||
        (value >= 'à' && value <= 'ü')) {
        return 1;
    } 

    return 0;
}

int iterativeBsearch(dictionary *dict_pointer, unsigned char *str) {
   int start = 0;
   int end = dict_pointer-1;
   while(start<=end) {
      int mid = (start+end)/2;
      if( strcmp(dict_pointer->dict[mid], str)) {
         return mid;
      } else if(  ) {
         end = mid-1;
      } else {
         start = mid+1;
      }
   }
   return -1;
}

int main () {
    
    FILE *arq;
    dictionary pt_dict;

    start_dict(&pt_dict);
    open_file(&arq);
    load_dict(&arq, &pt_dict);


    unsigned char c;
    while ( (c = getchar()) != EOF ) {
        lower_case(&c);
        while ( ! is_character(c) && (c = getchar() != EOF )) {
            printf("%c", c);
            scanf("%c", &c);
        }

        char *str = "";
        while ( is_character(c) && ! (c = getchar() != EOF)) {
            str = str + c;
            c = getchar();
        } 

        if (str) {
            if () {
                printf("%s", str);
            } else {
                printf("[%s]", str);
            }            
        } 
    }

    return 1;
}
