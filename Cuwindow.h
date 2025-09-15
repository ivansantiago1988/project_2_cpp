#ifndef CUWINDOW_H
#define CUWINDOW_H

#include "defs.h"
#include <string>
#include "RGB.h"
#include "FlowPanel.h"
#include "PanelArray.h"
#include <X11/Xlib.h>
using namespace std;

class CuWindow{

private:
    int width;
    int height;
    string name;
    PanelArray arrayofFlowPanels;
    RGB backgroundColour;
    Display* display;                 // Connection to the X server
    Window window;                    // XID of the window
    GC gc;   


public:

    CuWindow(string name, int wd, int h, RGB backgrColour);


    // Destructor
    ~CuWindow();

     
    int getWidth() const;
    int getHeight() const;
    string getName() const;



    void setWidth(int wd);
    void setHeight(int h);
    void setName(string& nameWindow);
    void setBackground(RGB& color);

    bool addPanel(FlowPanel* b);

    FlowPanel* removePanel(string Id);

    FlowPanel* getPanel(string Id) const;

    void draw();

    void print() const;

    void printPanels() const;

    void printPanelTextAreas() const;

};



#endif




