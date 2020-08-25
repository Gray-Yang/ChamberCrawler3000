#ifndef __WARRIOR_H__
#define __WARRIOR_H__

#include "player.h"
#include <string>

class Warrior : public Player{
public:
    Warrior(); // constructor
    std::string name() const override;
};

#endif 
