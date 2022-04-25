#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#include "RLEList.h"
#include "AsciiArtTool.h"

/*
 * TO DO:
 * Fix asciiArtPrintEncoded()
 * on RLEListRemove() join 2 nodes together if middle one is gone
 * complete RLEList.c's to do list
 */
char InvertChar(char to_invert);

int main(int argc, char** argv)
{
    if(argc!=4) //needs a define
    {
        printf("Usage: ./AsciiArtTool <flags> <source> <target>\n");
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
        }
        else if (strcmp(argv[1],"-i") == 0)
        {
            RLEListResult result=RLE_LIST_SUCCESS;
            result=RLEListMap(image,&InvertChar);
            if(result!=RLE_LIST_SUCCESS)
            {
                printf("error map");
                RLEListDestroy(image);
                fclose(source);
                fclose(dest);
                return 0;
            }
            asciiArtPrint(image,dest);
        }
        else
        {
            printf("Unknown flag");
        }

        RLEListDestroy(image);
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


