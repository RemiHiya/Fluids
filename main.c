#include "raylib.h"

const int screenWidth = 800;
const int screenHeight = 450;

void UpdateDrawFrame(void);

int main(void)
{
    InitWindow(screenWidth, screenHeight, "Fluid Simulation");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        UpdateDrawFrame();
    }

    CloseWindow();
    return 0;
}

void UpdateDrawFrame(void)
{
    BeginDrawing();

    ClearBackground(RAYWHITE);

    DrawPixel(10, 10, PINK);

    EndDrawing();
}
