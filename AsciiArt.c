//
// Created by Noy Zini on 16/04/2022.
//

#include "AsciiArt.h"
#include <stdio.h>
#include "RLEList.h"
#include <stdlib.h>



RLEList asciiArtRead(FILE* in_stream)
{
    RLEList file_RLE = RLEListCreate();
    in_stream= fopen("in_stream","r");
    if(in_stream==NULL)
        return NULL;
    char letter=fgetc(in_stream);
    while(letter!=EOF)
    {
        if(RLEListAppend(file_RLE,letter)!=RLE_LIST_SUCCESS)
            return NULL;
        letter=fgetc(in_stream);
    }
    fclose(in_stream);
    return file_RLE;
}



RLEListResult asciiArtPrintEncoded(RLEList list,FILE* out_stream)
{

    out_stream = fopen("out_stream","w");
    RLEListResult result;
    char *encoded_list= RLEListExportToString(list,result);
    if(result==RLE_LIST_SUCCESS)
    {
        fprintf(out_stream, encoded_list);
        free(encoded_list);
        fclose(out_stream);
        return RLE_LIST_SUCCESS;
    }
    fclose(out_stream);
    return RLE_LIST_NULL_ARGUMENT;
}