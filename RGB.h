#ifndef RGB_H
#define RGB_H

#include "defs.h"

class RGB {


    private:
        int r;
        int g;
        int b;

    public:
        RGB(int red, int green, int blue);

        RGB(CuColour colour);

        RGB();


        int getR() const;

        int getG() const;

        int getB() const;


        unsigned long getColour() const;

        void setColour(CuColour colour);



        // Static functions declarations
        static const RGB WHITE();
        static const RGB BLACK();
        static const RGB RED();
        static const RGB GREEN();
        static const RGB BLUE();


};

#endif