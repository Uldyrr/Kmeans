#include "List_t.h"
#include <stdio.h>

typedef struct List {
    void** Elements;
    uint64_t Capacity;
    uint64_t Count;  
} List_t;


List_t* CreateList(uint64_t capacity) {
    List_t* list = (List_t*)malloc(sizeof(List_t));

    if (list == NULL) {
        printf("Unable to allocate %zu bytes for list\n", sizeof(List_t));
        return NULL;
    } 

    list->Elements = (void**)malloc(sizeof(void*) * capacity);

    if (list->Elements == NULL) {
        printf("Unable to allocate %zu bytes for elements\n", sizeof(void*) * capacity);
        return NULL;
    }

    list->Capacity = capacity;
    list->Count = 0;

    return list;
}

void DestroyList(List_t* list, FreeFN_t freeFN) {
    if (list == NULL) return;
    if (freeFN != NULL) { 
        uint64_t count = list->Count;  

        for (uint64_t i = 0; i < count; i++) freeFN(list->Elements[i]); 
    }
    if (list->Elements != NULL) free(list->Elements);
    
    free(list);
}

void ListAdd(List_t* list, void* element) {
    if (list->Count + 1 > list->Capacity) {
        list->Capacity *= 2;
        list->Elements = (void**)realloc(list->Elements, sizeof(void*) * list->Capacity);

        if (list->Elements == NULL) {
            printf("Failed to reallocate elements for list during add!\n");
            return;
        }
    }

    list->Elements[list->Count++] = element;
}

void ListRemove(List_t* list, uint64_t i) {
    uint64_t end = list->Count - 1;

    if (i > end) return;
    if (i == end) { list->Count = end; return; }
    while (i < end) {
        list->Elements[i] = list->Elements[i + 1];
        i++;
    }

    list->Count--;
}

void ListClear(List_t* list) {
    list->Count = 0;
}

void* ListIndex(List_t* list, uint64_t i) {
    if (i >= list->Count) return NULL;

    return list->Elements[i];
}

uint64_t ListLength(List_t* list) {
    return list->Count;
}