#include "troll.h"
#include <string>


Troll::Troll(): Player(120,25,15) {}

std::string Troll::name() const {
    return "Troll";
}
