#include <stdio.h>
#include <stdlib.h>
#include "RLEList.h"

#define EMPTY_CHAR '\0'
#define EMPTY_NODE -1

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
