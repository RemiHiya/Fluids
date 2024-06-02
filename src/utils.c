#include "raylib.h"

void drawPixel(int x, int y, float res, Color color) {
    if (res > 1) return;
    int size = 1 / res;

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            DrawPixel(x+j, y+i, color);
        }
    }
}
