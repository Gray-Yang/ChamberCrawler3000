#ifndef PLAYER_H
#define PLAYER_H

#include "character.h"
#include <string>

class Enemy;

class Player : public Character {
    public:
    Player(int HP, int Atk, int Def);
    virtual std::string name() const override;
};

#endif
