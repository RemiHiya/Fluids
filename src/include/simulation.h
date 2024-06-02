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
void update(buffer *buffer, float dt);
void gravity(buffer *buffer, float dt);
void project(buffer *buffer);
void advect(buffer *buffer);
#endif //FLUIDS_SIMULATION_H
