//
// Created by remsc on 02/06/2024.
//

#include "include/simulation.h"
#include <stdlib.h>

buffer *init(int w, int h, float res) {
    buffer *buffer = malloc(sizeof(struct BUFFER_T));

    int width = w/res, height = h/res;

    buffer->ubuffer = malloc(height * sizeof(float*));
    buffer->vbuffer = malloc(height * sizeof(float*));

    for (int i = 0; i < height; ++i) {
        buffer->ubuffer = malloc(width * sizeof(float));
        buffer->vbuffer = malloc(width * sizeof(float));
    }

    return buffer;
}
