#ifndef ENEMY_H
#define ENEMY_H

#include "character.h"
#include <string>

class Player;
class Enemy: public Character{
    protected:
    public:
    Enemy(int hp,int atk,int def);
    virtual std::string name() const override;
};

#endif
