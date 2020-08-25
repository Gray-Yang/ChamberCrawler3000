#ifndef __SHADE_H__
#define __SHADE_H__

#include "player.h"
#include <string>

class Shade : public Player{
public:
    Shade(); // constructor
    std::string name() const override;
};

#endif 
