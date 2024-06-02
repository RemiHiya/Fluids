#include "raylib.h"
#include <stdio.h>
#include "src/include/simulation.h"

const int screenWidth = 800;
const int screenHeight = 450;
const float resolution = 0.1f;


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
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
