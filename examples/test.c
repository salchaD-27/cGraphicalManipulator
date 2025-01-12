#include <stdio.h>
#include <stdlib.h>
#include "cGraphicalManipulator.h"

int main(){
    int width, height;
    RGB** pixelGrid = imageToPixelGrid("testInputImage.jpg", &width, &height);
    pixelGridToImage(pixelGrid, width, height, "outputImage.jpg");
    pixelGridToImage(resizeImage(pixelGrid, height, width, 100, 100), width, height, "output_resizeImage.jpg");
    pixelGridToImage(flipHoriz(pixelGrid, height, width), width, height, "output_flipHoriz.jpg");
    pixelGridToImage(flipVert(pixelGrid, height, width), width, height, "output_flipVert.jpg");
    pixelGridToImage(bnw(pixelGrid, height, width), width, height, "output_bnw.jpg");
    pixelGridToImage(singleColorPop(pixelGrid, height, width, 0, 255, 0, 254), width, height, "output_singleColorPop.jpg");
    pixelGridToImage(singleColorRemove(pixelGrid, height, width, 0, 255, 0, 254), width, height, "output_singleColorRemove.jpg");
    pixelGridToImage(changeColor(pixelGrid, height, width, 0, 255, 0, 255, 0, 0, 200), width, height, "output_changeColor.jpg");
    pixelGridToImage(adjustShadowIntensity(pixelGrid, height, width, 1.2), width, height, "output_adjustShadowIntensity.jpg");
    pixelGridToImage(adjustBrightness(pixelGrid, height, width, 1.2), width, height, "output_adjustBrightness.jpg");
    pixelGridToImage(adjustBlackPoint(pixelGrid, height, width, 1.2), width, height, "output_adjustBlackPoint.jpg");
    pixelGridToImage(adjustWarmth(pixelGrid, height, width, 1.2), width, height, "output_adjustWarmth.jpg");
}