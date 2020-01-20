#include <stdio.h>
#include <stdlib.h>

/* Danning Yu, 305087992 */
/* Remember: space acts like a null byte */
/* Read in input, sort it, then print it */

/* Function Declarations */
int frobcmp(char const *a, char const *b);
int compare(const void* a, const void* b);
void printAllStrings(char **arrOfStrings, int numberOfStrings);

/* Function Implementations */
int frobcmp(char const *a, char const *b){
    int alength;
    int blength;
    int alengthPreCompute;
    int blengthPreCompute;

    /* get the lengths of a and b */
	for(alengthPreCompute=0; a[alengthPreCompute] != ' '; alengthPreCompute++){}

    for(blengthPreCompute=0; b[blengthPreCompute] != ' '; blengthPreCompute++){}

    /* printf("comparing :%s: and :%s:\n", a, b); */

    for(alength=0, blength = 0; 
        a[alength] != ' ' && b[blength] != ' ';
        alength++, blength++){
        if((a[alength] ^ 42) < (b[blength] ^ 42)){
            return -1;
        }
        if((a[alength] ^ 42) > (b[blength] ^ 42)){
            return 1;
        }
    }
    /* if exited for-loop, then equal up to certain point */
    if(alengthPreCompute < blengthPreCompute){
        return -1;
    }
    else if(alengthPreCompute > blengthPreCompute){
        return 1;
    }
    /* at this point, alength == blength */
    return 0;
}

int compare(const void* a, const void* b){
    return frobcmp(*(char**)(a), *(char**)(b));
}

void printAllStrings(char **arrOfStrings, int numOfStrings){
    int i;
    /* const int alwaysTrue = 1; */
    for(i = 0; i<=numOfStrings; i++){
        int j = 0;
        while(arrOfStrings[i][j] != ' '){
            if(putchar(arrOfStrings[i][j]) == EOF){
                fprintf(stderr, "Error occurred when printing characters\n");
                exit(1);
            }
            j++;
        }
        if(putchar(' ') == EOF){
            fprintf(stderr, "Error occurred when printing characters\n");
            exit(1);
        }
    }
}

/* Main */
int main(){
    int ch = 0;
    int allStringsIndex = -1;
    int addNewString = 1;
    /* 1 for true, 0 for false */
    int newStringIndex = 0;
    char* newString = NULL;
    int i;

    char** allStrings = (char**)(malloc(sizeof(char*)));
    if(allStrings == NULL){
        fprintf(stderr, "Error in allocating memory to hold arr of strings\n");
        exit(1);
    }

    /* read in strings */
    while((ch = getchar())){
        if(ferror(stdin)){
            fprintf(stderr, "Error when reading file, EXITING\n");
            exit(1);
        }
        if(feof(stdin)){
            break;  
         }
        if(addNewString && ch != EOF){
            if(feof(stdin)){
                break;
            }
            /* printf("1Adding :%c:\n", ch); */
            
            /* start of new string */
            allStringsIndex++;
            /* expand allStrings to hold another ptr */
            allStrings = (char**)(realloc(allStrings, (allStringsIndex+1)*sizeof(char*)));
            if(allStrings == NULL){
                fprintf(stderr, "Error in allocating memory to hold arr of strings\n");
                exit(1);
            }

            /* make new ptr for strings, allocate size for 1 char */
            newString = (char*)(malloc(sizeof(char)));
            if(newString == NULL){
                fprintf(stderr, "Error in allocating memory to hold arr of strings\n");
                exit(1);
            }
            newString[newStringIndex] = ch;
            allStrings[allStringsIndex] = newString;
            addNewString = 0;
            newStringIndex++;

            if(ch == ' '){
                /* space acts as "null byte" */
                addNewString = 1;
                newStringIndex = 0;
                newString = NULL;
                continue;
            }
        }
        else if (!addNewString){
            /* printf("2Adding :%c:\n", ch); */
            newString = (char*)(realloc(newString, (newStringIndex+1)*sizeof(char)));
            if(newString == NULL){
                fprintf(stderr, "Error in allocating memory to hold arr of strings\n");
                exit(1);
            }
            newString[newStringIndex] = ch;
            allStrings[allStringsIndex] = newString;
            newStringIndex++;
            if(ch == ' '){
                /* space acts as "null byte" */
                addNewString = 1;
                newStringIndex = 0;
                newString = NULL;
            }
        }
    }

    if(allStringsIndex != -1 && newStringIndex != 0
        && allStrings[allStringsIndex][newStringIndex-1] != ' '){
        /* last char is not space */
        newString = (char*)(realloc(newString, (newStringIndex+1)*sizeof(char)));
        if(newString == NULL){
            fprintf(stderr, "Error in allocating memory to hold arr of strings\n");
            exit(1);
        }
        newString[newStringIndex] = ' ';
        allStrings[allStringsIndex] = newString;
    }

    qsort(allStrings, allStringsIndex+1, sizeof(char*), compare);
    printAllStrings(allStrings, allStringsIndex);

    /* clean up allocated memory */
    for(i = 0; i<=allStringsIndex; i++){
        free(allStrings[i]);
    }
    free(allStrings);
    exit(0);
}
