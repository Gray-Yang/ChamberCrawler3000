#include "warrior.h"
#include <string>

Warrior::Warrior(): Player(2020,135,136) { }

std::string Warrior::name() const {
   return "Warrior";
}
