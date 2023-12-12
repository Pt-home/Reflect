#include <emscripten.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <stdbool.h>

typedef unsigned char byte;
typedef unsigned int uint32;
typedef unsigned long long uint64;
typedef float float32;

void left2right(unsigned char* imageBuffer, int width, int height, int horizontal) {
    int pixelSize = 4;
    int verticalLine = width * horizontal / 100;

    unsigned char* tempBuffer = malloc(width * height * pixelSize);

    if (horizontal == 50) {
        for(int y = 0; y < height; y++) {
            for(int x = 0; x < width; x++) {
                if (x < verticalLine) {
                    memcpy(&tempBuffer[(y * width + x) * pixelSize],
                           &imageBuffer[(y * width + x) * pixelSize],
                           pixelSize);
                } else {
                    memcpy(&tempBuffer[(y * width + x) * pixelSize],
                           &imageBuffer[(y * width + (2 * verticalLine - x - 1)) * pixelSize],
                           pixelSize);
                }
            }
        }
    }
    else if (horizontal > 50) {
        int reflectionStart = 2 * verticalLine - width;

        for(int y = 0; y < height; y++) {
            for(int x = 0; x < width; x++) {
                if (x >= verticalLine) {
                    memcpy(&tempBuffer[(y * width + x) * pixelSize],
                           &imageBuffer[(y * width + (2 * verticalLine - x - 1)) * pixelSize],
                           pixelSize);
                } else {
                    memcpy(&tempBuffer[(y * width + x) * pixelSize],
                           &imageBuffer[(y * width + x) * pixelSize],
                           pixelSize);
                }
            }
        }
    }
    else if (horizontal < 50) {
        int reflectionStart = width - verticalLine;
        int reflectionEnd = 2 * verticalLine;

        // Reflect the left side of the image to the right side of the new buffer.
        for(int y = 0; y < height; y++) {
            for(int x = verticalLine; x < width; x++) {
                memcpy(&tempBuffer[(y * width + x) * pixelSize],
                       &imageBuffer[(y * width + (width - x - 1)) * pixelSize],
                       pixelSize);
            }
        }

        // Copy the left side of the image to the left side of the new buffer.
        for(int y = 0; y < height; y++) {
            for(int x = 0; x < verticalLine; x++) {
                memcpy(&tempBuffer[(y * width + x) * pixelSize],
                       &tempBuffer[(y * width + (reflectionEnd - x - 1)) * pixelSize],
                       pixelSize);
            }
        }
    }

    memcpy(imageBuffer, tempBuffer, width * height * pixelSize);
    free(tempBuffer);
}

void right2left(unsigned char* imageBuffer, int width, int height, int horizontal) {
    int pixelSize = 4;
    int verticalLine = width * horizontal / 100;

    unsigned char* tempBuffer = malloc(width * height * pixelSize);

    if (horizontal == 50) {
        for(int y = 0; y < height; y++) {
            for(int x = 0; x < width; x++) {
                if (x >= verticalLine) {
                    memcpy(&tempBuffer[(y * width + x) * pixelSize],
                           &imageBuffer[(y * width + x) * pixelSize],
                           pixelSize);
                } else {
                    memcpy(&tempBuffer[(y * width + x) * pixelSize],
                           &imageBuffer[(y * width + (2 * verticalLine - x - 1)) * pixelSize],
                           pixelSize);
                }
            }
        }
    }
    else if (horizontal < 50) {
        int reflectionStart = 2 * verticalLine - width;

        for(int y = 0; y < height; y++) {
            for(int x = 0; x < width; x++) {
                if (x < verticalLine) {
                    memcpy(&tempBuffer[(y * width + x) * pixelSize],
                           &imageBuffer[(y * width + (2 * verticalLine - x - 1)) * pixelSize],
                           pixelSize);
                } else {
                    memcpy(&tempBuffer[(y * width + x) * pixelSize],
                           &imageBuffer[(y * width + x) * pixelSize],
                           pixelSize);
                }
            }
        }
    }
    else if (horizontal > 50) {
        int reflectionStart = horizontal;
        int reflectionEnd = 100;

        // Reflect the right side of the image to the left side of the new buffer.
        for(int y = 0; y < height; y++) {
            for(int x = 0; x < verticalLine; x++) {
                memcpy(&tempBuffer[(y * width + x) * pixelSize],
                       &imageBuffer[(y * width + (width - x - 1 + reflectionStart)) * pixelSize],
                       pixelSize);
            }
        }

        // Reflect part of the new buffer to its right side.
        for(int y = 0; y < height; y++) {
            for(int x = verticalLine; x < width; x++) {
                memcpy(&tempBuffer[(y * width + x) * pixelSize],
                       &tempBuffer[(y * width + (2 * verticalLine - x - 1)) * pixelSize],
                       pixelSize);
            }
        }
    }

    memcpy(imageBuffer, tempBuffer, width * height * pixelSize);
    free(tempBuffer);
}



void top2bottom(unsigned char* imageBuffer, int width, int height, int vertical) {
    int pixelSize = 4;
    int horizontalLine = height * vertical / 100;

    unsigned char* tempBuffer = malloc(width * height * pixelSize);

    if (vertical == 50) {
        for(int y = 0; y < height; y++) {
            for(int x = 0; x < width; x++) {
                if (y < horizontalLine) {
                    memcpy(&tempBuffer[(y * width + x) * pixelSize],
                           &imageBuffer[(y * width + x) * pixelSize],
                           pixelSize);
                } else {
                    memcpy(&tempBuffer[(y * width + x) * pixelSize],
                           &imageBuffer[((2 * horizontalLine - y - 1) * width + x) * pixelSize],
                           pixelSize);
                }
            }
        }
    }
    else if (vertical > 50) {
        int reflectionStart = 2 * horizontalLine - height;

        for(int y = 0; y < height; y++) {
            for(int x = 0; x < width; x++) {
                if (y >= horizontalLine) {
                    memcpy(&tempBuffer[(y * width + x) * pixelSize],
                           &imageBuffer[((2 * horizontalLine - y - 1) * width + x) * pixelSize],
                           pixelSize);
                } else {
                    memcpy(&tempBuffer[(y * width + x) * pixelSize],
                           &imageBuffer[(y * width + x) * pixelSize],
                           pixelSize);
                }
            }
        }
    }
    else if (vertical < 50) {
        int reflectionStart = height - horizontalLine;
        int reflectionEnd = 2 * horizontalLine;

        // Reflect the top side of the image to the bottom side of the new buffer.
        for(int y = horizontalLine; y < height; y++) {
            for(int x = 0; x < width; x++) {
                memcpy(&tempBuffer[(y * width + x) * pixelSize],
                       &imageBuffer[((height - y - 1) * width + x) * pixelSize],
                       pixelSize);
            }
        }

        // Copy the top side of the image to the top side of the new buffer.
        for(int y = 0; y < horizontalLine; y++) {
            for(int x = 0; x < width; x++) {
                memcpy(&tempBuffer[(y * width + x) * pixelSize],
                       &tempBuffer[((reflectionEnd - y - 1) * width + x) * pixelSize],
                       pixelSize);
            }
        }
    }

    memcpy(imageBuffer, tempBuffer, width * height * pixelSize);
    free(tempBuffer);
}

void bottom2top(unsigned char* imageBuffer, int width, int height, int vertical) {
    int pixelSize = 4;
    int horizontalLine = height * vertical / 100;

    unsigned char* tempBuffer = malloc(width * height * pixelSize);

    if (vertical == 50) {
        for(int y = 0; y < height; y++) {
            for(int x = 0; x < width; x++) {
                if (y >= horizontalLine) {
                    memcpy(&tempBuffer[(y * width + x) * pixelSize],
                           &imageBuffer[(y * width + x) * pixelSize],
                           pixelSize);
                } else {
                    memcpy(&tempBuffer[(y * width + x) * pixelSize],
                           &imageBuffer[((2 * horizontalLine - y - 1) * width + x) * pixelSize],
                           pixelSize);
                }
            }
        }
    }
    else if (vertical < 50) {
        int reflectionStart = 2 * horizontalLine - height;

        for(int y = 0; y < height; y++) {
            for(int x = 0; x < width; x++) {
                if (y < horizontalLine) {
                    memcpy(&tempBuffer[(y * width + x) * pixelSize],
                           &imageBuffer[((2 * horizontalLine - y - 1) * width + x) * pixelSize],
                           pixelSize);
                } else {
                    memcpy(&tempBuffer[(y * width + x) * pixelSize],
                           &imageBuffer[(y * width + x) * pixelSize],
                           pixelSize);
                }
            }
        }
    }
    else if (vertical > 50) {
        int reflectionStart = height * (vertical - 50) / 100;
        int reflectionEnd = height * vertical / 100;

        // Reflect the bottom part of the image to the top side of the new buffer.
        for(int y = 0; y < horizontalLine; y++) {
            for(int x = 0; x < width; x++) {
                memcpy(&tempBuffer[(y * width + x) * pixelSize],
                       &imageBuffer[((height - y - 1) * width + x) * pixelSize],
                       pixelSize);
            }
        }

        // Copy the bottom side of the image to the bottom side of the new buffer.
        for(int y = horizontalLine; y < height; y++) {
            for(int x = 0; x < width; x++) {
                memcpy(&tempBuffer[(y * width + x) * pixelSize],
                       &tempBuffer[((2 * reflectionEnd - y - 1) * width + x) * pixelSize],
                       pixelSize);
            }
        }
    }

    memcpy(imageBuffer, tempBuffer, width * height * pixelSize);
    free(tempBuffer);
}


///////////////////////////////////////////////////////////////

void flipHorizontal(unsigned char* imageBuffer, int width, int height) {
    int pixelSize = 4; // Assuming RGB + alpha channel image

    for(int y = 0; y < height; y++) {
        for(int x = 0; x < width / 2; x++) {
            int leftIdx = (y * width + x) * pixelSize;
            int rightIdx = (y * width + (width - 1 - x)) * pixelSize;
            for(int i = 0; i < pixelSize; i++) {
                unsigned char temp = imageBuffer[leftIdx + i];
                imageBuffer[leftIdx + i] = imageBuffer[rightIdx + i];
                imageBuffer[rightIdx + i] = temp;
            }
        }
    }
}

void flipVertical(unsigned char* imageBuffer, int width, int height) {
    int pixelSize = 4; // Assuming RGB + alpha channel image

    for(int y = 0; y < height / 2; y++) {
        for(int x = 0; x < width; x++) {
            int topIdx = (y * width + x) * pixelSize;
            int bottomIdx = ((height - 1 - y) * width + x) * pixelSize;
            for(int i = 0; i < pixelSize; i++) {
                unsigned char temp = imageBuffer[topIdx + i];
                imageBuffer[topIdx + i] = imageBuffer[bottomIdx + i];
                imageBuffer[bottomIdx + i] = temp;
            }
        }
    }
}

void rotate180(unsigned char* buffer, int width, int height) {
    int pixelSize = 4; // Assuming RGB + alpha channel image
    for (int y = 0; y < height / 2; ++y) {
        for (int x = 0; x < width; ++x) {
            int idx1 = (y * width + x) * pixelSize;
            int idx2 = ((height - y - 1) * width + (width - x - 1)) * pixelSize;
            for (int i = 0; i < pixelSize; ++i) {
                unsigned char tmp = buffer[idx1 + i];
                buffer[idx1 + i] = buffer[idx2 + i];
                buffer[idx2 + i] = tmp;
            }
        }
    }
}

void full_lt2rb(unsigned char* imageBuffer, int width, int height) {
    int pixelSize = 4; // Assuming RGB + alpha channel image

    unsigned char* newImageBuffer1 = malloc(width * height * pixelSize);
    unsigned char* newImageBuffer2 = malloc(width * height * pixelSize);

    // Copy original image to two new buffers
    memcpy(newImageBuffer1, imageBuffer, width * height * pixelSize);
    memcpy(newImageBuffer2, imageBuffer, width * height * pixelSize);

    // Rotate second buffer
    rotate180(newImageBuffer2, width, height);

    // List of buffers to modify
    unsigned char* buffers[2] = {newImageBuffer1, newImageBuffer2};

    // Perform transformation on both buffers
    for(int b = 0; b < 2; b++) {
        unsigned char* buffer = buffers[b];

        float ratio = (float) height / width;
        int dx = 0;  // horizontal shift, fixed at 0 as diagonal is fixed at 50
        int dy = 0;  // vertical shift, fixed at 0 as diagonal is fixed at 50

        // calculate the rectangle size
        int rectWidth = width - dx;
        int rectHeight = height - dy;

        // Perform the transformation and interpolation on the buffer
        for(int y = 0; y < rectHeight; y++) {
            for(int x = 0; x < rectWidth; x++) {
                if(rectHeight - 1 - y < ratio * x) {
                    int i = (y * rectWidth + x) * pixelSize;
                    buffer[i]   = 0;
                    buffer[i+1] = 0;
                    buffer[i+2] = 0;
                    buffer[i+3] = 0;
                }
            }
        }

        for(int y = 0; y < rectHeight; y++) {
            for(int x = 0; x < rectWidth; x++) {
                if(rectHeight - 1 - y > ratio * x + 1) {
                    float newX = (float) x / rectWidth;
                    float newY = (float) y / rectHeight;
                    float refX = 1.0f - newY;
                    float refY = 1.0f - newX;
                    int destX = round(refX * rectWidth);
                    int destY = round(refY * rectHeight);
                    destX = destX < rectWidth ? destX : rectWidth - 1;
                    destY = destY < rectHeight ? destY : rectHeight - 1;
                    int srcIdx = (y * rectWidth + x) * pixelSize;
                    int destIdx = (destY * rectWidth + destX) * pixelSize;
                    memcpy(buffer + destIdx, buffer + srcIdx, pixelSize);
                }
            }
        }

        // interpolation
        if (rectHeight > rectWidth) {
            for(int y = 0; y < rectHeight; y++) {
                for(int x = 0; x < rectWidth; x++) {
                    int i = (y * rectWidth + x) * pixelSize;
                    if(buffer[i+3] == 0) {
                        int up = y;
                        int down = y;
                        while (up > 0 && buffer[(up * rectWidth + x) * pixelSize + 3] == 0) up--;
                        while (down < rectHeight - 1 && buffer[(down * rectWidth + x) * pixelSize + 3] == 0) down++;
                        unsigned char* upColor = buffer + (up * rectWidth + x) * pixelSize;
                        unsigned char* downColor = buffer + (down * rectWidth + x) * pixelSize;
                        for(int k = 0; k < pixelSize; k++) {
                            buffer[i + k] = (upColor[k] + downColor[k]) / 2;
                        }
                    }
                }
            }
        } else {
            for(int y = 0; y < rectHeight; y++) {
                for(int x = 0; x < rectWidth; x++) {
                    int i = (y * rectWidth + x) * pixelSize;
                    if(buffer[i+3] == 0) {
                        int left = x;
                        int right = x;
                        while (left > 0 && buffer[(y * rectWidth + left) * pixelSize + 3] == 0) left--;
                        while (right < rectWidth - 1 && buffer[(y * rectWidth + right) * pixelSize + 3] == 0) right++;
                        unsigned char* leftColor = buffer + (y * rectWidth + left) * pixelSize;
                        unsigned char* rightColor = buffer + (y * rectWidth + right) * pixelSize;
                        for(int k = 0; k < pixelSize; k++) {
                            buffer[i + k] = (leftColor[k] + rightColor[k]) / 2;
                        }
                    }
                }
            }
        }
    }

    // Rotate the second buffer back
    rotate180(newImageBuffer2, width, height);

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int srcIdx1 = (y * width + x) * pixelSize;
            int srcIdx2 = (y * width + x) * pixelSize;
            int destIdx = (y * width + x) * pixelSize;
            float ratio = (float) height / width;
            if (height - 1 - y > ratio * x)
                memcpy(imageBuffer + destIdx, newImageBuffer2 + srcIdx2, pixelSize);
            else 
                memcpy(imageBuffer + destIdx, newImageBuffer1 + srcIdx1, pixelSize);
        }
    }

    // Free the memory of the new images
    free(newImageBuffer1);
    free(newImageBuffer2);
}

void lt2rb(unsigned char* imageBuffer, int width, int height, int diagonal) {
    int pixelSize = 4; // Assuming RGB + alpha channel image
	
	bool wasRepeat = false;
	if (diagonal<50) {
		full_lt2rb(imageBuffer,  width, height);
		rotate180(imageBuffer,   width,   height);
		diagonal = 100-diagonal;
		wasRepeat = true;
	}

    float ratio = (float) height / width;
    int dx = (int) ((diagonal - 50) / 50.0 * width);  // horizontal shift
    int dy = (int) ((diagonal - 50) / 50.0 * height);  // vertical shift

    // calculate the rectangle size
    int rectWidth = width - dx;
    int rectHeight = height - dy;

    unsigned char* newImageBuffer = malloc(rectWidth * rectHeight * pixelSize); // allocate memory for the new image

    // copy the part of the original image to the new one
    for (int y = dy; y < height; y++) {
        for (int x = dx; x < width; x++) {
            int srcIdx = (y * width + x) * pixelSize;
            int destIdx = ((y - dy) * rectWidth + (x - dx)) * pixelSize;
            memcpy(newImageBuffer + destIdx, imageBuffer + srcIdx, pixelSize);
        }
    }

    // apply the transformation and interpolation on the new image
    for(int y = 0; y < rectHeight; y++) {
        for(int x = 0; x < rectWidth; x++) {
            if(rectHeight - 1 - y < ratio * x) {
                int i = (y * rectWidth + x) * pixelSize;
                newImageBuffer[i]   = 0;
                newImageBuffer[i+1] = 0;
                newImageBuffer[i+2] = 0;
                newImageBuffer[i+3] = 0;
            }
        }
    }

    for(int y = 0; y < rectHeight; y++) {
        for(int x = 0; x < rectWidth; x++) {
            if(rectHeight - 1 - y > ratio * x + 1) {
                float newX = (float) x / rectWidth;
                float newY = (float) y / rectHeight;
                float refX = 1.0f - newY;
                float refY = 1.0f - newX;
                int destX = round(refX * rectWidth);
                int destY = round(refY * rectHeight);
                destX = destX < rectWidth ? destX : rectWidth - 1;
                destY = destY < rectHeight ? destY : rectHeight - 1;
                int srcIdx = (y * rectWidth + x) * pixelSize;
                int destIdx = (destY * rectWidth + destX) * pixelSize;
                memcpy(newImageBuffer + destIdx, newImageBuffer + srcIdx, pixelSize);
            }
        }
    }

    // interpolation
    if (rectHeight > rectWidth) {
        for(int y = 0; y < rectHeight; y++) {
            for(int x = 0; x < rectWidth; x++) {
                int i = (y * rectWidth + x) * pixelSize;
                if(newImageBuffer[i+3] == 0) {
                    int up = y;
                    int down = y;
                    while (up > 0 && newImageBuffer[(up * rectWidth + x) * pixelSize + 3] == 0) up--;
                    while (down < rectHeight - 1 && newImageBuffer[(down * rectWidth + x) * pixelSize + 3] == 0) down++;
                    unsigned char* upColor = newImageBuffer + (up * rectWidth + x) * pixelSize;
                    unsigned char* downColor = newImageBuffer + (down * rectWidth + x) * pixelSize;
                    for(int k = 0; k < pixelSize; k++) {
                        newImageBuffer[i + k] = (upColor[k] + downColor[k]) / 2;
                    }
                }
            }
        }
    } else {
        for(int y = 0; y < rectHeight; y++) {
            for(int x = 0; x < rectWidth; x++) {
                int i = (y * rectWidth + x) * pixelSize;
                if(newImageBuffer[i+3] == 0) {
                    int left = x;
                    int right = x;
                    while (left > 0 && newImageBuffer[(y * rectWidth + left) * pixelSize + 3] == 0) left--;
                    while (right < rectWidth - 1 && newImageBuffer[(y * rectWidth + right) * pixelSize + 3] == 0) right++;
                    unsigned char* leftColor = newImageBuffer + (y * rectWidth + left) * pixelSize;
                    unsigned char* rightColor = newImageBuffer + (y * rectWidth + right) * pixelSize;
                    for(int k = 0; k < pixelSize; k++) {
                        newImageBuffer[i + k] = (leftColor[k] + rightColor[k]) / 2;
                    }
                }
            }
        }
    }

    // replace the part of the original image with the transformed one
    for (int y = dy; y < height; y++) {
        for (int x = dx; x < width; x++) {
            int srcIdx = ((y - dy) * rectWidth + (x - dx)) * pixelSize;
            int destIdx = (y * width + x) * pixelSize;
            memcpy(imageBuffer + destIdx, newImageBuffer + srcIdx, pixelSize);
        }
    }

    // free the memory of the new image
    free(newImageBuffer);
	
	if (wasRepeat) {
		rotate180(imageBuffer, width, height);
	}
	
}

void rb2lt(unsigned char* imageBuffer, int width, int height, int diagonal) {
    // 1) Rotate the image 180 degrees
    rotate180(imageBuffer, width, height);

    // 2) Update diagonal
    diagonal = 100 - diagonal;

    // 3) Apply the lt2rb filter
    lt2rb(imageBuffer, width, height, diagonal);

    // 4) Rotate the image 180 degrees again
    rotate180(imageBuffer, width, height);
}

void lb2rt(unsigned char* imageBuffer, int width, int height, int diagonal) {
    // 1)
    flipHorizontal(imageBuffer, width, height);

    // 2) Update diagonal
    diagonal = 100 - diagonal;

    // 3) Apply the rb2lt filter
    rb2lt(imageBuffer, width, height, diagonal);

    // 4) 
    flipHorizontal(imageBuffer, width, height);
}

void rt2lb(unsigned char* imageBuffer, int width, int height, int diagonal) {
    // 1)
    flipHorizontal(imageBuffer, width, height);

    // 2) Update diagonal
    diagonal = 100 - diagonal;

    // 3) Apply the lt2rb filter
    lt2rb(imageBuffer, width, height, diagonal);

    // 4) 
    flipHorizontal(imageBuffer, width, height);
}

EMSCRIPTEN_KEEPALIVE
byte* wasmAlloc(uint32 width, uint32 height) {
  return malloc(width * height * 4);
}

EMSCRIPTEN_KEEPALIVE
void wasmFree(byte* p) {
  free(p);
}

EMSCRIPTEN_KEEPALIVE
void wasmProcess(byte* inputData, uint32 size, int width, int height, int horizontal, int vertical, int diagonal, const char* typeReflect) {
  if (strcmp(typeReflect, "L2R") == 0) {    
	left2right(inputData, width, height, horizontal);	
  }
  if (strcmp(typeReflect, "R2L") == 0) {    
	right2left(inputData, width, height, horizontal);	
  }
  if (strcmp(typeReflect, "T2B") == 0) {    
	top2bottom(inputData, width, height, vertical);	
  }
  if (strcmp(typeReflect, "B2T") == 0) {    
	bottom2top(inputData, width, height, vertical);	
  }
  if (strcmp(typeReflect, "Q1") == 0) {
    right2left(inputData, width, height, horizontal);	  
	top2bottom(inputData, width, height, vertical);		
  }
  if (strcmp(typeReflect, "Q2") == 0) {    
	left2right(inputData, width, height, horizontal);
    top2bottom(inputData, width, height, vertical);		
  }
  if (strcmp(typeReflect, "Q3") == 0) {    
	left2right(inputData, width, height, horizontal);
    bottom2top(inputData, width, height, vertical);		
  }
  if (strcmp(typeReflect, "Q4") == 0) {
    right2left(inputData, width, height, horizontal);		  
	bottom2top(inputData, width, height, vertical);		
  }
  if (strcmp(typeReflect, "LT2RB") == 0) {  	
	lt2rb(inputData, width, height, diagonal);	
  }
  if (strcmp(typeReflect, "RB2LT") == 0) {    
	rb2lt(inputData, width, height, diagonal);	
  }
  if (strcmp(typeReflect, "LB2RT") == 0) {    
	lb2rt(inputData, width, height, diagonal);	
  }
  if (strcmp(typeReflect, "RT2LB") == 0) {    
	rt2lb(inputData, width, height, diagonal);	
  }  
}



