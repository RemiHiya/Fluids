//
// Created by remsc on 04/06/2024.
//

#include "include/fluid.h"
#include "include/utils.h"
#include <stdlib.h>
#include <math.h>

#define IX(x, y) ((x) + (y) * w)

fluid *fluidCreate(int w, int h, float diffusion, float viscosity, float dt) {
    fluid *fluid = malloc(sizeof(*fluid));

    fluid->sizeX = w;
    fluid->sizeY = h;
    fluid->dt = dt;
    fluid->diff = diffusion;
    fluid->visc = viscosity;

    fluid->s = calloc(w * h, sizeof(float));
    fluid->density = calloc(w * h, sizeof(float));

    fluid->Vx = calloc(w * h, sizeof(float));
    fluid->Vy = calloc(w * h, sizeof(float));

    fluid->Vx0 = calloc(w * h, sizeof(float));
    fluid->Vy0 = calloc(w * h, sizeof(float));

    return fluid;
}

void fluidFree(fluid *fluid) {
    free(fluid->s);
    free(fluid->density);

    free(fluid->Vx);
    free(fluid->Vy);

    free(fluid->Vx0);
    free(fluid->Vy0);

    free(fluid);
}

void fluidStep(fluid *fluid) {
    int w          = fluid->sizeX;
    int h          = fluid->sizeY;
    float visc     = fluid->visc;
    float diff     = fluid->diff;
    float dt       = fluid->dt;
    float *Vx      = fluid->Vx;
    float *Vy      = fluid->Vy;
    float *Vx0     = fluid->Vx0;
    float *Vy0     = fluid->Vy0;
    float *s       = fluid->s;
    float *density = fluid->density;

    diffuse(1, Vx0, Vx, visc, dt, 4, w, h);
    diffuse(2, Vy0, Vy, visc, dt, 4, w, h);

    project(Vx0, Vy0, Vx, Vy, 4, w, h);

    advect(1, Vx, Vx0, Vx0, Vy0, dt, w, h);
    advect(2, Vy, Vy0, Vx0, Vy0, dt, w, h);

    project(Vx, Vy, Vx0, Vy0, 4, w, h);
    diffuse(0, s, density, diff, dt, 4, w, h);
    advect(0, density, s, Vx, Vy, dt, w, h);
}

void fluidRenderDensity(fluid *fluid, int w, int h, float res) {
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            float d = fluid->density[IX(j, i)];
            drawPixel(j, i, res, CLITERAL(Color){255, 255, 255, (int) d});
        }
    }
}

void fluidFadeDensity(fluid *fluid, int w, int h, float dt) {
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            float d = fluid->density[IX(j, i)] -= 1 * dt;
            fluid->density[IX(j, i)] = d<0 ? 0 : d;

        }
    }
}

void fluidAddDensity(fluid *fluid, int x, int y, float amount) {
    int w = fluid->sizeX;
    fluid->density[IX(x, y)] += amount;
}

void fluidAddVelocity(fluid *fluid, int x, int y, float amountX, float amountY) {
    int w = fluid->sizeX;
    int index = IX(x, y);

    fluid->Vx[index] += amountX;
    fluid->Vy[index] += amountY;
}

static void diffuse (int b, float *x, float *x0, float diff, float dt, int iter, int w, int h) {
    float a = dt * diff * (float) (w - 2) * (float) (h - 2);
    lin_solve(b, x, x0, a, 1 + 6 * a, iter, w, h);
}

static void lin_solve(int b, float *x, float *x0, float a, float c, int iter, int w, int h) {
    float cRecip = 1.0f / c;
    for (int k = 0; k < iter; k++) {
        for (int j = 1; j < h - 1; j++) {
            for (int i = 1; i < w - 1; i++) {
                x[IX(i, j)] =
                        (x0[IX(i, j)]
                        + a*(x[IX(i+1, j)]
                        +x[IX(i-1, j    )]
                        +x[IX(i  , j+1  )]
                        +x[IX(i  , j-1  )]
                        )) * cRecip;
            }
        }
        set_bnd(b, x, w, h);
    }
}

static void project(float *velX, float *velY, float *p, float *div, int iter, int w, int h) {
    for (int j = 1; j < h - 1; j++) {
        for (int i = 1; i < w - 1; i++) {
            div[IX(i, j)] = -0.5f*(
                    velX[IX(i+1, j   )]
                    -velX[IX(i-1, j  )]
                    +velY[IX(i  , j+1)]
                    -velY[IX(i  , j-1)]
                    )/(float) w;   // ????
            p[IX(i, j)] = 0;
        }
    }
    set_bnd(0, div, w, h);
    set_bnd(0, p, w, h);
    lin_solve(0, p, div, 1, 6, iter, w, h);

        for (int j = 1; j < h - 1; j++) {
            for (int i = 1; i < w - 1; i++) {
                velX[IX(i, j)] -= 0.5f * (  p[IX(i+1, j)]
                                                 -p[IX(i-1, j)]) * (float) w; // ??
                velY[IX(i, j)] -= 0.5f * (  p[IX(i, j+1)]
                                                 -p[IX(i, j-1)]) * (float) h; // ??
            }
        }
    set_bnd(1, velX, w, h);
    set_bnd(2, velY, w, h);
}
static void advect(int b, float *d, float *d0,  float *velX, float *velY, float dt, int w, int h) {
    float i0, i1, j0, j1;

    float dtx = dt * (float) (w - 2);
    float dty = dt * (float) (h - 2);

    float s0, s1, t0, t1;
    float tmp1, tmp2, x, y;

    float Nfloat = (float) w;
    float ifloat, jfloat;
    int i, j;

    for(j = 1, jfloat = 1; j < h - 1; j++, jfloat++) {
        for(i = 1, ifloat = 1; i < w - 1; i++, ifloat++) {
            tmp1 = dtx * velX[IX(i, j)];
            tmp2 = dty * velY[IX(i, j)];
            x    = ifloat - tmp1;
            y    = jfloat - tmp2;

            if(x < 0.5f) x = 0.5f;
            if(x > Nfloat + 0.5f) x = Nfloat + 0.5f;
            i0 = floorf(x);
            i1 = i0 + 1.0f;
            if(y < 0.5f) y = 0.5f;
            if(y > Nfloat + 0.5f) y = Nfloat + 0.5f;
            j0 = floorf(y);
            j1 = j0 + 1.0f;

            s1 = x - i0;
            s0 = 1.0f - s1;
            t1 = y - j0;
            t0 = 1.0f - t1;

            int i0i = (int) i0;
            int i1i = (int) i1;
            int j0i = (int) j0;
            int j1i = (int) j1;

            d[IX(i, j)] =
                    s0 * ( t0 * d0[IX(i0i, j0i)] + t1 * d0[IX(i0i, j1i)]) +
                    s1 * ( t0 * d0[IX(i1i, j0i)] + t1 * d0[IX(i1i, j1i)]);
        }
    }
    set_bnd(b, d, w, h);
}

static void set_bnd(int b, float *x, int w, int h) {
    for(int i = 1; i < w - 1; i++) {
        x[IX(i, 0  )] = b == 2 ? -x[IX(i, 1  )] : x[IX(i, 1  )];
        x[IX(i, h-1)] = b == 2 ? -x[IX(i, h-2)] : x[IX(i, h-2)];
    }
    for(int j = 1; j < h - 1; j++) {
        x[IX(0  , j)] = b == 1 ? -x[IX(1  , j)] : x[IX(1  , j)];
        x[IX(w-1, j)] = b == 1 ? -x[IX(w-2, j)] : x[IX(w-2, j)];
    }

    x[IX(0, 0)]       = 0.33f * (x[IX(1, 0)] + x[IX(0, 1)]);
    x[IX(0, h-1)]     = 0.33f * (x[IX(1, h-1)] + x[IX(0, h-2)]);
    x[IX(w-1, 0)]     = 0.33f * (x[IX(w-2, 0)] + x[IX(w-1, 1)]);
    x[IX(w-1, h-1)]   = 0.33f * (x[IX(w-2, h-1)] + x[IX(w-1, h-2)]);
}