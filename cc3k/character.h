#ifndef CHARACTER_H
#define CHARACTER_H

#include "unit.h"

#include <string>
class Character{
    protected:
    double HP;
    double Atk;
    double Def;
    double HP_lim;
    double Atk_lim;
    double Def_lim;
    double gold;
    public:
    Character(double hp, double atk, double def);
    double get_HP() const; // return current HP
    double get_Atk() const; // return current attack
    double get_Def() const; // return current defence
    double get_HP_lim() const; // return current HP
    double get_Atk_lim() const; // return current attack
    double get_Def_lim() const; // return current defence
    virtual std::string name() const = 0;
    void add_gold(int value);
    int get_gold() const; // return current gold value
    void set_gold(int value) ;
    void change_HP(double value);
    void change_Atk(double value);
    void change_Def(double value);
    void set_hp(double value);
    bool dead();
    
    virtual ~Character();
};

#endif
