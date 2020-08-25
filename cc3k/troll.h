#ifndef __TROLL_H__
#define __TROLL_H__

#include "player.h"
#include <string>

class Troll : public Player{
public:
    Troll(); // constructor
    std::string name() const override;
};

#endif 
