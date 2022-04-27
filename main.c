#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "RLEList.h"
#include "AsciiArtTool.h"

#define INVERT_FLAG "-i"
#define ENCODED_FLAG "-e"
#define TO_INVERT_1 ' '
#define TO_INVERT_2 '@'
#define REQUIRED_ARGUMENTS 4
#define FLAG 1
#define SOURCE 2
#define TARGET 3

char InvertChar(char toInvert);

int main(int argc, char** argv)
{
    if(argc!=REQUIRED_ARGUMENTS)
    {
        printf("Usage: ./AsciiArtTool <flag> <source> <target>\n");
        return 0;
    }
    else
    {
        FILE* source = fopen(argv[SOURCE],"r");
        if (!source)
        {
            printf("error: can't open source file\n");
            return 0;
        }
        FILE* dest = fopen(argv[TARGET],"w");
        if (!dest)
        {
            printf("error: can't open target file\n");
            fclose(source);
            return 0;
        }

        RLEList image = asciiArtRead(source);
        if(RLEListSize(image)==0)
        {
            RLEListDestroy(image);
            fclose(source);
            fclose(dest);
            return 0;
        }

        if (strcmp(argv[FLAG],ENCODED_FLAG) == 0)
        {
            asciiArtPrintEncoded(image,dest);
        }
        else if (strcmp(argv[FLAG],INVERT_FLAG) == 0)
        {
            RLEListResult result=RLE_LIST_SUCCESS;
            result=RLEListMap(image,&InvertChar);
            if(result!=RLE_LIST_SUCCESS)
            {
                printf("error: map function failed during process\n");
                RLEListDestroy(image);
                fclose(source);
                fclose(dest);
                return 0;
            }
            asciiArtPrint(image,dest);
        }
        else
        {
            printf("error: Unknown flag\n");
        }
        RLEListDestroy(image);
        fclose(source);
        fclose(dest);
    }
    return 0;
}

char InvertChar(char toInvert)
{
    if (toInvert == TO_INVERT_1)
    {
        return TO_INVERT_2;
    }
    if (toInvert == TO_INVERT_2)
    {
        return TO_INVERT_1;
    }
    return toInvert;
}
