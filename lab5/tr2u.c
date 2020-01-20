#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* Danning Yu */
/* 305087992 */
/* Using write and read */

int main(int argc, char *argv[]){
    if(argc != 3){
        write(STDERR_FILENO, "Error: incorrect number of arguments\n", 37);
        exit(1);
    }

    if(strlen(argv[1]) != strlen(argv[2])){
        write(STDERR_FILENO, "Error: sets 1 and 2 must be the same length\n", 44);
        exit(1);
    }

    char* fromChars = argv[1];
    char* toChars = argv[2];

    char convertTable[256] = {'\0'};
    /* to hold all 7 bit ASCII characters */
    size_t i;
    for(i = 0; i<strlen(fromChars); i++){
        if(convertTable[(unsigned char)fromChars[i]] == '\0'){
            convertTable[(unsigned char)fromChars[i]] = toChars[i];
        }
        else if(convertTable[(unsigned char)fromChars[i]] != '\0'){
            write(STDERR_FILENO, "Duplicate element(s) in from set\n", 33);
            exit(1);
        }
    }

    unsigned char charBuffer[1];
    unsigned char outputBuffer[1];

    while(read(STDIN_FILENO, charBuffer, 1) > 0){
        // if(convertTable[(unsigned char)charBuffer[0]] != '\0'){
        //     outputBuffer[0] = convertTable[(unsigned char)charBuffer[0]];
        if(convertTable[charBuffer[0]] != '\0'){
            outputBuffer[0] = convertTable[charBuffer[0]];
            if(write(STDOUT_FILENO, outputBuffer, 1) < 0){
                write(STDERR_FILENO, "Error when writing characters\n", 30);
                exit(1);
            }
        }

        else{
            if(write(STDOUT_FILENO, charBuffer, 1) < 0){
                write(STDERR_FILENO, "Error when writing characters\n", 30);
                exit(1);
            }
        }
    }
    exit(0);
}
