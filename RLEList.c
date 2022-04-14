#include <stdio.h>
#include <stdlib.h>
#include "RLEList.h"

#define EMPTY '\0'

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