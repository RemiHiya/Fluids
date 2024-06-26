#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include "src/include/fluid.h"

const int screenWidth = 1600;
const int screenHeight = 800;
const float resolution = 0.07f;


int main(void)
{
    InitWindow(screenWidth, screenHeight, "Fluid Simulation");
    SetTargetFPS(60);

    int w = screenWidth * resolution +1;
    int h = screenHeight * resolution +1;
    fluid *fluid = fluidCreate(w, h, 0, 0, 0);

    while (!WindowShouldClose()) {

        fluid->dt = GetFrameTime();
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            fluidAddDensity(fluid, GetMouseX() * resolution, GetMouseY() * resolution, 500);
            fluidAddVelocity(fluid, GetMouseX()*resolution, GetMouseY()*resolution, GetMouseDelta().x, GetMouseDelta().y);
        }
        fluidStep(fluid);
        fluidFadeDensity(fluid, w, h, GetFrameTime());

        BeginDrawing();
        ClearBackground(BLACK);
        //fluidRenderDensity(fluid, w, h, resolution);
        fluidRenderVelocity(fluid, w, h, resolution);

        char *t = malloc(16 * sizeof(char));
        sprintf(t, "%0.1f", 1.0f/GetFrameTime());
        DrawText(t, 5, 0, 15, RED);
        EndDrawing();
    }

    fluidFree(fluid);
    CloseWindow();
    return 0;
}
