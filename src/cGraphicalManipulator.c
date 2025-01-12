#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

typedef struct {
    unsigned char r, g, b;
} RGB;

void freePixelGrid(RGB** pixelGrid, int height) {
    for (int y = 0; y < height; y++) {
        free(pixelGrid[y]);
    }
    free(pixelGrid);
}
double colorDistance(RGB c1, RGB c2) {
    return sqrt(pow(c1.r - c2.r, 2) + pow(c1.g - c2.g, 2) + pow(c1.b - c2.b, 2));
}

// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// -----------------------------------------------------------------------------------------------------------------------------------------------------------

RGB** imageToPixelGrid(const char* imagePath, int* width, int* height) {
    int nChannels;
    unsigned char* data = stbi_load(imagePath, width, height, &nChannels, 3);
    if (data == NULL) {
        fprintf(stderr, "Error loading image: %s\n", imagePath);
        return NULL;
    }
    RGB** pixelGrid = (RGB**)malloc(*height * sizeof(RGB*));
    if (pixelGrid == NULL) {
        fprintf(stderr, "Error allocating memory for pixel grid.\n");
        stbi_image_free(data);
        return NULL;
    }
    for (int y = 0; y < *height; y++) {
        pixelGrid[y] = (RGB*)malloc(*width * sizeof(RGB));
        for (int x = 0; x < *width; x++) {
            int index = (y * *width + x) * 3;
            pixelGrid[y][x].r = data[index];     // Red component
            pixelGrid[y][x].g = data[index + 1]; // Green component
            pixelGrid[y][x].b = data[index + 2]; // Blue component
        }
    }
    stbi_image_free(data);
    return pixelGrid;
}

int pixelGridToImage(RGB** pixelGrid, int width, int height, const char* outputImagePath) {
    unsigned char* data = (unsigned char*)malloc(width * height * 3 * sizeof(unsigned char));
    if (data == NULL) {
        fprintf(stderr, "Error allocating memory for image data.\n");
        return 1; // Error
    }
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int index = (y * width + x) * 3;
            data[index] = pixelGrid[y][x].r;     // Red component
            data[index + 1] = pixelGrid[y][x].g; // Green component
            data[index + 2] = pixelGrid[y][x].b; // Blue component
        }
    }
    int success = stbi_write_jpg(outputImagePath, width, height, 3, data, 100);
    free(data);
    return success ? 0 : 1;
}

// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// -----------------------------------------------------------------------------------------------------------------------------------------------------------

RGB** resizeImage(RGB** pixelGrid, int originalHeight, int originalWidth, int newHeight, int newWidth) {
    RGB** resizedPixelGrid = (RGB**)malloc(newHeight * sizeof(RGB*));
    for (int i = 0; i < newHeight; i++) {
        resizedPixelGrid[i] = (RGB*)malloc(newWidth * sizeof(RGB));
    }
    float x_ratio = (float)(originalWidth) / newWidth;
    float y_ratio = (float)(originalHeight) / newHeight;
    for (int y = 0; y < newHeight; y++) {
        for (int x = 0; x < newWidth; x++){
            int origX = (int)(x * x_ratio);
            int origY = (int)(y * y_ratio);
            resizedPixelGrid[y][x] = pixelGrid[origY][origX];
        }
    }
    return resizedPixelGrid;
}

RGB** cropImage(RGB** pixelGrid, int originalHeight, int originalWidth, int top, int left, int right, int bottom, int* croppedHeight, int* croppedWidth) {
    *croppedHeight = originalHeight - top - bottom;
    *croppedWidth = originalWidth - left - right;
    RGB** croppedPixelGrid = (RGB**)malloc(*croppedHeight * sizeof(RGB*));
    for (int i = 0; i < *croppedHeight; i++) {
        croppedPixelGrid[i] = (RGB*)malloc(*croppedWidth * sizeof(RGB));
    }
    for (int y = 0; y < *croppedHeight; y++) {
        for (int x = 0; x < *croppedWidth; x++) {
            croppedPixelGrid[y][x] = pixelGrid[top + y][left + x];
        }
    }
    return croppedPixelGrid;
}

// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// -----------------------------------------------------------------------------------------------------------------------------------------------------------

RGB** flipHoriz(RGB** pixelGrid, int height, int width) {
    RGB** flippedPixelGrid = (RGB**)malloc(height * sizeof(RGB*));
    for (int i = 0; i < height; i++) {
        flippedPixelGrid[i] = (RGB*)malloc(width * sizeof(RGB));
    }
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            flippedPixelGrid[y][x] = pixelGrid[y][width - x - 1];
        }
    }
    return flippedPixelGrid;
}

RGB** flipVert(RGB** pixelGrid, int height, int width) {
    RGB** flippedPixelGrid = (RGB**)malloc(height * sizeof(RGB*));
    for (int i = 0; i < height; i++) {
        flippedPixelGrid[i] = (RGB*)malloc(width * sizeof(RGB));
    }
    for (int y = 0; y < height; y++) {
        flippedPixelGrid[y] = pixelGrid[height - y - 1];
    }
    return flippedPixelGrid;
}

// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// -----------------------------------------------------------------------------------------------------------------------------------------------------------

RGB** bnw(RGB** pixelGrid, int height, int width) {
    RGB** bnwGrid = (RGB**)malloc(height * sizeof(RGB*));
    for (int i = 0; i < height; i++) {
        bnwGrid[i] = (RGB*)malloc(width * sizeof(RGB));
    }
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int average = (pixelGrid[y][x].r + pixelGrid[y][x].g + pixelGrid[y][x].b) / 3;
            bnwGrid[y][x].r = bnwGrid[y][x].g = bnwGrid[y][x].b = average;
        }
    }
    return bnwGrid;
}

RGB** singleColorPop(RGB** pixelGrid, int height, int width, unsigned char r, unsigned char g, unsigned char b, double threshold) {
    RGB target = {r, g, b};
    RGB** popGrid = (RGB**)malloc(height * sizeof(RGB*));
    for (int i = 0; i < height; i++) {
        popGrid[i] = (RGB*)malloc(width * sizeof(RGB));
        for (int j = 0; j < width; j++) {
            double distance = colorDistance(pixelGrid[i][j], target);
            if (distance < threshold) {
                popGrid[i][j] = pixelGrid[i][j];
            } else {
                unsigned char avg = (pixelGrid[i][j].r + pixelGrid[i][j].g + pixelGrid[i][j].b) / 3;
                popGrid[i][j] = (RGB){avg, avg, avg};
            }
        }
    }
    return popGrid;
}

RGB** singleColorRemove(RGB** pixelGrid, int height, int width, unsigned char r, unsigned char g, unsigned char b, double threshold) {
    RGB target = {r, g, b};
    RGB** removeGrid = (RGB**)malloc(height * sizeof(RGB*));
    for (int i = 0; i < height; i++) {
        removeGrid[i] = (RGB*)malloc(width * sizeof(RGB));
        for (int j = 0; j < width; j++) {
            double distance = colorDistance(pixelGrid[i][j], target);
            if (distance < threshold) {
                unsigned char avg = (pixelGrid[i][j].r + pixelGrid[i][j].g + pixelGrid[i][j].b) / 3;
                removeGrid[i][j] = (RGB){avg, avg, avg}; 
            } else {
                removeGrid[i][j] = pixelGrid[i][j]; 
            }
        }
    }
    return removeGrid;
}

RGB** changeColor(RGB** pixelGrid, int height, int width, unsigned char r1, unsigned char g1, unsigned char b1, 
                  unsigned char r2, unsigned char g2, unsigned char b2, double threshold) {
    RGB target = {r1, g1, b1};
    RGB replacement = {r2, g2, b2};
    RGB** modifiedGrid = (RGB**)malloc(height * sizeof(RGB*));
    for (int i = 0; i < height; i++) {
        modifiedGrid[i] = (RGB*)malloc(width * sizeof(RGB));
        for (int j = 0; j < width; j++) {
            double distance = colorDistance(pixelGrid[i][j], target);
            if (distance <= threshold) {
                modifiedGrid[i][j] = replacement;
            } else {
                modifiedGrid[i][j] = pixelGrid[i][j];
            }
        }
    }
    return modifiedGrid;
}

// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// -----------------------------------------------------------------------------------------------------------------------------------------------------------

RGB** adjustShadowIntensity(RGB** pixelGrid, int height, int width, double factor) {
    RGB** adjustedGrid = (RGB**)malloc(height * sizeof(RGB*));
    for (int i = 0; i < height; i++) {
        adjustedGrid[i] = (RGB*)malloc(width * sizeof(RGB));
        for (int j = 0; j < width; j++) {
            RGB pixel = pixelGrid[i][j];
            adjustedGrid[i][j].r = (pixel.r < 128) ? (int)(pixel.r * factor) : pixel.r;
            adjustedGrid[i][j].g = (pixel.g < 128) ? (int)(pixel.g * factor) : pixel.g;
            adjustedGrid[i][j].b = (pixel.b < 128) ? (int)(pixel.b * factor) : pixel.b;

            adjustedGrid[i][j].r = adjustedGrid[i][j].r > 255 ? 255 : (adjustedGrid[i][j].r < 0 ? 0 : adjustedGrid[i][j].r);
            adjustedGrid[i][j].g = adjustedGrid[i][j].g > 255 ? 255 : (adjustedGrid[i][j].g < 0 ? 0 : adjustedGrid[i][j].g);
            adjustedGrid[i][j].b = adjustedGrid[i][j].b > 255 ? 255 : (adjustedGrid[i][j].b < 0 ? 0 : adjustedGrid[i][j].b);
        }
    }
    return adjustedGrid;
}

RGB** adjustBlackPoint(RGB** pixelGrid, int height, int width, int level) {
    RGB** adjustedGrid = (RGB**)malloc(height * sizeof(RGB*));
    for (int i = 0; i < height; i++) {
        adjustedGrid[i] = (RGB*)malloc(width * sizeof(RGB));
        for (int j = 0; j < width; j++) {
            RGB pixel = pixelGrid[i][j];
            adjustedGrid[i][j].r = (pixel.r - level) < 0 ? 0 : (pixel.r - level);
            adjustedGrid[i][j].g = (pixel.g - level) < 0 ? 0 : (pixel.g - level);
            adjustedGrid[i][j].b = (pixel.b - level) < 0 ? 0 : (pixel.b - level);
        }
    }
    return adjustedGrid;
}

RGB** adjustBrightness(RGB** pixelGrid, int height, int width, double brightnessFactor) {
    RGB** adjustedGrid = (RGB**)malloc(height * sizeof(RGB*));
    for (int i = 0; i < height; i++) {
        adjustedGrid[i] = (RGB*)malloc(width * sizeof(RGB));
        for (int j = 0; j < width; j++) {
            RGB pixel = pixelGrid[i][j];
            adjustedGrid[i][j].r = (int)(pixel.r * brightnessFactor);
            adjustedGrid[i][j].g = (int)(pixel.g * brightnessFactor);
            adjustedGrid[i][j].b = (int)(pixel.b * brightnessFactor);

            adjustedGrid[i][j].r = adjustedGrid[i][j].r > 255 ? 255 : (adjustedGrid[i][j].r < 0 ? 0 : adjustedGrid[i][j].r);
            adjustedGrid[i][j].g = adjustedGrid[i][j].g > 255 ? 255 : (adjustedGrid[i][j].g < 0 ? 0 : adjustedGrid[i][j].g);
            adjustedGrid[i][j].b = adjustedGrid[i][j].b > 255 ? 255 : (adjustedGrid[i][j].b < 0 ? 0 : adjustedGrid[i][j].b);
        }
    }
    return adjustedGrid;
}

RGB** adjustWarmth(RGB** pixelGrid, int height, int width, double warmthFactor) {
    RGB** adjustedGrid = (RGB**)malloc(height * sizeof(RGB*));
    for (int i = 0; i < height; i++) {
        adjustedGrid[i] = (RGB*)malloc(width * sizeof(RGB));
        for (int j = 0; j < width; j++) {
            RGB pixel = pixelGrid[i][j];
            adjustedGrid[i][j].r = (int)(pixel.r * (1 + warmthFactor));
            adjustedGrid[i][j].g = (int)(pixel.g * (1 + warmthFactor));
            adjustedGrid[i][j].b = (int)(pixel.b * (1 - warmthFactor));

            adjustedGrid[i][j].r = adjustedGrid[i][j].r > 255 ? 255 : (adjustedGrid[i][j].r < 0 ? 0 : adjustedGrid[i][j].r);
            adjustedGrid[i][j].g = adjustedGrid[i][j].g > 255 ? 255 : (adjustedGrid[i][j].g < 0 ? 0 : adjustedGrid[i][j].g);
            adjustedGrid[i][j].b = adjustedGrid[i][j].b > 255 ? 255 : (adjustedGrid[i][j].b < 0 ? 0 : adjustedGrid[i][j].b);
        }
    }
    return adjustedGrid;
}

// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
