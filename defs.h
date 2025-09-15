#include <iostream>
#ifndef DEFS_H
#define DEFS_H
#define MAX_COMPONENTS 256

#define CuColour unsigned long


struct Rectangle{
    int x;
    int y;
    int width;
    int height;


 // Constructor: takes x, y, width, and height.
    Rectangle(int x, int y, int width, int height) {
        this->x = x;
        this->y = y;
        this->width = width;
        this->height = height;
    }


    bool overlaps(const Rectangle& rect) const { 

     return !(x < rect.x + rect.width && x + width > rect.x &&
                    y < rect.y + rect.height && y + height > rect.y);

    
    }
};



#endif