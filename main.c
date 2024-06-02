#include "raylib.h"
#include "src/include/utils.h"

const int screenWidth = 800;
const int screenHeight = 450;
const float resolution = 0.5f;

void update();

int main(void)
{
    InitWindow(screenWidth, screenHeight, "Fluid Simulation");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        update();
    }

    CloseWindow();
    return 0;
}

void update()
{
    BeginDrawing();

    ClearBackground(RAYWHITE);

    drawPixel(0, 0, 0.1f, PINK);

    EndDrawing();
}
