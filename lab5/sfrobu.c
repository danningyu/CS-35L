#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

/* Danning Yu, 305087992 */
/* Remember: space acts like a null byte */
/* Read in input, sort it, then print it */
// check for malloc(0)!

/* Function Declarations */
int frobcmp(const unsigned char *a, const unsigned char *b);
int compare(const void* a, const void* b);
void printAllStrings(unsigned char **arrOfStrings, int numberOfStrings);

/* For -f option */
int case_insensitive = 0;

/* Function Implementations */
int frobcmp(const unsigned char *a, const unsigned char *b){
    int alength;
    int blength;
    int alengthPreCompute;
    int blengthPreCompute;

    /* get the lengths of a and b */
    for(alengthPreCompute=0; a[alengthPreCompute] != ' '; alengthPreCompute++){}

    for(blengthPreCompute=0; b[blengthPreCompute] != ' '; blengthPreCompute++){}

    for(alength=0, blength = 0; a[alength] != ' ' && b[blength] != ' ';
        alength++, blength++){
        if(case_insensitive){
            if( (toupper( a[alength] ^ 42 ) ) < (toupper( b[blength] ^ 42 ) ) ){
                return -1;
            }
            if( (toupper(a[alength] ^ 42)) > (toupper(b[blength] ^ 42)) ){
                   return 1;
               }
        }
        else{
            if((a[alength] ^ 42) < (b[blength] ^ 42)){
                return -1;
            }
            if((a[alength] ^ 42) > (b[blength] ^ 42)){
                return 1;
            }
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
    return frobcmp(*(unsigned char**)(a), *(unsigned char**)(b));
}

void printAllStrings(unsigned char **arrOfStrings, int numOfStrings){
    int i;
    unsigned char charBuffer[1];
    unsigned char spaceCharBuffer[1] = {' '};
    /* const int alwaysTrue = 1; */
    for(i = 0; i<numOfStrings; i++){
        int j = 0;
        while(arrOfStrings[i][j] != ' '){
            charBuffer[0] = arrOfStrings[i][j];
           // if(putchar(arrOfStrings[i][j]) == EOF){
            if(write(STDOUT_FILENO, charBuffer, 1) < 0){
                fprintf(stderr, "Error occurred when printing characters\n");
                exit(1);
            }
            j++;
        }
        if(write(STDOUT_FILENO, spaceCharBuffer, 1) < 0){
            fprintf(stderr, "Error occurred when printing characters\n");
            exit(1);
        }
    }
}

/* Main */
int main(int argc, char *argv[]){
    /* Read in arguments */
    if(argc > 2){
        fprintf(stderr, "Incorrect number of arguments\n");
        exit(1);
    }

    if(argc == 2){
        if(strlen(argv[1]) != 2){
            fprintf(stderr, "Bad argument, only -f allowed\n");
            exit(1);
        }
        if(argv[1][0] == '-' && argv[1][1] == 'f'){
          //  printf("Case insensitive option\n");
            case_insensitive = 1;
        //how about if(argc == 2 && argv[1] != "-f")?
        }
        else {
            fprintf(stderr, "Bad argument, only -f allowed\n");
            exit(1);
        }
    }

    /* Read in text from stdin */
    struct stat inputFile;
    int fileSize = 0;
    unsigned char** allStrings = NULL;
    unsigned char* inputFileContents = NULL;
    int numWords = 0;
    int addedSpaceAtEnd = 0;
    int alwaysTrue = 1;
    unsigned char inBuffer[1];
    int wordIndex = 0;
    int startOfWord = 1;
    int lastWordSize = 0;
    int addNewString = 1;
    int newStringIndex = 0;
    unsigned char* newString = NULL;
    int zeroSizeInitialFile = 0;

    if(fstat(STDIN_FILENO, &inputFile) < 0){
        fprintf(stderr, "Error when reading in from stdin\n");
        exit(1);
    }

    // if(S_ISREG(inputFile.st_mode)){
    //     printf("regular file\n");
    // }
    // else if(S_ISFIFO(inputFile.st_mode)){
    //     printf("Piped in\n");
    // }
    if(inputFile.st_size == 0){
      //  printf("Nothing to sort.\n");
        zeroSizeInitialFile = 1;
    }

    if(S_ISREG(inputFile.st_mode) && inputFile.st_size != 0){
        fileSize = inputFile.st_size;
      //     printf("File size is %d\n", fileSize);
        inputFileContents = (unsigned char*)(
            malloc(fileSize*sizeof(unsigned char)));
        if(inputFileContents == NULL){
            fprintf(stderr, 
                "Error in allocating memory to hold input file\n");
            exit(1);
        }
        if(read(STDIN_FILENO, inputFileContents, fileSize) < 0){
            fprintf(stderr, "Error when reading in from file\n");
        }
        for(int i = 0; i<fileSize; i++){
            if(inputFileContents[i] == ' '){
                numWords++;
               // printf("Now %d words\n", numWords);
            }
        }
        if(inputFileContents[fileSize-1] != ' '){
           // printf("Adding trailing space\n");
            numWords++; //missing trailing space
            addedSpaceAtEnd = 1;
            fileSize = fileSize + 1;
            inputFileContents = (unsigned char*)(
                realloc(inputFileContents, fileSize*sizeof(unsigned char)));
            inputFileContents[fileSize-1] = ' ';
        }
        allStrings = (unsigned char**)(
            malloc(numWords*sizeof(unsigned char*)));
        if(allStrings == NULL){
            fprintf(stderr, 
                "Error in allocating memory to hold arr of strings\n");
            exit(1);
        }

       // printf("File size is %d\n", fileSize);
        for(int i = 0; i<fileSize; i++){
            // printf("Analyzing :%c:\n", inputFileContents[i]);
            if(startOfWord){
                allStrings[wordIndex] = &inputFileContents[i];
                wordIndex++;
                startOfWord = 0;
                lastWordSize = 1;
                // printf("Start of word at %d\n", i);
            }
            if(inputFileContents[i] == ' '){
                startOfWord = 1;
                //word ended, so next iteration, store start of word
            }
            else {
                lastWordSize++;
            }
            // printf("Last word size: %d\n", lastWordSize);
        }
    }
    else if(S_ISFIFO(inputFile.st_mode)){
        // printf("Stdin is not a regular file\n");
        allStrings = (unsigned char**)(malloc(sizeof(unsigned char*)));
        if(allStrings == NULL){
            fprintf(stderr, 
                "Error in allocating memory to hold arr of strings\n");
            exit(1);
        }
        while(alwaysTrue){
            ssize_t readResult = read(STDIN_FILENO, inBuffer, 1);
            if(readResult < 0){
                fprintf(stderr, "Error when reading from stdin\n");
                exit(1);
            }
            if(readResult == 0){ //reached end of file
                break;
            }
            if(addNewString){
                /* start of new string */
                numWords++;
                /* expand allStrings to hold another ptr */
                allStrings = (unsigned char**)(
                    realloc(allStrings, (numWords)*sizeof(unsigned char*)));
                if(allStrings == NULL){
                    fprintf(stderr, 
                        "Error in allocating memory to hold arr of strings\n");
                    exit(1);
                }

                /* make new ptr for strings, allocate size for 1 char */
                newString = (unsigned char*)(malloc(sizeof(unsigned char)));
                if(newString == NULL){
                    fprintf(stderr, 
                        "Error in allocating memory to hold arr of strings\n");
                    exit(1);
                }
                newString[newStringIndex] = inBuffer[0];
                allStrings[numWords-1] = newString;
                addNewString = 0;
                newStringIndex++;
               // printf("1Inserting :%c:\n", inBuffer[0]);
                if(inBuffer[0] == ' '){
                    /* space acts as "null byte" */
                    addNewString = 1;
                    newStringIndex = 0;
                    newString = NULL;
                    continue;
                }
            }
            else if (!addNewString){
                newString = (unsigned char*)(
                    realloc(newString, (newStringIndex+1)*sizeof(unsigned char)));
                if(newString == NULL){
                    fprintf(stderr, 
                        "Error in allocating memory to hold arr of strings\n");
                    exit(1);
                }
                newString[newStringIndex] = inBuffer[0];
                allStrings[numWords-1] = newString;
               // printf("2Inserting :%c:\n", inBuffer[0]);
                newStringIndex++;
                if(inBuffer[0] == ' '){
                    /* space acts as "null byte" */
                    addNewString = 1;
                    newStringIndex = 0;
                    newString = NULL;
                }
            }
            // printf("Read in :%c:\n", inBuffer[0]);
        }
        if(numWords != 0 && newStringIndex != 0
            && allStrings[numWords-1][newStringIndex-1] != ' '){
        /* last char is not space */
        newString = (unsigned char*)(
            realloc(newString, (newStringIndex+1)*sizeof(unsigned char)));
        if(newString == NULL){
            fprintf(stderr, 
                "Error in allocating memory to hold arr of strings\n");
            exit(1);
        }
        newString[newStringIndex] = ' ';
        allStrings[numWords-1] = newString;
        }
    }
    lastWordSize = lastWordSize - addedSpaceAtEnd;
   //  printf("REV last word size: %d\n", lastWordSize);

    /* Read in any bytes that have been appended to file */
    unsigned char* additionalContent=NULL;
    int additionalSize = 0;
    int addedSpaceAtEnd2 = 0;
    int trueFileSize = fileSize - addedSpaceAtEnd;
    //if empty file, then fileSize = addedSpaceAtEnd = 0
    unsigned char tempBuffer[1];
    int additionalSizeNEW = 0;

    while(alwaysTrue){
        ssize_t readResult = read(STDIN_FILENO, tempBuffer, 1);
        // printf("readResult: %d\n", readResult);
        if(readResult < 0){
            fprintf(stderr, "Error in reading in data from file\n");
            exit(1);
        }
        if(readResult == 0){
            break;
        }
        additionalSizeNEW++;
    }

    lseek(STDIN_FILENO, trueFileSize - lastWordSize, SEEK_SET);
    //move file pointer to start of last word in old file

    if(additionalSizeNEW > 0){ //file size has increased
        
        additionalSize = additionalSizeNEW + lastWordSize; 
        //subtract old filesize
        if(!zeroSizeInitialFile){
            numWords--; //roll back 1 word
            wordIndex--;
        }
        
        fileSize = inputFile.st_size; //then update filesize
        // printf("FILE GREW, size is now %ld, increase of %d\n", inputFile.st_size, (int)additionalSize - lastWordSize);
        additionalContent = (unsigned char*)(
            malloc(additionalSize*sizeof(unsigned char)));
        // inputFileContents = (char*)(realloc(inputFileContents, fileSize*sizeof(unsigned char)));
        // this line causes issues because reallocating invalidates all the old ptrs
        if(additionalContent == NULL){
            fprintf(stderr, 
                "Error in allocating memory to hold input file\n");
            exit(1);
        }
        if(read(STDIN_FILENO, additionalContent, additionalSize) < 0){ 
        //read in additional bytes
            fprintf(stderr, "Error when reading in from file\n");
        }
         //  printf("Additional size is %d\n", additionalSize);
        for(int i = 0; i<additionalSize; i++){
            // printf("ADD: 2Analyzing :%c:\n", additionalContent[i]);
            if(additionalContent[i] == ' '){
                numWords++;
              //   printf("ADD: Now %d words\n", numWords);
            }
        }
        if(additionalContent[additionalSize-1] != ' '){
          //   printf("ADD: Adding trailing space\n");
            numWords++; //missing trailing space
            addedSpaceAtEnd2 = 1;
            additionalSize = additionalSize + 1;
            additionalContent = (unsigned char*)(
                realloc(additionalContent, additionalSize*sizeof(char)));
            additionalContent[additionalSize-1] = ' ';
        }

        if(allStrings != NULL){
            allStrings = (unsigned char**)(
                realloc(allStrings, numWords*sizeof(unsigned char*)));
        }
        else{
            allStrings = (unsigned char**)(
                malloc(numWords*sizeof(unsigned char*)));
        }

        if(allStrings == NULL){
            fprintf(stderr, 
                "Error in allocating memory to hold arr of strings\n");
            exit(1);
        }
        // printf("ADD: File size is now %d\n", fileSize);
        for(int i = 0; i<additionalSize; i++){
           //  printf("ADD: Analyzing :%c:\n", additionalContent[i]);
            if(startOfWord){
                allStrings[wordIndex] = &additionalContent[i];
                wordIndex++;
                startOfWord = 0;
              //   printf("ADD: Start of word at %d\n", i);
            }
            if(additionalContent[i] == ' '){
                startOfWord = 1; //word ended, so next iteration, store start of word
            }
        }
        if(addedSpaceAtEnd2){
            // printf("2Added space at end\n");
        }
    }
   //  printf("FINAL num of words: %d\n", numWords);
    if(allStrings != NULL){
        qsort(allStrings, numWords, sizeof(unsigned char*), compare);
        printAllStrings(allStrings, numWords);
    }
    
    /* clean up allocated memory */
    if(S_ISFIFO(inputFile.st_mode)){
        for(int i = 0; i<numWords; i++){
            free(allStrings[i]);
        }
    }

    free(allStrings);
    free(inputFileContents);
    free(additionalContent);
    exit(0);
}
