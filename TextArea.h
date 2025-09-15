#ifndef TEXTAREA_H
#define TEXTAREA_H

#include <string>
#include <X11/Xlib.h>
#include "RGB.h"


class TextArea {
private:
    // Member variables
    int x, y;                // Coordinates of the TextArea
    int width, height;       // Dimensions of the TextArea
    std::string text;        // Text displayed on the TextArea
    std::string id;          // Unique identifier
    RGB fill;                // Fill color
    RGB border;              // Border color



public:
    // Constructors 1
    TextArea(int x, int y, int width, int height, const std::string& id, const std::string& label,
             const RGB& fill = RGB(255, 255, 255), const RGB& border = RGB(0, 0, 0));

    // Constructors 2
    TextArea(const Rectangle& rect, const std::string& id, const std::string& label,
             const RGB& fill = RGB(255, 255, 255), const RGB& border = RGB(0, 0, 0));

    // Constructor 3
    TextArea();


    // Copy constructor 
   // TextArea(const TextArea &other);

    // getters
    int getX() const;
    int getY() const;
    int getWidth() const;
    int getHeight() const;
    std::string getText() const;
    std::string getId() const;
    RGB getFill() const;
    RGB getBorder() const;

    //setters
    void setX(int newX);
    void setY(int newY);
    void setWidth(int newWidth);
    void setHeight(int newHeight);
    void setText(const std::string& newText);
    void setId(const std::string& newId);
    void setFill(const RGB& newFill);
    void setBorder(const RGB& newBorder);   


    bool overlaps(const TextArea& ta) const;

    void print() const;

    void draw(Display *display, Window win, GC gc, int x1, int y1);

};

#endif