#include "Cuwindow.h"
#include <iostream>
#include <unistd.h> // For usleep

using namespace std;

// Constructor 1
CuWindow::CuWindow( string name, int wd, int h, RGB backgrColour){
    this->name = name;                        // Assign name
    this->width = wd;                        // Assign width
    this->height = h;                       // Assign height
    this->backgroundColour = backgrColour;
    


    // Open a connection to the X server
    this->display = XOpenDisplay(nullptr);
    if (!this->display) {
        std::cerr << "Unable to open X display!" << std::endl;
        exit(1);
    }

    // Create a window
    int screen = DefaultScreen(this->display);
    this->window = XCreateSimpleWindow(this->display, RootWindow(this->display, screen), 0, 0, this->width, this->height, 1,
                                       BlackPixel(this->display, screen), WhitePixel(this->display, screen));

    // Set the window name
    XStoreName(this->display, this->window, this->name.c_str());

    // Select input events
    XSelectInput(this->display, this->window, ExposureMask | KeyPressMask);

    // Map (show) the window
    XMapWindow(this->display, this->window);

    XFlush(this->display);

    // Create a graphics context
    this->gc = XCreateGC(this->display, this->window, 0, nullptr);

    // Set the background color
        unsigned long bgColor = this->backgroundColour.getColour();
        XSetWindowBackground(this->display, this->window, bgColor);

}


// Destructor
CuWindow::~CuWindow() {

 // Free all FlowPanels
    for (int i = 0; i < arrayofFlowPanels.getSize(); i++) {
        delete arrayofFlowPanels.get(i);
    }

    if (this->gc) {
        XFreeGC(this->display, this->gc);
    }
    if (this->window) {
        XDestroyWindow(this->display, this->window);
    }
    if (this->display) {
        XCloseDisplay(this->display);
    }         // Close the X server connection
}


int CuWindow::getWidth() const { return width; }
int CuWindow::getHeight() const { return height; }
string CuWindow::getName()const { return name; }

void CuWindow::setWidth(int wd) {  width = wd; }
void CuWindow::setHeight(int h) { height = h; }
void CuWindow::setName(string& nameWindow) {name = nameWindow; }
void CuWindow::setBackground(RGB& color) { backgroundColour = color; }



bool CuWindow::addPanel(FlowPanel* b) {
    // Get panel properties
    int panelX = b->getX();
    int panelY = b->getY();
    int panelWidth = b->getWidth();
    int panelHeight = b->getHeight();

    // Check if panel fits within CuWindow boundaries
    if (panelX < 0 || panelY < 0 || panelX + panelWidth > width || panelY + panelHeight > height) {
        return false; // Out of bounds
    }

    
    // Check for overlap with existing flow panels
    for (int i = 0; i < arrayofFlowPanels.getSize(); i++) {
        if (arrayofFlowPanels.get(i)->overlaps(b)) {
            return false; // Overlap detected
        }
    }


    // Add panel if there is space available
    if (arrayofFlowPanels.getSize() < MAX_COMPONENTS) {
        arrayofFlowPanels.add(b);
        return true; // Successfully added
    }

    return false; // No space available
}


FlowPanel* CuWindow::removePanel(string Id) {
    for (int i = 0; i < arrayofFlowPanels.getSize(); ++i) {
        if (arrayofFlowPanels.get(i)->getId() == Id) {
            FlowPanel* panelToReturn = arrayofFlowPanels.get(i);
            arrayofFlowPanels.remove(i);
            return panelToReturn; // Return the removed panel pointer
        }
    }
    return nullptr; // Panel not found
}



FlowPanel* CuWindow::getPanel(string Id) const {
    for (int i = 0; i < arrayofFlowPanels.getSize(); ++i) {
        if (arrayofFlowPanels.get(i)->getId() == Id ) {
            return arrayofFlowPanels.get(i); // Return pointer to the panel
        }
    }
    return nullptr; // FlowPanel not found
}


void CuWindow::draw() {
    // Optional: Remove or adjust sleep delay
    usleep(100000);  

    // Fill the window with the background color
    XSetForeground(this->display, this->gc, this->backgroundColour.getColour());
    XFillRectangle(this->display, this->window, this->gc, 0, 0, this->width, this->height);

    
    // Draw all FlowPanels
    for (int i = 0; i < arrayofFlowPanels.getSize(); i++) {
        FlowPanel* panel = arrayofFlowPanels.get(i);
        if (!panel) continue;  // Ensure panel is not null

        
        // **Draw the FlowPanel (which will draw its own TextAreas)**
        panel->draw(this->display, this->window, this->gc);
    }

    // Flush the X server (Ensures all drawing is completed)
    XSync(this->display, False); // Alternative to XFlush
}


void CuWindow::print() const {
    cout<< "Window name " << name << endl;
    cout<< "Number of panels " << arrayofFlowPanels.getSize() << endl;

}

void CuWindow::printPanels() const {
    
    // Print FlowPanel information
    for (int i = 0; i < arrayofFlowPanels.getSize(); i++) {
        std::cout << "  Label: " << arrayofFlowPanels.get(i)->getId() << std::endl;
        std::cout << "  Position: " << arrayofFlowPanels.get(i)->getX() << ", " << arrayofFlowPanels.get(i)->getY() << std::endl;
        std::cout << "  Size: " << arrayofFlowPanels.get(i)->getWidth() << ", " << arrayofFlowPanels.get(i)->getHeight() << std::endl;
    } 

}

void CuWindow::printPanelTextAreas() const {
    std::cout << "TextAreas in Panels of Window: " << this->name << std::endl;
    for (int i = 0; i < arrayofFlowPanels.getSize(); ++i) {
        std::cout << "Panel " << i + 1 << " (" << arrayofFlowPanels.get(i)->getId() << "):" << std::endl;
        arrayofFlowPanels.get(i)->printTextAreas();
    }
}