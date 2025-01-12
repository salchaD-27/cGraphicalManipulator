#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "stb_image.h"
#include "stb_image_write.h"
#ifndef CGRAPHICALMANIPULATOR_H
#define CGRAPHICALMANIPULATOR_H

typedef struct {
    unsigned char r, g, b;
} RGB;

// Function declarations
RGB** imageToPixelGrid(const char* imagePath, int* width, int* height);
int pixelGridToImage(RGB** pixelGrid, int width, int height, const char* outputImagePath);
RGB** resizeImage(RGB** pixelGrid, int originalHeight, int originalWidth, int newHeight, int newWidth);
RGB** cropImage(RGB** pixelGrid, int originalHeight, int originalWidth, int top, int left, int right, int bottom, int* croppedHeight, int* croppedWidth);
RGB** flipHoriz(RGB** pixelGrid, int height, int width);
RGB** flipVert(RGB** pixelGrid, int height, int width);
RGB** bnw(RGB** pixelGrid, int height, int width);
RGB** singleColorPop(RGB** pixelGrid, int height, int width, unsigned char r, unsigned char g, unsigned char b, double threshold);
RGB** singleColorRemove(RGB** pixelGrid, int height, int width, unsigned char r, unsigned char g, unsigned char b, double threshold);
RGB** changeColor(RGB** pixelGrid, int height, int width, unsigned char r1, unsigned char g1, unsigned char b1, 
                  unsigned char r2, unsigned char g2, unsigned char b2, double threshold);
RGB** adjustShadowIntensity(RGB** pixelGrid, int height, int width, double factor);
RGB** adjustBrightness(RGB** pixelGrid, int height, int width, double factor);
RGB** adjustBlackPoint(RGB** pixelGrid, int height, int width, double factor);
RGB** adjustWarmth(RGB** pixelGrid, int height, int width, double factor);

#endif