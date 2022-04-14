#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "RLEList.h"

#define EMPTY_CHAR '\0'
#define EMPTY_NODE -1

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
        *result= RLE_LIST_NULL_ARGUMENT;
        return EMPTY_CHAR;
    }
    if(RLEListSize(list)<index)
    {
        *result= RLE_LIST_INDEX_OUT_OF_BOUNDS;
        return EMPTY_CHAR;
    }
    int count=0;
    while (list)
    {
        count+=list->repetitions;
        if(index<=count)
        {
            *result= RLE_LIST_SUCCESS;
            return list->letter;
        }
        list = list->next;
    }
}

char* RLEListExportToString(RLEList list, RLEListResult* result)
{
    if(list==NULL)
    {
        *result= RLE_LIST_NULL_ARGUMENT;
        return NULL;
    }
    char *list_as_string=malloc(NodeCount(list)*3* sizeof(char));
    while (list)
    {
        *list_as_string=list->letter;
        list_as_string++;
        *list_as_string=(char)(list->repetitions);
        list_as_string++;
        *list_as_string='\n';
        list_as_string++;
        list = list->next;
    }
    *result= RLE_LIST_SUCCESS;
    return list_as_string;
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

