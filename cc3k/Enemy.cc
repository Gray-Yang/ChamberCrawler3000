#include "Enemy.h"

Enemy::Enemy(int hp, int atk,int def): 
Character(hp,atk,def) { }

std::string Enemy::name() const {
    return "Enemy";
}
