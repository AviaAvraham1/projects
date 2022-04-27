#include "AsciiArtTool.h"
#include <stdio.h>
#include <stdlib.h>

#define EMPTY_CHAR '\0'
#define NEW_LINE '\n'
#define CHAR_CONVERT_INT '0'
#define FACTOR 10
#define BUFFER 256

RLEList asciiArtRead(FILE* in_stream)
{
    /*
    RLEList fileRLE = RLEListCreate();
    if(in_stream==NULL)
    {
        return NULL;
    }
    char letter=fgetc(in_stream);
    while(letter!=EOF)
    {
        if(RLEListAppend(fileRLE, letter) != RLE_LIST_SUCCESS)
        {
            return NULL;
        }
        letter=fgetc(in_stream);
    }
    return fileRLE;
    */
    RLEList fileRLE = RLEListCreate();
    if(in_stream==NULL)
    {
        return NULL;
    }
    char buffer[BUFFER];
    for(int j=0;j<BUFFER;j++)
    {
        buffer[j]=EMPTY_CHAR;
    }
    while (fgets(buffer,BUFFER,in_stream)!=NULL)
    {
        for (int i=0;i<BUFFER&&buffer[i]!=EMPTY_CHAR;i++)
        {
            if(RLEListAppend(fileRLE,buffer[i])!=RLE_LIST_SUCCESS)
                return NULL;

        }
        for(int j=0;j<BUFFER;j++)
        {
            buffer[j]=EMPTY_CHAR;
        }
    }
    return fileRLE;
}

RLEListResult asciiArtPrint(RLEList list, FILE *out_stream)
{
    RLEListResult result=RLE_LIST_SUCCESS;
    char *listAsString = RLEListExportToString(list, &result);
    char *listAsStringHead = listAsString;

    if(listAsString == NULL)
    {
        return RLE_LIST_OUT_OF_MEMORY;
    }
    if (result != RLE_LIST_SUCCESS)
    {
        free(listAsString);
        return result;
    }

    char *toBePrinted = malloc((1 + RLEListSize(list)) * sizeof(char));
    if(toBePrinted == NULL)
    {
        free(listAsString);
        return RLE_LIST_OUT_OF_MEMORY;
    }
    for(int i=0;i<1+RLEListSize(list);i++)
    {
        toBePrinted[i]=EMPTY_CHAR;
    }

    char *ptr = toBePrinted;

    while (*listAsString)
    {
        char letterToPrint = *listAsString;
        listAsString++;
        int letterRepetitions = 0;
        while (*listAsString != NEW_LINE)
        {
            letterRepetitions = letterRepetitions * FACTOR;
            letterRepetitions += *listAsString - CHAR_CONVERT_INT;
            listAsString++;
        }
        for (int i = 0; i < letterRepetitions; i++)
        {
            *ptr = letterToPrint;
            ptr++;
        }
        listAsString++;
    }

    fputs(toBePrinted, out_stream);
    free(toBePrinted);
    free(listAsStringHead);
    return RLE_LIST_SUCCESS;
}


RLEListResult asciiArtPrintEncoded(RLEList list,FILE* out_stream)
{
    if(list==NULL || out_stream==NULL)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }

    RLEListResult result=RLE_LIST_SUCCESS;
    char *encodedList= RLEListExportToString(list, &result);

    if(encodedList == NULL)
    {
        return RLE_LIST_OUT_OF_MEMORY;
    }
    if (result != RLE_LIST_SUCCESS)
    {
        free(encodedList);
        return result;
    }
    fputs(encodedList, out_stream);
    free(encodedList);
    return RLE_LIST_SUCCESS;
}