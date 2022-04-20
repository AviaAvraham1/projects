#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#include "RLEList.h"
#include "AsciiArt.h"

/*
 * TO DO:
 * Fix asciiArtPrintEncoded()
 * on RLEListRemove() join 2 nodes together if middle one is gone
 * complete RLEList.c's to do list
 */
char InvertChar(char to_invert);

int main(int argc, char** argv)
{
    /*
    char *readPath = "../test1.txt", *writePath = "../writeHere.txt";
    FILE* fileReadFrom = fopen(readPath, "r");
    RLEList fileAsList = asciiArtRead(fileReadFrom);
    RLEListResult result;
    char *c = RLEListExportToString(fileAsList,&result);
    //printf("%s",c); //here works so far!

    FILE* fileWriteTo = fopen(writePath,"w");
    //FILE* out = stdout; //doesn't work for some reason
    //result = asciiArtPrint(fileAsList,fileWriteTo);
    result = asciiArtPrintEncoded(fileAsList,fileWriteTo);

    if (result == RLE_LIST_ERROR)
        printf("error");

    fclose(fileReadFrom);
    fclose(fileWriteTo);
     */
    //-------AsciiArtTool - code ---------------

    if(argc!=4) //needs a define
    {
        printf("Usage: ./AsciiArtTool <flags> <source> <target>");
        return 0;
    }
    else
    {

        FILE* source = fopen(argv[2],"r");
        if (!source)
        {
            printf("error");
            return 0;
        }
        FILE* dest = fopen(argv[3],"w");
        if (!dest)
        {
            printf("error");
            fclose(source);
            return 0;
        }

        RLEList image = asciiArtRead(source);

        if (strcmp(argv[1],"-e") == 0)
        {
            asciiArtPrintEncoded(image,dest);
            RLEListDestroy(image);
        }
        else if (strcmp(argv[1],"-i") == 0)
        {
            RLEListMap(image,InvertChar);
            asciiArtPrint(image,dest);
            RLEListDestroy(image);
        }
        else
        {
            printf("Unknown flag");
            return 0;
        }
        fclose(source);
        fclose(dest);
    }
    return 0;
}

char InvertChar(char to_invert)
{
    if (to_invert == ' ')
        return '@';
    if (to_invert == '@')
        return ' ';
    return to_invert;
}


