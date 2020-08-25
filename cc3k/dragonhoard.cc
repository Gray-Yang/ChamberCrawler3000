#include "dragonhoard.h"
#include "Gold.h"

dragonhoard::dragonhoard(int id, std::shared_ptr<Character> d):
 Gold{6},id{id},d{d}{ }

int dragonhoard::getid(){
    return id;
}
std::shared_ptr<Character> dragonhoard::getdragon(){
    return d;
}

