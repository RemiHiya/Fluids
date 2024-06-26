//
// Created by remsc on 04/06/2024.
//

#ifndef FLUIDS_FLUID_H
#define FLUIDS_FLUID_H
typedef struct FLUID_T {
    int sizeX;
    int sizeY;
    float dt;
    float diff;
    float visc;

    float *s;
    float *density;

    float *Vx;
    float *Vy;

    float *Vx0;
    float *Vy0;
} fluid;

fluid *fluidCreate(int w, int h, float diffusion, float viscosity, float dt);
void fluidFree(fluid *fluid);
void fluidStep(fluid *fluid);
void fluidRenderDensity(fluid *fluid, int w, int h, float res);
void fluidRenderVelocity(fluid *fluid, int w, int h, float res);
void fluidFadeDensity(fluid *fluid, int w, int h, float dt);
void fluidAddDensity(fluid *fluid, int x, int y, float amount);
void fluidAddVelocity(fluid *fluid, int x, int y, float amountX, float amountY);
static void set_bnd(int b, float *x, int w, int h);
static void lin_solve(int b, float *x, float *x0, float a, float c, int iter, int w, int h);
static void diffuse (int b, float *x, float *x0, float diff, float dt, int iter, int w, int h);
static void project(float *velX, float *velY, float *p, float *div, int iter, int w, int h);
static void advect(int b, float *d, float *d0,  float *velX, float *velY, float dt, int w, int h);
#endif //FLUIDS_FLUID_H
