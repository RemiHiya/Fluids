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
    DrawRectangle(x*size, y*size, size, size, color);
}

Color dir2col(double x, double y) {
    double len = sqrt(x*x + y*y);
    double nx = x / len, ny = y / len;

    double angle = atan2(ny, nx);

    double hue = angle * (180.0 / M_PI) + 90;
    if (hue < 0) hue += 360;

    double c = 1.0;
    double x_value = 1.0 - fabs(fmod(hue / 60.0, 2) - 1.0);
    double m = 0;

    double r_prime, g_prime, b_prime;
    if (hue >= 0 && hue < 60) {
        r_prime = c; g_prime = x_value; b_prime = 0;
    } else if (hue >= 60 && hue < 120) {
        r_prime = x_value; g_prime = c; b_prime = 0;
    } else if (hue >= 120 && hue < 180) {
        r_prime = 0; g_prime = c; b_prime = x_value;
    } else if (hue >= 180 && hue < 240) {
        r_prime = 0; g_prime = x_value; b_prime = c;
    } else if (hue >= 240 && hue < 300) {
        r_prime = x_value; g_prime = 0; b_prime = c;
    } else {
        r_prime = c; g_prime = 0; b_prime = x_value;
    }

    int r = (int)((r_prime + m) * 255);
    int g = (int)((g_prime + m) * 255);
    int b = (int)((b_prime + m) * 255);

    return CLITERAL(Color){r, g, b, (int) len};
}