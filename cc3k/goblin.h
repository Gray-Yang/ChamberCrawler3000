#ifndef __GOBLIN_H__
#define __GOBLIN_H__

#include "player.h"
#include <string>

class Goblin : public Player{
public:
    Goblin(); // constructor
    std::string name() const override;
};

#endif 
