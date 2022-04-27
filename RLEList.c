#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "RLEList.h"

#define EMPTY_CHAR '\0'
#define EMPTY_NODE -1
#define NEGATIVE_NUMBER -1
#define NEXT_DIGIT 10
#define EMPTY_LIST 0
#define CHAR_AND_NEW_LINE 2
#define CHAR_CONVERT_INT '0'

static int NumOfDigits(int num);
static int CharCount(RLEList list);
static void PutIntInString(int num, char **writeTo);
static char getDigit(int num, int requiredDigit);
/*
 * TO DO:
 */

 struct RLEList_t{
    char letter;
    int repetitions;
    struct RLEList_t* next;
};


RLEList RLEListCreate()
{
    RLEList ptr= malloc(sizeof(*ptr));
    if(!ptr)
    {
        return NULL;
    }
    ptr ->letter=EMPTY_CHAR;
    ptr ->repetitions=0;
    ptr ->next =NULL;
    return ptr;
}

void RLEListDestroy(RLEList list)
{
    while(list) {
        RLEList toDelete = list;
        list = list->next;
        free(toDelete);
    }
}

int RLEListSize(RLEList list)
{
    if(list==NULL)
    {
        return EMPTY_NODE;
    }
    int count=0;
    while (list)
    {
        count+=list->repetitions;
        list = list->next;
    }
    return count;
}

char RLEListGet(RLEList list, int index, RLEListResult *result)
{
    if(list==NULL)
    {
        if(result!=NULL)
            *result= RLE_LIST_NULL_ARGUMENT;
        return EMPTY_CHAR;
    }
    if(RLEListSize(list)-1<index || index<0)
    {
        if(result!=NULL)
            *result= RLE_LIST_INDEX_OUT_OF_BOUNDS;
        return EMPTY_CHAR;
    }
    int count=0;
    char letter=list->letter;
    while (list)
    {
        count+=list->repetitions;
        if(index+1<=count)
        {
            if(result!=NULL)
                *result= RLE_LIST_SUCCESS;
            letter=list->letter;
            break;
        }
        list = list->next;
    }
    return letter;
}

char* RLEListExportToString(RLEList list, RLEListResult* result)
{
    if(list==NULL)
    {
        if (result != NULL)
            *result= RLE_LIST_NULL_ARGUMENT;
        return NULL;
    }



    char *list_as_string=malloc((1+CharCount(list)) * sizeof(char));

    if (!list_as_string)
    {
        if (result != NULL)
            *result= RLE_LIST_OUT_OF_MEMORY;
        return NULL;
    }


    for(int i=0;i<1+CharCount(list);i++)
    {
        list_as_string[i]=EMPTY_CHAR;
    }

    if (CharCount(list) == 0)
    {
        *list_as_string = '\0';
        if (result != NULL)
            *result= RLE_LIST_SUCCESS;
        return list_as_string;
    }
    char *stringStart = list_as_string;
    while (list)
    {
        *list_as_string=list->letter;
        list_as_string++;

        PutIntInString(list->repetitions,&list_as_string);

        *list_as_string='\n';
        list_as_string++;
        list = list->next;
    }
    if (result != NULL)
        *result= RLE_LIST_SUCCESS;
    return stringStart;
}


RLEListResult RLEListAppend(RLEList list, char value)
{
    if (list == NULL)
        return RLE_LIST_NULL_ARGUMENT;

    while (list->next != NULL)
        list = list->next;

    if (list->letter == value)
    {
        list->repetitions++;
        return RLE_LIST_SUCCESS;
    }
    else if (list->repetitions == 0)
    {
        list->letter = value;
        list->repetitions++;
        return RLE_LIST_SUCCESS;
    }
    else
    {
        assert(list->letter != value && list->repetitions != 0 && list->next == NULL);
        RLEList newNode = RLEListCreate();
        if (newNode == NULL)
            return RLE_LIST_OUT_OF_MEMORY;

        newNode->letter = value;
        newNode->repetitions = 1;
        list->next=newNode;
        return RLE_LIST_SUCCESS;
    }
}

RLEListResult RLEListRemove(RLEList list, int index)
{
    if (list == NULL)
        return RLE_LIST_NULL_ARGUMENT;

    if(RLEListSize(list)-1<index || index<0)
    {
        return RLE_LIST_INDEX_OUT_OF_BOUNDS;
    }

    if(list->repetitions==1 && index==0)
    {
        if(list->next == NULL)
        {
            list->letter=EMPTY_CHAR;
            list->repetitions=0;
            return RLE_LIST_SUCCESS;
        }
        RLEList to_delete=list->next;
        list->letter=to_delete->letter;
        list->repetitions=to_delete->repetitions;
        list->next=to_delete->next;
        to_delete->next=NULL;
        RLEListDestroy(to_delete);
        return RLE_LIST_SUCCESS;
    }

    RLEList previousOne = list;

    while (list && index > list->repetitions-1)
    {
        if (list->next == NULL)
            return RLE_LIST_INDEX_OUT_OF_BOUNDS;
        index-=list->repetitions;
        previousOne = list;
        list = list->next;
    }

    assert(list != NULL && index < list->repetitions);


    list->repetitions--;
    if (list->repetitions == 0)
    {
        previousOne->next = list->next;
        RLEList next_one=list->next;
        list->next = NULL;
        RLEListDestroy(list);
        if(next_one != NULL && next_one->letter==previousOne->letter)
        {
            previousOne->repetitions+=next_one->repetitions;
            previousOne->next=next_one->next;
            next_one->next=NULL;
            RLEListDestroy(next_one);
        }
    }
    return RLE_LIST_SUCCESS;
}

RLEListResult RLEListMap(RLEList list, MapFunction map_function)
{
    if (list == NULL || map_function == NULL)
        return RLE_LIST_NULL_ARGUMENT;
    RLEList head = list;
    while (list != NULL)
    {
        list->letter = map_function(list->letter);
        list = list->next;
    }
    list = head;
    while (list && list->next)
    {
        while (list->next != NULL && list->letter == list->next->letter)
        {
            RLEList uniteWith = list->next;
            list->repetitions += uniteWith->repetitions;
            list->next = uniteWith->next;
            uniteWith->next = NULL;
            RLEListDestroy(uniteWith);
        }
        list = list->next;
    }

    return RLE_LIST_SUCCESS;
}

static int CharCount(RLEList list)
{
    if (list->letter == EMPTY_CHAR)
    {
        return EMPTY_LIST;
    }
    int count = 0;
    while (list != NULL)
    {
        count+=CHAR_AND_NEW_LINE;
        count += NumOfDigits(list->repetitions);
        list = list->next;
    }
    return count;
}

static int NumOfDigits(int num)
{
    if (num < 0)
        return NEGATIVE_NUMBER;
    if (num == 0)
        return 1;
    int digits = 0;
    while (num != 0)
    {
        num /= NEXT_DIGIT;
        digits++;
    }
    return digits;
}

static char getDigit(int num, int requiredDigit)
{
    int reductions_needed = NumOfDigits(num) - requiredDigit;
    for (int i = 0 ; i < reductions_needed; i++)
        num /= NEXT_DIGIT;
    return (char)((num % NEXT_DIGIT) + CHAR_CONVERT_INT);
}

static void PutIntInString(int num, char **writeTo)
{
    int digits = NumOfDigits(num);
    for (int i = 0; *writeTo &&i < digits; i++)
    {
        **writeTo = getDigit(num, i + 1);
        *writeTo += 1;
    }
}

