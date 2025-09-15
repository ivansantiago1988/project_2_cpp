#ifndef TAARRAY_H
#define TAARRAY_H

#define MAX_ARR 64

#include <string>
#include "TextArea.h"
using namespace std;

class TAArray{
  private:

    TextArea** elements;
    int size;
  
  public:

    TAArray();
   
    ~TAArray();

    bool add(TextArea*);

    bool add(TextArea*, int index);

    TextArea* get(string id) const;
    
    TextArea* get(int index) const;

    TextArea* remove(string name);

    TextArea* remove(int index);

   
    int getSize() const;

    
   
};

#endif

