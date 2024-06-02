#ifndef FLUIDS_UTILS_H
#define FLUIDS_UTILS_H

#include "raylib.h"
void drawPixel(int x, int y, float res, Color color);
Color dir2col(double x, double y);
double degreesToRadians(double degrees);
double cosd(double x);
double sind(double x);
#endif //FLUIDS_UTILS_H
