//
// Created by Noy Zini on 16/04/2022.
// Edited by Avia Avraham on 18/04/2022
//

#include "AsciiArt.h"
#include <stdio.h>
#include <stdlib.h>



RLEList asciiArtRead(FILE* in_stream)
{
    RLEList file_RLE = RLEListCreate();
    //in_stream= fopen("in_stream","r");
    if(in_stream==NULL)
        return NULL;
    char letter=fgetc(in_stream);
    while(letter!=EOF)
    {
        if(RLEListAppend(file_RLE,letter)!=RLE_LIST_SUCCESS)
            return NULL;
        letter=fgetc(in_stream);
    }
    //fclose(in_stream);
    return file_RLE;
}

RLEListResult asciiArtPrint(RLEList list, FILE *out_stream)
{
    RLEListResult result;
    char *list_as_string = RLEListExportToString(list,&result);
    char *write = malloc(RLEListSize(list) * sizeof(char)); //free this
    char *ptr = write;
    char letterToWrite = 'A';
    int letterRepetitions = 0;

    if (result != RLE_LIST_SUCCESS)//test this!!! result might be initialized as NULL ?
        return result;


    while (*list_as_string)
    {
        char currentChar = list_as_string[0];

        if (currentChar >= '0' && currentChar <= '9')
        {
            letterRepetitions = letterRepetitions * 10;
            letterRepetitions += currentChar - '0';
        }
        else if (currentChar == '\n')
        {
            if (letterToWrite == currentChar)
                letterRepetitions--;
            for (int i = 0; i < letterRepetitions; i++)
            {
                *ptr = letterToWrite;
                ptr++;
            }
            letterToWrite = '\n';
            letterRepetitions = 0;
        }
        else
        {
            letterToWrite = currentChar;
        }
        list_as_string++;
    }
    fputs(write,out_stream);
    return RLE_LIST_SUCCESS;

}


RLEListResult asciiArtPrintEncoded(RLEList list,FILE* out_stream)
{
    //out_stream = fopen("out_stream","w");
    RLEListResult result;
    char *encoded_list= RLEListExportToString(list,&result);
    if(result==RLE_LIST_SUCCESS)
    {
        fprintf(out_stream, encoded_list);
        free(encoded_list);
        //fclose(out_stream);
        return RLE_LIST_SUCCESS;
    }
    //fclose(out_stream);
    return RLE_LIST_NULL_ARGUMENT;
}