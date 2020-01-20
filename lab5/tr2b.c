#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/* Danning Yu */
/* 305087992 */
/* Using getchar and putchar */

int main(int argc, char *argv[]){
    if(argc != 3){
        fprintf(stderr, "Error: incorrect number of arguments\n");
        exit(1);
    }

    if(strlen(argv[1]) != strlen(argv[2])){
        fprintf(stderr, "Error: sets 1 and 2 must be the same length\n");
        exit(1);
    }

    char* fromChars = argv[1];
    char* toChars = argv[2];

    unsigned char convertTable[256] = {'\0'};
    /* to hold all 7 bit ASCII characters */
    size_t i;
    for(i = 0; i<strlen(fromChars); i++){
        if(convertTable[(unsigned char)fromChars[i]] == '\0'){
            convertTable[(unsigned char)fromChars[i]] = toChars[i];
        }
        else if(convertTable[(unsigned char)fromChars[i]] != '\0'){
            fprintf(stderr, "Duplicate element(s) in from set\n");
            exit(1);
        }
    }
   // int alwaysTrue = 1;
    int c;
    while((c = getchar()) != EOF){
        ;
        if(feof(stdin)){
            break;
        }

        if(ferror(stdin)){
            fprintf(stderr, "Error occurred when reading from stdin\n");
        }

        if(convertTable[c] != '\0'){
            putchar(convertTable[c]);
            if(ferror(stdout)){
                fprintf(stderr, "Error when printing characters\n");
                exit(1);
            }
        }
        else{
            putchar(c);
            if(ferror(stdout)){
                fprintf(stderr, "Error when printing characters\n");
                exit(1);
            }
        }

    }
    exit(0);
}
