#ifndef VECTOR2_H_
#define VECTOR2_H_

#include <math.h>
#include <stdint.h>

typedef struct {
    float X;
    float Y;
} Vector2_t;

Vector2_t* CreateVector2(float x, float y);
Vector2_t* CopyVector2(Vector2_t* v);
void DestroyVector2(Vector2_t* v);
float Vector2Magnitude(Vector2_t* v);
float Vector2DistanceBetween(Vector2_t* a, Vector2_t* b);
uint8_t Vector2Equality(Vector2_t* a, Vector2_t* b);

#endif