#include <stdio.h>
#include <stdint.h>
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include "vec3.h"
#include "objs.h"
#include "objLoader.h"

int HEIGHT = 640;
int WIDTH = 800;
#define FOV 70
#define ASPECT ((float)HEIGHT / (float)WIDTH)

SDL_Renderer* renderer;
SDL_Window* window;
SDL_Texture* buffer;
uint32_t * FrameBuffer;
obj plane;

void renderImage(void);
void wait4input(void);
void tracePixel(int x, int y);
void plotPixel(int x, int y, vec3 Color);
vec3 getVecDirFromCam(int x, int y, int fov);

const vec3 lightPos =
{
    .x = 0,
    .y = 1,
    .z = 2,
};

const vec3 cameraPos = 
{
    .x = 0,
    .y = 1,
    .z = -5,
};

const vec3 spherePos =
{
    .x = 0,
    .y = 1,
    .z = 2,
};

int main(__attribute((unused)) int argc, __attribute((unused)) char** argv){
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow(
        "RTX", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WIDTH, HEIGHT, SDL_WINDOW_RESIZABLE
    );
    renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    buffer = SDL_CreateTexture(renderer,
        SDL_PIXELFORMAT_RGBA8888,
        SDL_TEXTUREACCESS_STREAMING,
        WIDTH,
        HEIGHT);
    FrameBuffer = (uint32_t*)malloc(WIDTH * HEIGHT * sizeof(uint32_t));

    printf("started rendering... %s\n", SDL_GetError());
    renderImage();
    wait4input();
    SDL_Quit();
    SDL_DestroyTexture(buffer);
    free(FrameBuffer);
    return 0;
}

void wait4input(void)
{
    while(1)
    {
        SDL_Event event;
        while(SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT:
                    return;
                case SDL_WINDOWEVENT:
                    if(event.window.event == SDL_WINDOWEVENT_RESIZED)
                    {
                        SDL_GetWindowSize(window, &WIDTH, &HEIGHT);
                        free(FrameBuffer);
                        SDL_DestroyTexture(buffer);
                        buffer = SDL_CreateTexture(renderer,
                            SDL_PIXELFORMAT_RGBA8888,
                            SDL_TEXTUREACCESS_STREAMING,
                            WIDTH,
                            HEIGHT);
                        FrameBuffer = (uint32_t*)malloc(WIDTH * HEIGHT * sizeof(uint32_t));
                        renderImage();
                    }
                    break;
            }
        }
    }
}

void renderImage(void)
{
    plane = GetPlane();
    for (int i = 0; i < WIDTH; i++)
    {
        for (int j = 0; j < HEIGHT; j++)
        {
            tracePixel(i, j);
        }
    }
    
    SDL_UpdateTexture(buffer, NULL, FrameBuffer, WIDTH * 4);
    SDL_RenderCopy(renderer, buffer, NULL, NULL);
    SDL_RenderPresent(renderer);

    free(plane.triangles);
}

void plotPixel(int x, int y, vec3 Color)
{
    uint32_t col =  (((int)(fminf(Color.x, 1.0) * 255) & 0xFF) << 24) |
                    (((int)(fminf(Color.y, 1.0) * 255) & 0xFF) << 16) |
                    (((int)(fminf(Color.z, 1.0) * 255) & 0xFF) << 8 ) |
                    0x00;
    FrameBuffer[y * WIDTH + x] = col;
}

int InInfluenceSphere(vec3 rayOrigin, vec3 rayDirection, vec3 center, float radius)
{
	vec3 oc = SubVec3(center, rayOrigin);
    float a = DotVec3(rayDirection, rayDirection);
    float b = 2.0f * DotVec3(rayDirection, oc);
    float c = DotVec3(oc, oc) - radius * radius;
    float discriminant = b * b - 4 * a * c;
    return (discriminant > 0);
}

// this function is from wikipedia
int ray_intersects_triangle(const vec3 ray_origin,
    const vec3 ray_vector,
    const triangle triangle, vec3* out_intersection_point)
{
    const float epsilon = 1.19209e-07;

    vec3 edge1 = SubVec3(triangle.b, triangle.a);
    vec3 edge2 = SubVec3(triangle.c, triangle.a);
    vec3 ray_cross_e2 = CrossVec3(ray_vector, edge2);
    float det = DotVec3(edge1, ray_cross_e2);

    if (det > -epsilon && det < epsilon)
        return 0;    // This ray is parallel to this triangle.

    float inv_det = 1.0 / det;
    vec3 s = SubVec3(ray_origin, triangle.a);
    float u = inv_det * DotVec3(s, ray_cross_e2);

    if ((u < 0 && fabsf(u) > epsilon) || (u > 1 && fabsf(u - 1) > epsilon))
        return 0;

    vec3 s_cross_e1 = CrossVec3(s, edge1);
    float v = inv_det * DotVec3(ray_vector, s_cross_e1);

    if ((v < 0 && fabsf(v) > epsilon) || (u + v > 1 && fabsf(u + v - 1) > epsilon))
        return 0;

    // At this stage we can compute t to find out where the intersection point is on the line.
    float t = inv_det * DotVec3(edge2, s_cross_e1);

    if (t > epsilon) // ray intersection
    {
        if(out_intersection_point != NULL)
            *out_intersection_point = AddVec3(ray_origin, ValMulVec3(ray_vector, t));
        return 1;
    }
    else // This means that there is a line intersection but not a ray intersection.
        return 0;
}

vec3 getVecDirFromCam(int x, int y, int fov)
{
    vec3 dir = {0,0,1};
    float angleX = ((float)x / WIDTH - .5) * (float)fov;
    float deltaX = dir.z * tanf(angleX * DEG_TO_RAD);
    dir.x += deltaX;
    float angleY = -((float)y / HEIGHT - .5) * (float)fov * ASPECT;
    float deltaY = dir.z * tanf(angleY * DEG_TO_RAD);
    dir.y += deltaY;
    return dir;
}

float Specular(vec3 normal, vec3 tolightVec, vec3 viewDir, float S)
{
    //vec3 halfwayDir = NormVec3(AddVec3(SubVec3((vec3){0,0,0}, tolightVec), viewDir));
    float Dot = powf(fmax(DotVec3(normal, tolightVec), 0.0), 32) * S;
/*
    vec3 halfwayDir = normalize(lightDir2 + viewDir);
    pow(max(dot(normal, halfwayDir), 0.0), 32.0) * specFact;
*/
    
    if(Dot > 0) return Dot;
    return 0;

}

vec3 calculateLighting(vec3 baseColor, vec3 hitpoint, vec3 reflectedRay, vec3 Dir, vec3 normal)
{

    vec3 ToLightVec = NormVec3(SubVec3(lightPos, hitpoint));
    float Spec = Specular(reflectedRay, ToLightVec, Dir, 0.3);
    vec3 Specular = (vec3){Spec, Spec, Spec};

    //float lightIntensity = 1 / LenVec3(ToLightVec);
    float diff = DotVec3(ToLightVec, normal);
    //max(dot(lightDir2, normal), 0.0);
    vec3 Diffuse = (vec3){diff, diff, diff};
    
    //float specular = 0;
    //baseColor = AddVec3(baseColor, (vec3){specular, specular, specular});

    float ambientFact = 0.1;
    vec3 Ambient = (vec3){ambientFact, ambientFact, ambientFact};
    vec3 lighting = Ambient;
    Diffuse = AddVec3(Diffuse, Specular);
    lighting = AddVec3(Ambient, Diffuse);
    return (MulVec3(baseColor, lighting));
}

void tracePixel(int x, int y)
{
    vec3 dir = NormVec3(getVecDirFromCam(x, y, FOV));
    int planehit = 0;
    vec3 ClosestHitPoint;
    float ClosestHitPointDist = -1;
    int triangleIndex = -1;
    for (int i = 0; i < plane.tiangleCount; i++)
    {
        vec3 hitPoint = {0, 0, 0};
        int hit = ray_intersects_triangle(cameraPos, dir, plane.triangles[i], &hitPoint);
        if(!hit)
            continue;
        float dist = LenVec3(SubVec3(cameraPos, hitPoint));
        if(ClosestHitPointDist == -1 || dist < ClosestHitPointDist)
        {
            ClosestHitPointDist = dist;
            ClosestHitPoint = hitPoint;
            triangleIndex = 1;
        }
        planehit++;
    }
    
    int intersect = InInfluenceSphere(cameraPos, dir, spherePos, .1);
    vec3 color = (vec3){0, 0, 0};
    
    if(!!planehit)
    {
        vec3 Norm = GetTriangleNormal(plane.triangles[triangleIndex]);
        vec3 Reflected = RefectVec3(dir, Norm);
        color = calculateLighting(plane.color, ClosestHitPoint, Reflected, dir, Norm);
    }
    color = intersect ? (vec3){1, 1, 1} : color;

    plotPixel(x, y, color);
}
