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
    buffer->ubuffer = malloc(height * sizeof(double*));
    buffer->vbuffer = malloc(height * sizeof(double*));

    for (int i = 0; i < height; ++i) {
        buffer->ubuffer = malloc(width * sizeof(double));
        buffer->vbuffer = malloc(width * sizeof(double));
    }

    return buffer;
}

void display(buffer *buffer) {
    for (int i = 0; i < buffer->h; ++i) {
        for (int j = 0; j < buffer->w; ++j) {
            drawPixel(j, i, buffer->res, CLITERAL(Color){j%10 * 25, i%10 * 25, 0, 255});
            buffer->vbuffer[i][j];
        }
    }
}
void update(buffer *buffer, float dt) {
    gravity(buffer, dt);
    project(buffer);
    advect(buffer);
}

void gravity(buffer *buffer, float dt) {
    for (int i = 0; i < buffer->h; ++i) {
        for (int j = 0; j < buffer->w; ++j) {
            buffer->vbuffer[i][j] += dt * -g;
        }
    }
}

void project(buffer *buffer) {

}
void advect(buffer *buffer) {

}
