#include "vec3.h"
#include <math.h>

inline vec3 SubVec3(vec3 a, vec3 b)
{
    return (vec3)
    {
        .x = a.x - b.x,
        .y = a.y - b.y,
        .z = a.z - b.z,
    };
}

inline vec3 AddVec3(vec3 a, vec3 b)
{
    return (vec3)
    {
        .x = a.x + b.x,
        .y = a.y + b.y,
        .z = a.z + b.z,
    };
}

inline vec3 MulVec3(vec3 a, vec3 b)
{
    return (vec3)
    {
        .x = a.x * b.x,
        .y = a.y * b.y,
        .z = a.z * b.z,
    };
}


inline vec3 ValMulVec3(vec3 a, float b)
{
    return (vec3)
    {
        .x = a.x * b,
        .y = a.y * b,
        .z = a.z * b,
    };
}

vec3 ValAddVec3(vec3 a, float b)
{
    return (vec3)
    {
        .x = a.x + b,
        .y = a.y + b,
        .z = a.z + b,
    };
}

float AngleVec3(vec3 a, vec3 b)
{
    float dot = DotVec3(a, b);
    float div = dot / (LenVec3(a) * LenVec3(b));
    return acosf(div * DEG_TO_RAD);
}

inline vec3 CrossVec3(vec3 a, vec3 b)
{
    return (vec3)
    {
        .x = a.y * b.z - a.z * b.y,
        .y = a.z * b.x - a.x * b.z,
        .z = a.x * b.y - a.y * b.x,
    };
}

inline float LenVec3(vec3 a)
{
    return sqrtf(a.x * a.x + a.y * a.y + a.z * a.z);
}

inline vec3 NormVec3(vec3 a)
{
    float len = LenVec3(a);
    return (vec3)
    {
        .x = a.x / len,
        .y = a.y / len,
        .z = a.z / len,
    };
}

vec3 RefectVec3(vec3 a, vec3 norm)
{
    return SubVec3(a, ValMulVec3(norm, 2 * DotVec3(a, norm)));
}

inline float DotVec3(vec3 a, vec3 b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}