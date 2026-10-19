#ifndef LIST_H_
#define LIST_H_

#include <stdlib.h>
#include <stdint.h>

#define LIST_DEFAULT_CAPACITY 8

typedef struct List List_t;
typedef void (*FreeFN_t)(void*);

List_t* CreateList(uint64_t capacity);
void DestroyList(List_t* list, FreeFN_t freeFN);
void ListAdd(List_t* list, void* element);
void ListRemove(List_t* list, uint64_t i);
void ListClear(List_t* list);
void* ListIndex(List_t* list, uint64_t i);
uint64_t ListLength(List_t* list);

#endif