#include <stdio.h>
#include <stdlib.h>

//#include "RLEList.h"
#include "AsciiArt.h"

/*
 * TO DO:
 * Fix asciiArtPrintEncoded()
 * on RLEListRemove() join 2 nodes together if middle one is gone
 * complete RLEList.c's to do list
 */

int main(int argc, char** argv)
{
    char *readPath = "../test2.txt", *writePath = "../writeHere.txt";
    FILE* fileReadFrom = fopen(readPath, "r");
    RLEList fileAsList = asciiArtRead(fileReadFrom);
    RLEListResult result;
    char *c = RLEListExportToString(fileAsList,&result);
    //printf("%s",c); //here works so far!

    FILE* fileWriteTo = fopen(writePath,"w");
    //FILE* out = stdout; //doesn't work for some reason
    result = asciiArtPrint(fileAsList,fileWriteTo);

    if (result == RLE_LIST_ERROR)
        printf("error");

    fclose(fileReadFrom);
    fclose(fileWriteTo);

    //-------AsciiArtTool - code ---------------
    if(argc!=4) //needs a define
    {
        printf("Error in input, not enough arguments");
        return 0;
    }



    return 0;
}


