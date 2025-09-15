#include <iostream>
using namespace std;
#include "FlowPanel.h"
#include "TextArea.h"


FlowPanel::FlowPanel(int x, int y, int width, int height, const string& id, int xgapi, int ygapi){

    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->id = id;
    this->xgap = xgapi;
    this->ygap = ygapi;

}

FlowPanel::FlowPanel(Rectangle& rect, const string& id, int xgapi, int ygapi){

    this->x = rect.x;
    this->y = rect.y;
    this->width = rect.width;
    this->height = rect.height;
    this->id = id;
    this->xgap = xgapi;
    this->ygap = ygapi;

}


// Deep copy constructor
FlowPanel::FlowPanel(const FlowPanel& other) {
    this->x = other.x;
    this->y = other.y;
    this->width = other.width;
    this->height = other.height;
    this->id = other.id;
    this->xgap = other.xgap;
    this->ygap = other.ygap;

  
    // Manually deep copy each TextArea
    for (int i = 0; i < other.textAreas.getSize(); i++) {
        TextArea* original = other.textAreas.get(i);
        if (original) {
            // Create a new TextArea with the same attributes
            TextArea* copy = new TextArea();
            copy->setX(original->getX());
            copy->setY(original->getY());
            copy->setWidth(original->getWidth());
            copy->setHeight(original->getHeight());
            copy->setText(original->getText());

            // Add the new copy to the copied FlowPanel
            this->textAreas.add(copy);
        }
    }
}


// Destructor (Deletes all contained TextAreas)
FlowPanel::~FlowPanel() {
    for (int i = 0; i < textAreas.getSize(); i++) {
        delete textAreas.get(i);  // Free memory for each TextArea
    }
}


string FlowPanel::getId() const { 
    
    return id; 
    
 }

int FlowPanel::getWidth() const {

    return width;
}

int FlowPanel::getHeight() const {
    
    return height;
}

int FlowPanel::getX() const {
    
    return x;
}

int FlowPanel::getY() const {
    
    return y;
}

bool FlowPanel::overlaps(FlowPanel* p) const {

    
    return !(x + width <= p->getX() || p->getX() + p->getWidth() <= x ||
             y + height <= p->getY() || p->getY() + p->getHeight() <= y);
             
}     

void FlowPanel::print() const{

    // Print Panel information
     cout << "id: " << id << endl;
     cout << "Prefered Location " << x << ", " << y << endl;
     cout << "Size: " << width << ", " << height << endl;
      
}


void FlowPanel::printTextAreas() const {

   cout << endl << endl << "Text Areas:" << endl;
   for (int i=0; i<textAreas.getSize(); ++i)
   textAreas.get(i)->print();
   cout << endl;
      
}

int FlowPanel::getTextAreacount() const {

    return textAreas.getSize();

}

// Add a TextArea to the panel (FlowPanel takes ownership)
void FlowPanel::addTextArea(TextArea* ta) {
     
     textAreas.add(ta);  // Add to TAArray
      
}

// Get a TextArea by index (FlowPanel retains ownership)
TextArea* FlowPanel::getTextArea(int index) const {
    
    return textAreas.get(index);
}

// Remove a TextArea from FlowPanel (Transfers ownership to caller)
TextArea* FlowPanel::removeTextArea(string s) {
    
    return textAreas.remove(s); // Caller is now responsible for deletion
}

// Remove a TextArea from FlowPanel (Transfers ownership to caller)
TextArea* FlowPanel::removeTextArea(int n) {
    
    return textAreas.remove(n); // Caller is now responsible for deletion
}


void FlowPanel::draw(Display *display, Window win, GC gc) {
    // Draw FlowPanel boundary (for debugging)
    XSetForeground(display, gc, BlackPixel(display, 0));
    XDrawRectangle(display, win, gc, x, y, width, height);

    // **Flow Layout Positioning**
    int startX = x + xgap;  // Initial x position inside panel
    int startY = y + ygap;  // Initial y position inside panel
    int currentX = startX;
    int currentY = startY;
    int maxWidth = x + width; // Right boundary
    int maxHeight = y + height; // Bottom boundary
    int rowHeight = 0;  // Keeps track of the tallest element in the row
    bool allFit = True;

    for (int i = 0; i < textAreas.getSize(); ++i) {
    
        TextArea* element = textAreas.get(i);
        
        if (!element) continue; // Skip null elements

        int elemWidth = element->getWidth();
        int elemHeight = element->getHeight();

        // **Ensure the element fits within FlowPanel**
        if (currentX + elemWidth > maxWidth) {
            // Move to the next row
            currentX = startX;
            currentY += rowHeight + ygap;
            rowHeight = 0;
        }

        // **Check if the new row goes out of FlowPanel boundaries**
        if (currentY + elemHeight > maxHeight) {
            std::cout << "Skipping TextArea " << element->getText()
                      << " because it exceeds panel height." << std::endl;
            allFit = false;  // Mark that not all elements fit
            break;  // Stop processing further TextAreas
        }

        // **Update row height (keep track of the tallest element in this row)**
        rowHeight = std::max(rowHeight, elemHeight);

        // **Set Position RELATIVE to FlowPanel**
        element->setX(currentX - x);
        element->setY(currentY - y);


        // **Draw the TextArea**
        element->draw(display, win, gc, x, y);

        
        // **Move right for the next element**
        currentX += elemWidth + xgap;
    }

    // **Ensure all drawing operations are flushed**
    XFlush(display); // Ensures all drawing commands are executed immediately
}

int FlowPanel::isTextAreaOutOfBounds() {
    for (int i = 0; i < textAreas.getSize(); i++) {
        TextArea* ta = textAreas.get(i);

        if (ta->getX() + ta->getWidth() > x + width ||
            ta->getY() + ta->getHeight() > y + height) {
            std::cout << "TextArea at index " << i << " is out of FlowPanel bounds!\n";
            return i;
        }
    }
    return -1;
}