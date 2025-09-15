#ifndef FLOWPANEL_H
#define FLOWPANEL_H

#define MAX_ARR 64

#include <string>
#include "TAArray.h"
#include <X11/Xlib.h>
using namespace std;

class FlowPanel{
  private:
    string id;
    int x; 
    int y;
    int width;
    int height;
    int xgap;
    int ygap;
    TAArray textAreas;
    
  
  public:

    FlowPanel(int x, int y, int width, int height, const string& id, int xgap = 10, int ygap = 10);

    FlowPanel(Rectangle& rect, const string& id, int xgap = 10, int ygap = 10);
    
    
    // Deep copy constructor
    FlowPanel(const FlowPanel& other);

    // destructor 
    ~FlowPanel();

    
     string getId() const;
     int getWidth()const;
     int getHeight() const;

     int getX() const;
     int getY() const;

     bool overlaps(FlowPanel* p) const;

     
     void print() const;

     void printTextAreas() const;

     int getTextAreacount() const;

     // Add a TextArea to the panel (FlowPanel takes ownership)
    void addTextArea(TextArea* ta);

    // Get a TextArea by index (FlowPanel retains ownership)
    TextArea* getTextArea(int index) const;

    // Remove a TextArea from FlowPanel (Transfers ownership to caller)
    TextArea* removeTextArea(string s);

    // Remove a TextArea from FlowPanel (Transfers ownership to caller)
    TextArea* removeTextArea(int n);


    void draw(Display *display, Window win, GC gc);

    int isTextAreaOutOfBounds();
   
};

#endif

