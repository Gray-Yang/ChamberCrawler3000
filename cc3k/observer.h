#ifndef __observer__
#define __observer__

#include <iostream>
#include <vector>
#include "controller.h"

class observer{
    public:
    virtual void notify(int col, int row, char symbol) = 0;
    virtual ~observer();
};


#endif
