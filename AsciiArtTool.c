//
// Created by Noy Zini on 16/04/2022.
// Edited by Avia Avraham on 18/04/2022
//

#include "AsciiArtTool.h"
#include <stdio.h>
#include <stdlib.h>


RLEList asciiArtRead(FILE* in_stream)
{
    RLEList file_RLE = RLEListCreate();
    if(in_stream==NULL)
        return NULL;
    char letter=fgetc(in_stream);
    while(letter!=EOF)
    {
        if(RLEListAppend(file_RLE,letter)!=RLE_LIST_SUCCESS)
            return NULL;
        letter=fgetc(in_stream);
    }
    return file_RLE;
}

RLEListResult asciiArtPrint(RLEList list, FILE *out_stream)
{
    RLEListResult result;
    char *list_as_string = RLEListExportToString(list,&result);
    char *list_as_string_head = list_as_string;


    if(list_as_string==NULL)
        return RLE_LIST_OUT_OF_MEMORY;
    if (result != RLE_LIST_SUCCESS)//test this!!! result might be initialized as NULL ?
    {
        free(list_as_string);
        return result;
    }
    char *write = malloc((1+RLEListSize(list)) * sizeof(char));//need better name & find needed size with \n's

    if(write == NULL)
    {
        free(list_as_string);
        return RLE_LIST_OUT_OF_MEMORY;
    }
/*
    if (RLEListSize(list) == 0)
    {
        *write = '\0';
        fputs(write,out_stream);
        free(list_as_string);
        free(write);
        return RLE_LIST_SUCCESS;
    }
    */

    for(int i=0;i<1+RLEListSize(list);i++)
    {
        write[i]='\0';
    }
    char *ptr = write;

    while (*list_as_string)
    {
        char toPrint = *list_as_string;
        list_as_string++;
        int letterRepetitions = 0;
        while (*list_as_string != '\n')
        {
            letterRepetitions = letterRepetitions * 10;
            letterRepetitions += *list_as_string - '0';
            list_as_string++;
        }

        for (int i = 0; i < letterRepetitions; i++)
        {
            *ptr = toPrint;
            ptr++;
        }

        list_as_string++;

    }

    fputs(write,out_stream);
    free(write);
    free(list_as_string_head);
    return RLE_LIST_SUCCESS;
}


RLEListResult asciiArtPrintEncoded(RLEList list,FILE* out_stream)
{
    if(list==NULL || out_stream==NULL)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }

    RLEListResult result=RLE_LIST_SUCCESS;
    char *encoded_list= RLEListExportToString(list,&result);

    if(encoded_list==NULL)
    {
        return RLE_LIST_OUT_OF_MEMORY;
    }
    if (result != RLE_LIST_SUCCESS)
    {
        free(encoded_list);
        return result;
    }
    //fprintf(out_stream,"%s" ,encoded_list);
    fputs(encoded_list,out_stream);
    free(encoded_list);
    return RLE_LIST_SUCCESS;
}