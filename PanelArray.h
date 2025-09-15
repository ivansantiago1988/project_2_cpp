#ifndef PANELARRAY_H
#define PANELARRAY_H

#define MAX_ARR 64

#include <string>
#include "PanelArray.h"
#include "FlowPanel.h"
using namespace std;

class PanelArray{
  private:

    FlowPanel** ArrayofFlowPanelPointers;;
    int size;
  
  public:

    PanelArray();

    ~PanelArray();

    bool add(FlowPanel*);

    bool add(FlowPanel*, int index);

    FlowPanel* get(string id) const;
    
    FlowPanel* get(int index) const;

    FlowPanel* remove(string name);

    FlowPanel* remove(int index);

  
    int getSize() const;

    
   
};

#endif

