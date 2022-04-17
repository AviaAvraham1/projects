//
// Created by Noy Zini on 16/04/2022.
//

#include "AsciiArt.h"
#include <stdio.h>

#define LINE_SIZE 256

RLEList asciiArtRead(FILE* in_stream)
{
    RLEList file_RLE = RLEListCreate();
    in_stream= fopen("in_stream","r");
    if(in_stream==NULL)
        return NULL;

    int repetitions=0;
    while (1)
    {
        char letter=fgetc(in_stream);
        if(letter==EOF)
        {
            RLEListAppend(file_RLE,letter);

            break;
        }


    }


    fclose(in_stream);
    return file_RLE;
}