#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>

/* TODO: replace all // style commments */


int frobcmp(char const *a, char const *b);
int compare(const void* a, const void* b);

int frobcmp(char const *a, char const *b){
    int alength;
    int blength;
    for(alength=0, blength = 0; 
        a[alength] != ' ' && b[blength] != ' ';
        alength++, blength++){
        if((a[alength] ^ 42) < (b[blength] ^ 42)){
            printf("Case 1\n");
            return -1;
        }
        if((a[alength] ^ 42) > (b[blength] ^ 42)){
            printf("Case 2\n");
            return 1;
        }

    }
    /* if exited for-loop, then equal up to certain point */
    if(alength < blength){
        printf("Case 3\n");
        return -1;
    }
    else if(alength > blength){
        printf("Case 4\n");
        return 1;
    }
    /* at this point, alength == blength */
    printf("Case 5\n");
    return 0;
}

int compare(const void* a, const void* b){
    return frobcmp((char*)(a), (char*)(b));
}

int main(){

    char** allStrings = (char**)(malloc(sizeof(char**)));

    char str1[] = "\030\031";
    char str2[] = "*`_GZY";
    int result = compare(str1, str2);
    int result2 = frobcmp(str1, str2);
    assert(result == result2);
    printf("Result of comparison: %d\n", result);
    memfrob(str1, 2);
    // memfrob(str1, 4);
    memfrob(str2, 7);
    printf("str1 frob: %s\n", str1);
    printf("str2 frob: %s\n", str2);
    printf("Result of right comparison: %d\n", memcmp(str1, str2, 2));

    // sort: 
   //  free(allStrings);
    return 0;
}