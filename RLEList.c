#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "RLEList.h"

#define EMPTY '\0'

static int NumOfDigits(int num);
static char* intToCharArray(int num);
static int NodeCount(RLEList list);

 struct RLEList_t{
    char letter;
    int repetitions;
    struct RLEList_t* next;
};

//implement the functions here
RLEList RLEListCreate(){
    RLEList ptr= malloc(sizeof(*ptr));
    if(!ptr)
    {
        return NULL;
    }
    ptr ->letter=EMPTY;
    ptr ->repetitions=0;
    ptr ->next =NULL;
    return ptr;
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
    else
    {
        RLEList newNode = RLEListCreate();
        if (newNode == NULL)
            return RLE_LIST_OUT_OF_MEMORY;

        newNode->letter = value;
        newNode->repetitions = 1;
        list->next=newNode;
        //RLEListDestroy(newNode);
        return RLE_LIST_SUCCESS;
    }
}

RLEListResult RLEListRemove(RLEList list, int index)
{

    if (list == NULL)
        return RLE_LIST_NULL_ARGUMENT;

    RLEList previousOne;
    while (index > list->repetitions)
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
        list->next = NULL;
        RLEListDestroy(list);
    }
    return RLE_LIST_SUCCESS;
}

RLEListResult RLEListMap(RLEList list, MapFunction map_function)
{
    if (list == NULL || map_function == NULL)
        return RLE_LIST_NULL_ARGUMENT;
    while (list != NULL)
    {
        list->letter = map_function(list->letter);
        list = list->next;
    }
    return RLE_LIST_SUCCESS;

}

static int NodeCount(RLEList list)
{
    if (list == NULL)
        return RLE_LIST_NULL_ARGUMENT;
    int num = 0;
    while (list != NULL)
    {
        num++;
        num++;
        num += NumOfDigits(list->repetitions);
    }
    return num;
}

static int NumOfDigits(int num)
{
    if (num < 0)
        return -1; //ADD DEFINE HERE <--------------------
    if (num == 0)
        return 1;

    int digits = 0;
    while (num != 0)
    {
        num /= 10;
        digits++;
    }
    return digits;
}

static char* intToCharArray(int num)
{
    //Avia will do

}

