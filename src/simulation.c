//
// Created by remsc on 02/06/2024.
//

#include "include/simulation.h"
#include "include/utils.h"
#include <stdlib.h>

const float g = -9.81f;

buffer *init(int w, int h, float res) {
    buffer *buffer = malloc(sizeof(struct BUFFER_T));

    int width = w*res, height = h*res;

    buffer->w = width;
    buffer->h = height;
    buffer->res = res;
    buffer->ubuffer = calloc(height, sizeof(double*));
    buffer->vbuffer = calloc(height, sizeof(double*));

    for (int i = 0; i < height; ++i) {
        buffer->ubuffer[i] = calloc(width, sizeof(double));
        buffer->vbuffer[i] = calloc(width, sizeof(double));
    }

    return buffer;
}

int cellCheck(buffer *buffer, int x, int y) {
    return y>=0 && y<buffer->h && x>=0 && x<buffer->w;
}

void display(buffer *buffer) {
    for (int i = 0; i < buffer->h; ++i) {
        for (int j = 0; j < buffer->w; ++j) {
            //Color c = dir2col(j-buffer->w/2, i-buffer->h/2);
            Color c = dir2col(buffer->ubuffer[i][j], buffer->vbuffer[i][j]);
            drawPixel(j, i, buffer->res, c);
        }
    }
}

void update(buffer *buffer, float dt) {
    gravity(buffer, dt);
    //project(buffer, 500);
    advect(buffer, dt);
}

void gravity(buffer *buffer, float dt) {
    for (int i = 0; i < buffer->h; ++i) {
        for (int j = 0; j < buffer->w; ++j) {
            //buffer->vbuffer[i][j] += dt * -g;
//            buffer->ubuffer[i][j] *= 0.9;
//            buffer->vbuffer[i][j] *= 0.9;
        }
    }
}

void project(buffer *buffer, unsigned int n) {
    for (int iter = 0; iter < n; ++iter) {
        for (int j = 0; j < buffer->h-1; ++j) {
            for (int i = 0; i < buffer->w-1; ++i) {
                double d = buffer->ubuffer[j][i+1] - buffer->ubuffer[j][i] +
                        buffer->vbuffer[j+1][i] - buffer->vbuffer[j][i];
                d *= 1.9;
                int s = cellCheck(buffer, i+1, j) + cellCheck(buffer, i-1, j) +
                        cellCheck(buffer, i, j+1) + cellCheck(buffer, i, j-1);
                buffer->ubuffer[j][i]   += d * cellCheck(buffer, i-1, j) / s;
                buffer->ubuffer[j][i+1] -= d * cellCheck(buffer, i+1, j) / s;
                buffer->vbuffer[j][i]   += d * cellCheck(buffer, i, j-1) / s;
                buffer->vbuffer[j+1][i] -= d * cellCheck(buffer, i, j+1) / s;
            }
        }
    }
}
void advect(buffer *buffer, float dt) {
    for (int j = 1; j < buffer->h-1; ++j) {
        for (int i = 1; i < buffer->w-1; ++i) {
            buffer->ubuffer[j][i] += buffer->ubuffer[j+1][i];
            buffer->ubuffer[j][i] += buffer->ubuffer[j-1][i];
            buffer->ubuffer[j][i] += buffer->ubuffer[j][i+1];
            buffer->ubuffer[j][i] += buffer->ubuffer[j][i-1];
            buffer->ubuffer[j][i] /= 5;
            buffer->vbuffer[j][i] += buffer->vbuffer[j+1][i];
            buffer->vbuffer[j][i] += buffer->vbuffer[j-1][i];
            buffer->vbuffer[j][i] += buffer->vbuffer[j][i+1];
            buffer->vbuffer[j][i] += buffer->vbuffer[j][i-1];
            buffer->vbuffer[j][i] /= 5;
        }
    }
}
