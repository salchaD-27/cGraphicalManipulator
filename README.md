# cGraphicalManipulator

**cGraphicalManipulator** is a C library that provides advanced image manipulation functionality using pixel grids. The library offers a range of image processing functions, including resizing, cropping, flipping, converting to black-and-white, and applying color transformations. Additionally, it allows for brightness, shadow, and color adjustments for custom image effects.

## Features

- **Image Manipulation**  
    - Resize and crop images.
    - Flip images horizontally and vertically.

- **Color Transformations**  
    - Convert images to black-and-white.
    - Isolate specific colors.
    - Remove or change specific colors in images.

- **Adjustments**  
    - Adjust brightness and shadow intensity.
    - Modify image warmth.

## Installation

To use the **cGraphicalManipulator** library, include the following header files and link the necessary libraries in your C project.
`#include "cGraphicalManipulator.h"`


## Quick Start

### 1. Convert an Image to a Pixel Grid
To load an image and convert it to a pixel grid, use the `imageToPixelGrid` function. You will need to pass the path of the image, along with pointers for width and height, to retrieve the pixel data.

    int width, height;
    RGB** pixelGrid = imageToPixelGrid("example.jpg", &width, &height);


### 2\. Apply a Transformation (e.g., Black-and-White)

To convert the image to black-and-white, use the bnw function.
`RGB** bnwGrid = bnw(pixelGrid, height, width);`


### 3\. Convert Back to an Image

Once you have manipulated the pixel grid, convert it back into an image and save it.
`pixelGridToImage(bnwGrid, width, height, "output.jpg");`

Available Functions
-------------------

### **Image Manipulation**

*   RGB\*\* imageToPixelGrid(const char\* imagePath, int\* width, int\* height)
    
    *   Load an image from a file and convert it to a pixel grid.
        
*   int pixelGridToImage(RGB\*\* pixelGrid, int width, int height, const char\* outputImagePath)
    
    *   Convert a pixel grid back to an image file and save it.
        
*   RGB\*\* resizeImage(RGB\*\* pixelGrid, int originalHeight, int originalWidth, int newHeight, int newWidth)
    
    *   Resize an image to the specified dimensions.
        
*   RGB\*\* cropImage(RGB\*\* pixelGrid, int originalHeight, int originalWidth, int top, int left, int right, int bottom, int\* croppedHeight, int\* croppedWidth)
    
    *   Crop an image based on the specified coordinates.
        
*   RGB\*\* flipHoriz(RGB\*\* pixelGrid, int height, int width)
    
    *   Flip an image horizontally.
        
*   RGB\*\* flipVert(RGB\*\* pixelGrid, int height, int width)
    
    *   Flip an image vertically.
        

### **Color Transformations**

*   RGB\*\* bnw(RGB\*\* pixelGrid, int height, int width)
    
    *   Convert the image to black-and-white.
        
*   RGB\*\* singleColorPop(RGB\*\* pixelGrid, int height, int width, unsigned char r, unsigned char g, unsigned char b, double threshold)
    
    *   Isolate a single color in the image.
        
*   RGB\*\* singleColorRemove(RGB\*\* pixelGrid, int height, int width, unsigned char r, unsigned char g, unsigned char b, double threshold)
    
    *   Remove a specific color from the image.
        
*   RGB\*\* changeColor(RGB\*\* pixelGrid, int height, int width, unsigned char r1, unsigned char g1, unsigned char b1, unsigned char r2, unsigned char g2, unsigned char b2, double threshold)
    
    *   Change one color to another color in the image.
        

### **Adjustments**

*   RGB\*\* adjustBrightness(RGB\*\* pixelGrid, int height, int width, double factor)
    
    *   Adjust the brightness of the image.
        
*   RGB\*\* adjustShadowIntensity(RGB\*\* pixelGrid, int height, int width, double factor)
    
    *   Adjust the intensity of the shadows in the image.
        
*   RGB\*\* adjustWarmth(RGB\*\* pixelGrid, int height, int width, double factor)
    
    *   Adjust the warmth of the image.
        

Tests
-----

The library includes basic functions for image manipulation, but you may want to test it with different images to ensure functionality. Unit tests can be added to the tests folder to validate the image processing functions.

Contributing
------------

Contributions are welcome! If you would like to contribute to the library, please fork the repository and submit a pull request with any bug fixes or improvements.

License
-------

This project is licensed under the MIT License. See the LICENSE file for details.

Author
------

Developed by **Dharyansh Achlas**. For any queries, feel free to contact [https://github.com/salchaD-27](https://github.com/salchaD-27).