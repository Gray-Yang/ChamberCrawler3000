#include "player.h"
using namespace std;



Player::Player(int HP, int Atk, int Def):Character(HP,Atk,Def){} // ctor


std::string Player::name() const {return "Player";}
