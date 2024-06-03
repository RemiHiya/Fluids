#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include "src/include/simulation.h"

const int screenWidth = 1600;
const int screenHeight = 800;
const float resolution = 0.05f;


int main(void)
{
    InitWindow(screenWidth, screenHeight, "Fluid Simulation");
    SetTargetFPS(30);

    buffer *buffer = init(screenWidth, screenHeight, resolution);
    printf("Res : %f\nW : %d\nH : %d", buffer->res, buffer->w, buffer->h);
    while (!WindowShouldClose()) {
        update(buffer, GetFrameTime());
        buffer->ubuffer[15][15] = 255;
        buffer->vbuffer[15][15] = 0;
        buffer->ubuffer[15][50] = -255;
        buffer->vbuffer[15][50] = 0;
        BeginDrawing();
        ClearBackground(BLACK);
        display(buffer);
        char *t = malloc(16 * sizeof(char));
        sprintf(t, "%0.1f, %0.1f", 1.0f/GetFrameTime(), buffer->ubuffer[15][30]);
        DrawText(t, 0, 0, 15, RED);
        EndDrawing();
    }

    CloseWindow();
    free(buffer);
    return 0;
}
