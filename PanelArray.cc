#include <iostream>
using namespace std;
#include "PanelArray.h"



PanelArray::PanelArray(){
    size = 0;
    ArrayofFlowPanelPointers = new FlowPanel*[MAX_ARR];
}

PanelArray::~PanelArray(){
    delete [] ArrayofFlowPanelPointers;
}

bool PanelArray::add(FlowPanel* pa){
    if (size >= MAX_ARR)return false;

    FlowPanel** newArr  = new FlowPanel*[size + 1];

    for(int i = 0; i<size; i++){
        newArr[i]= ArrayofFlowPanelPointers[i];
    }
    
    newArr[size] = pa;

    delete[] ArrayofFlowPanelPointers;
    ArrayofFlowPanelPointers = newArr;
    size++;
    return true;
}


bool PanelArray::add(FlowPanel* pa, int index){

  // Check for valid index and array capacity
    if (size >= MAX_ARR || index < 0 || index > size) return false;

    // Shift elements to the right to make space for the new element
    for (int i = size; i > index; --i) {
        ArrayofFlowPanelPointers[i] = ArrayofFlowPanelPointers[i - 1];
    }

    // Insert the new element at the specified index
    ArrayofFlowPanelPointers[index] = pa;

    // Increase the size of the array
    size++;

    return true;
}


FlowPanel* PanelArray::get(string id) const {
    for (int i = 0; i < size; ++i){
        if (ArrayofFlowPanelPointers[i]->getId() == id){
            return ArrayofFlowPanelPointers[i];
        }
    }
    return NULL;
}

FlowPanel* PanelArray::get(int index) const {
    if (index < 0 || index >= size) return NULL;
    return ArrayofFlowPanelPointers[index];
}


FlowPanel* PanelArray::remove(string id) {
    int index = 0;

    // First check index before accessing the array
    while (index < size && ArrayofFlowPanelPointers[index]->getId() != id) {
        ++index;
    }

    // If index is out of bounds, element was not found
    if (index >= size) {
        return nullptr;
    }

    return remove(index);
}

FlowPanel* PanelArray::remove(int index)  {

    //did we fall off the end of the TAArray?
    if (index<0 || index >=size) return nullptr;

    //we have found what we wanted to remove,
    //assign the output value
      FlowPanel* elmRemove = ArrayofFlowPanelPointers[index];

    //copy everything after index left one position
    while (index < size - 1){
        ArrayofFlowPanelPointers[index] = ArrayofFlowPanelPointers[index + 1];
        ++index;
    }
    size--;
    return elmRemove;

}


int PanelArray::getSize() const {

      return size;
      
      }


