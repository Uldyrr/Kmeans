#include "Vector2_t.h"
#include <stdlib.h>
#include <stdio.h>

Vector2_t* CreateVector2(float x, float y) {
    Vector2_t* vector = (Vector2_t*)malloc(sizeof(Vector2_t));
    
    if (vector == NULL) {
        printf("Unable to allocate %zu bytes for a new vector\n", sizeof(Vector2_t));
        return NULL;
    }
    
    vector->X = x;
    vector->Y = y;

    return vector;
}

Vector2_t* CopyVector2(Vector2_t* v) {
    return CreateVector2(v->X, v->Y);
}

void DestroyVector2(Vector2_t* v) {
    free(v);
}

float Vector2Magnitude(Vector2_t* v) {
    register float x = v->X;
    register float y = v->Y;

    return sqrtf(x*x + y*y);
}

float Vector2DistanceBetween(Vector2_t* a, Vector2_t* b) {
    register float dx = b->X - a->X;
    register float dy = b->Y - a->Y;

    return sqrtf(dx*dx + dy*dy);
}

uint8_t Vector2Equality(Vector2_t* a, Vector2_t* b) {
    return a->X == b->X && a->Y == b->Y ? 1 : 0; 
}