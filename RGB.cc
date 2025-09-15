#include "RGB.h"

using namespace std;

// Constructor 1
RGB::RGB(int red, int green, int blue){
    this->r = red;          // Assign r
    this->g = green;        // Assign g
    this->b = blue;         // Assign b
}

// Constructor 2
RGB::RGB(CuColour colour){
    this->r = (colour >> 16) & 0xFF;          // Assign r
    this->g = (colour >> 8) & 0xFF;           // Assign g
    this->b = colour & 0xFF;                  // Assign b
}

// Constructor 3
RGB::RGB(){
    this->r = 0;           // Assign r
    this->g = 0;           // Assign g
    this->b = 0;           // Assign b
}


int RGB::getR() const {
    return r;
}

int RGB::getG() const {
    return g;
}

int RGB::getB() const {
    return b;
}


// get Cucolour funtion 
unsigned long RGB::getColour() const {

    return ((r & 0xFF) << 16) | ((g & 0xFF) << 8) | (b & 0xFF);

}

// set colour function 
void RGB::setColour(CuColour colour){

    this->r = (colour >> 16) & 0xFF;
    this->g = (colour >> 8) & 0xFF;
    this->b = colour & 0xFF;

}

// Static functions declarations
const RGB RGB::WHITE(){
    return RGB(255,255,255);
}
    

const RGB RGB::BLACK(){
    return RGB(0,0,0);
}

const RGB RGB::RED(){
    return RGB(255,0,0);
}

const RGB RGB::GREEN(){
    return RGB(0,255,0);
}

const RGB RGB::BLUE(){
    return RGB(0,0,255);
}