#include "raylib.h"
#include <math.h>

double degreesToRadians(double degrees) {
    return degrees * (PI / 180.0);
}
double sind(double x) {
    return sin(degreesToRadians(x));
}
double cosd(double x) {
    return cos(degreesToRadians(x));
}

void drawPixel(int x, int y, float res, Color color) {
    if (res > 1) return;
    int size = 1 / res;

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            DrawPixel((x*size)+j, (y*size)+i, color);
        }
    }
}

Color dir2col(double x, double y) {
    double len = sqrt(x*x + y*y);
    double nx = x/len, ny = y/len;

    double r = 256 * cosd(nx);
    double g = 256 * cosd(nx + 120);
    double b = 256 * cosd(nx - 120);
    return CLITERAL(Color){r, g, b, 255};
}
