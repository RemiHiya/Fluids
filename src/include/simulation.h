//
// Created by remsc on 02/06/2024.
//

#ifndef FLUIDS_SIMULATION_H
#define FLUIDS_SIMULATION_H

typedef struct BUFFER_T {
    int w, h;
    float **ubuffer;
    float **vbuffer;
} buffer;

buffer *init(int w, int h, float res);
#endif //FLUIDS_SIMULATION_H
