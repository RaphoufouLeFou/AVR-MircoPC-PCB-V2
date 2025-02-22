#ifndef _OBJS_
#define _OBJS_

#include <stdlib.h>
#include "vec3.h"

typedef struct {vec3 a,b,c;} triangle;

typedef struct
{
    vec3 color;
    vec3 pos;
    int tiangleCount;
    triangle * triangles;
}obj;

vec3 GetTriangleNormal(triangle a)
{
    return NormVec3(CrossVec3(SubVec3(a.b, a.a), SubVec3(a.c, a.a)));
}

obj GetPlane()
{
    obj plane = 
    {
        .color = {0.1, 0.1, 1},
        .pos = {0, 0, 0},
        .triangles = (triangle*)malloc(2 * sizeof(triangle)),
    };
    vec3 vert1 = {100, 0, 100};
    vec3 vert2 = {-100, 0, 100};
    vec3 vert3 = {100, 0, -100};
    vec3 vert4 = {-100, 0, -100};
    triangle t1 = 
    {
        .a = vert3, .b = vert2, .c = vert1,
    };
    triangle t2 = 
    {
        .a = vert3, .b = vert4, .c = vert2,
    };
    plane.triangles[0] = t1;
    plane.triangles[1] = t2;
    plane.tiangleCount = 2;
    return plane;
}

#endif //_OBJS_