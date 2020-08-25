#ifndef __Dragon_H_
#define __Dragon_H_


#include "Enemy.h"

class Gold;

class Dragon : public Enemy{
    public:
    int hoardrow;
    int hoardcol;
    Dragon(int hoardrow, int hoardcol);
};

#endif
