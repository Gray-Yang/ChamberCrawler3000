#include "character.h"
#include <cmath>
using namespace std;

Character::Character(double hp, double atk, double def) :
HP{hp}, Atk{atk},Def{def}, HP_lim{hp}, Atk_lim{atk}, Def_lim{def},gold{0}{} // ctor

Character::~Character(){ }


double Character::get_HP() const{
    return HP;
}

double Character::get_Atk() const {
    return Atk;
}

double Character::get_Def() const {
    return Def;
}

double Character::get_HP_lim() const{
    return HP_lim;
}

double Character::get_Atk_lim() const {
    return Atk_lim;
}

double Character::get_Def_lim() const {
    return Def_lim;
}
void Character::add_gold(int value){ 
    gold += value;
}

int Character::get_gold() const { return gold;}
void Character::set_gold(int value){ gold = value; }

void Character::change_HP(double value){
    HP += value; 
    if (HP <= 0){
        HP = 0;
    }else if (HP >= HP_lim && this->name() != "Vampire"){
        HP = HP_lim;
    }
}

void Character::change_Atk(double value){
    Atk += value; 
    if (Atk <= 0){
        Atk = 0;
    }
}

void Character::change_Def(double value){
    Def += value; 
    if (Def <= 0){
        Def = 0;
    }
}


bool Character::dead(){
    return HP <= 0;
}

void Character::set_hp(double value){ HP = value;}

