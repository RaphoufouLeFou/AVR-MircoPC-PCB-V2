#ifndef _VEC_3_
#define _VEC_3_

typedef struct {float x,y,z;} vec3;
#define MY_PI 3.14159265358979323846264338327950
#define DEG_TO_RAD MY_PI/180.0
#define RAD_TO_DEG 180.0/M_PI

vec3 SubVec3(vec3 a, vec3 b);
vec3 AddVec3(vec3 a, vec3 b);
vec3 MulVec3(vec3 a, vec3 b);
vec3 CrossVec3(vec3 a, vec3 b);
vec3 NormVec3(vec3 a);
vec3 RefectVec3(vec3 a, vec3 norm);
float DotVec3(vec3 a, vec3 b);
float LenVec3(vec3 a);
vec3 ValMulVec3(vec3 a, float b);
vec3 ValAddVec3(vec3 a, float b);
float AngleVec3(vec3 a, vec3 b);


#endif //_VEC_3_