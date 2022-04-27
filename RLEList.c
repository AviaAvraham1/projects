#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "RLEList.h"

#define EMPTY_CHAR '\0'
#define CHAR_CONVERT_INT '0'
#define NEW_LINE '\n'
#define EMPTY_NODE -1
#define NEGATIVE_NUMBER -1
#define UNIT_DIGIT 10
#define EMPTY_LIST 0
#define CHAR_AND_NEW_LINE 2

static int numOfDigits(int num);
static int charCount(RLEList list);
static void putIntInString(int num, char **writeTo);
static char getDigit(int num, int requiredDigit);
static void returnResult(RLEListResult **putInto, RLEListResult result);


 struct RLEList_t{
    char letter;
    int repetitions;
    struct RLEList_t* next;
};


RLEList RLEListCreate()
{
    RLEList ptr = malloc(sizeof(*ptr));
    if(!ptr)
    {
        return NULL;
    }
    ptr->letter = EMPTY_CHAR;
    ptr->repetitions = 0;
    ptr->next = NULL;
    return ptr;
}

void RLEListDestroy(RLEList list)
{
    while(list)
    {
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
        returnResult(&result,RLE_LIST_NULL_ARGUMENT);
        return EMPTY_CHAR;
    }
    if(RLEListSize(list)-1 < index || index < 0)
    {
        returnResult(&result,RLE_LIST_INDEX_OUT_OF_BOUNDS);
        return EMPTY_CHAR;
    }
    int count=0;
    char letter=list->letter;
    while (list)
    {
        count+=list->repetitions;
        if(index+1<=count)
        {
            returnResult(&result,RLE_LIST_SUCCESS);
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
        returnResult(&result,RLE_LIST_NULL_ARGUMENT);
        return NULL;
    }

    char *listAsString=malloc((1 + charCount(list)) * sizeof(char));
    if (!listAsString)
    {
        returnResult(&result,RLE_LIST_OUT_OF_MEMORY);
        return NULL;
    }

    for(int i=0;i< 1 + charCount(list); i++)
    {
        listAsString[i] = EMPTY_CHAR;
    }

    if (charCount(list) == 0)
    {
        *listAsString = EMPTY_CHAR;
        returnResult(&result,RLE_LIST_SUCCESS);
        return listAsString;
    }

    char *stringStart = listAsString;
    while (list)
    {
        *listAsString=list->letter;
        listAsString++;
        putIntInString(list->repetitions, &listAsString);
        *listAsString=NEW_LINE;
        listAsString++;
        list = list->next;
    }
    returnResult(&result,RLE_LIST_SUCCESS);
    return stringStart;
}


RLEListResult RLEListAppend(RLEList list, char value)
{
    if (list == NULL)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }

    while (list->next != NULL)
    {
        list = list->next;
    }

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
        {
            return RLE_LIST_OUT_OF_MEMORY;
        }
        newNode->letter = value;
        newNode->repetitions = 1;
        list->next=newNode;
        return RLE_LIST_SUCCESS;
    }
}

RLEListResult RLEListRemove(RLEList list, int index)
{
    if (list == NULL)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    if(RLEListSize(list)-1<index || index < 0)
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
        RLEList toDelete=list->next;
        list->letter=toDelete->letter;
        list->repetitions=toDelete->repetitions;
        list->next=toDelete->next;
        toDelete->next=NULL;
        RLEListDestroy(toDelete);
        return RLE_LIST_SUCCESS;
    }

    RLEList previousOne = list;
    while (list && index > list->repetitions-1)
    {
        if (list->next == NULL)
        {
            return RLE_LIST_INDEX_OUT_OF_BOUNDS;
        }
        index-=list->repetitions;
        previousOne = list;
        list = list->next;
    }

    assert(list != NULL && index < list->repetitions);

    list->repetitions--;
    if (list->repetitions == 0)
    {
        previousOne->next = list->next;
        RLEList nextOne=list->next;
        list->next = NULL;
        RLEListDestroy(list);
        if(nextOne != NULL && nextOne->letter == previousOne->letter)
        {
            previousOne->repetitions+=nextOne->repetitions;
            previousOne->next=nextOne->next;
            nextOne->next=NULL;
            RLEListDestroy(nextOne);
        }
    }
    return RLE_LIST_SUCCESS;
}

RLEListResult RLEListMap(RLEList list, MapFunction map_function)
{
    if (list == NULL || map_function == NULL)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    RLEList listHead = list;
    while (list != NULL)
    {
        list->letter = map_function(list->letter);
        list = list->next;
    }
    list = listHead;
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

static int charCount(RLEList list)
{
    if (list->letter == EMPTY_CHAR)
    {
        return EMPTY_LIST;
    }
    int count = 0;
    while (list != NULL)
    {
        count+=CHAR_AND_NEW_LINE;
        count += numOfDigits(list->repetitions);
        list = list->next;
    }
    return count;
}

static int numOfDigits(int num) {
    if (num < 0) {
        return NEGATIVE_NUMBER;
    }
    if (num == 0)
    {
        return 1;
    }
    int digits = 0;
    while (num != 0)
    {
        num /= UNIT_DIGIT;
        digits++;
    }
    return digits;
}

static char getDigit(int num, int requiredDigit)
{
    int reductionsNeeded = numOfDigits(num) - requiredDigit;
    for (int i = 0 ; i < reductionsNeeded; i++)
        num /= UNIT_DIGIT;
    return (char)((num % UNIT_DIGIT) + CHAR_CONVERT_INT);
}

static void putIntInString(int num, char **writeTo)
{
    int digits = numOfDigits(num);
    for (int i = 0; i < digits; i++)
    {
        **writeTo = getDigit(num, i + 1);
        *writeTo += 1;
    }
}

static void returnResult(RLEListResult **putInto, RLEListResult result)
{
    if (*putInto != NULL)
    {
        **putInto = result;
    }
}

