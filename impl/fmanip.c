#include"../lib/fmanip.h"

FILE *openFile(const char *fileName, const char *mode){

    FILE *filePtr;

    filePtr = fopen(fileName, mode);

    if (filePtr == NULL)
    {
        printf("An error occurred while opening the file %s!", fileName);
        exit(1);
    }

    return filePtr;
}