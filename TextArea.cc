#include "TextArea.h"
#include <iostream>

using namespace std;

// Constructor 1: Initializes member variables with x, y, width, height, id, label, fill, and border
TextArea::TextArea(int x, int y, int width, int height, const std::string& id, const std::string& label,
                   const RGB& fill, const RGB& border) {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->text = label;
    this->id = id;
    this->fill = fill;
    this->border = border;
}

// Constructor 2: Initializes member variables using a Rectangle object, id, label, fill, and border
TextArea::TextArea(const Rectangle& rect, const std::string& id, const std::string& label,
                   const RGB& fill, const RGB& border) {
    this->x = rect.x;
    this->y = rect.y;
    this->width = rect.width;
    this->height = rect.height;
    this->text = label;
    this->id = id;
    this->fill = fill;
    this->border = border;
}

// Constructor 3
TextArea::TextArea(){
    this->x = 0;          // Assign x coordinate
    this->y = 0;          // Assign y coordinate
    this->width = 100;    // Assign width
    this->height = 50;
    this->text = "Default";
    this->id = "1";
    this->fill = RGB(0, 128, 255);
    this->border = RGB(0, 0, 0);
}

    /*// Copy constructor for testing purposes ONLY.
    // It copies all member variables but sets 'text' to "DUPLICATE".
    // Do not include this copy constructor in your final assignment.
TextArea::TextArea(const TextArea &other) {
        x = other.x;
        y = other.y;
        width = other.width;
        height = other.height;
        text = "DUPLICATE"; // Instead of copying other.text, set to "DUPLICATE"
        id = other.id;
        fill = other.fill;
        border = other.border;
    }*/


// getters
int TextArea::getX() const { return x; }
int TextArea::getY() const { return y; }
int TextArea::getWidth() const { return width; }
int TextArea::getHeight() const { return height; }
std::string TextArea::getText() const { return text; }
std::string TextArea::getId() const { return id; }
RGB TextArea::getFill() const { return fill; }
RGB TextArea::getBorder() const { return border; }

// setters
void TextArea::setX(int newX) { x = newX; }
void TextArea::setY(int newY) { y = newY; }
void TextArea::setWidth(int newWidth) { width = newWidth; }
void TextArea::setHeight(int newHeight) { height = newHeight; }
void TextArea::setText(const std::string& newText) { text = newText; }
void TextArea::setId(const std::string& newId) { id = newId; }
void TextArea::setFill(const RGB& newFill) { fill = newFill; }
void TextArea::setBorder(const RGB& newBorder) { border = newBorder; }


bool TextArea::overlaps( const TextArea& ta) const {

     // Create Rectangle objects for both TextAreas
    Rectangle rect1(x, y, width, height);
    Rectangle rect2(ta.x, ta.y, ta.width, ta.height);

    // Use the Rectangle overlaps function
    return rect1.overlaps(rect2);

    }


void TextArea::print() const {

    // Print Text Area information
     cout << "id: " << id << endl;
     cout << "Prefered Location " << x << ", " << y << endl;
     cout << "Size: " << width << ", " << height << endl;
     cout << "Text: " << text << endl;

    }


void TextArea::draw(Display *display, Window win, GC gc, int x1, int y1) {
    
    int absX = x1 + x; // Calculate absolute x position
    int absY = y1 + y; // Calculate absolute y position

    // Draw the filled rectangle (background of TextArea)
    XSetForeground(display, gc,  fill.getColour()); // Set color to white
    XFillRectangle(display, win, gc, absX, absY, width, height);

    // Set border color to black and draw rectangle outline
    XSetForeground(display, gc, border.getColour());
    XDrawRectangle(display, win, gc, absX, absY, width, height);

    // Load font (Using "fixed" as a fallback if the default fails)
    XFontStruct *font_info = XLoadQueryFont(display, "fixed");
    if (!font_info) {
        cerr << "Error: Could not load font 'fixed'. Text will not be displayed." << endl;
        return;  // Skip text drawing if font fails to load
    }
    
    XSetFont(display, gc, font_info->fid);
    XSetForeground(display, gc, BlackPixel(display, DefaultScreen(display)));

    // Get font metrics
    int char_width = font_info->max_bounds.width; // Approx character width
    int char_height = font_info->max_bounds.ascent + font_info->max_bounds.descent; // Line height

    int chars_per_line = width / char_width; // How many characters fit per line
    int max_lines = height / char_height; // Maximum lines that fit

    int text_len = text.length();
    int line_count = 0;

    // Draw text line by line, wrapping if necessary
    for (int i = 0; i < text_len && line_count < max_lines; i += chars_per_line) {
        std::string line = text.substr(i, chars_per_line);
        XDrawString(display, win, gc, absX + 1, absY + (line_count + 1) * char_height, line.c_str(), line.length());
        line_count++;
    }

    // Free the loaded font
    XFreeFont(display, font_info);
    XFlush(display);

 }