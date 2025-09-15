#include <iostream>
#include <string>
#include "TAArray.h"

using namespace std;

TAArray::TAArray(){
    size = 0;
    elements = new TextArea*[MAX_ARR];
}

TAArray::~TAArray(){
    delete [] elements;
}

bool TAArray::add(TextArea* ta){

    if (size >= MAX_ARR)return false;

    /*// Check for overlap with textareas
    for (int i = 0; i < size; i++) {
        if (elements[i]->overlaps(*ta)) {
            return false; // Overlap detected
        }
    }*/

    TextArea** newArr  = new TextArea*[size + 1];

    for(int i = 0; i<size; i++){
        newArr[i]= elements[i];
    }
    
    newArr[size] = ta;

    delete[] elements;
    elements = newArr;
    size++;
    return true;
}

bool TAArray::add(TextArea* ta, int index){

  // Check for valid index and array capacity
    if (size >= MAX_ARR || index < 0 || index > size) return false;

    // Shift elements to the right to make space for the new element
    for (int i = size; i > index; --i) {
        elements[i] = elements[i - 1];
    }

    // Insert the new element at the specified index
    elements[index] = ta;

    // Increase the size of the array
    size++;

    return true;
}

TextArea* TAArray::get(string id) const {
    for (int i = 0; i < size; ++i){
        if (elements[i]->getId() == id){
            return elements[i];
        }
    }
    return NULL;
}

TextArea* TAArray::get(int index) const {
    if (index < 0 || index >= size) return NULL;
    return elements[index];
}


TextArea* TAArray::remove(string id)  {
    
    int index = 0;
    //we want to find the index of the element to remove
    while (elements[index]->getId()!= id && index < size){
        ++index;
    }

    // If index is out of bounds, element was not found
    if (index >= size) {
        return nullptr;
    }

    
    return remove(index);

}

TextArea* TAArray::remove(int index)  {

    //did we fall off the end of the TAArray?
    if (index<0 || index >=size) return nullptr;

    //we have found what we wanted to remove,
    //assign the output value
      TextArea* elmRemove = elements[index];

    //copy everything after index left one position
    while (index < size - 1){
        elements[index] = elements[index + 1];
        ++index;
    }
    size--;
    return elmRemove;

}



 int TAArray::getSize() const {

    return size;
 };