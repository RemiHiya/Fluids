#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include "src/include/simulation.h"

const int screenWidth = 800;
const int screenHeight = 400;
const float resolution = 0.5f;


int main(void)
{
    InitWindow(screenWidth, screenHeight, "Fluid Simulation");
    SetTargetFPS(60);

    buffer *buffer = init(screenWidth, screenHeight, resolution);
    printf("Res : %f\nW : %d\nH : %d", buffer->res, buffer->w, buffer->h);
    while (!WindowShouldClose()) {
        update(buffer, GetFrameTime());
        BeginDrawing();
        ClearBackground(BLACK);
        display(buffer);
        char *t = malloc(16 * sizeof(char));
        sprintf(t, "%f", 1.0f/GetFrameTime());
        DrawText(t, 0, 0, 15, RED);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
