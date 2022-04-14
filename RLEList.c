#include "RLEList.h"

typedef struct RLEList_t{
    char letter;
    int reptitions;
    struct RLEList_t* next;
};

//implement the functions here