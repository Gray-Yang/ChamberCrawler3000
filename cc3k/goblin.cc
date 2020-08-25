#include "goblin.h"
#include <string>


Goblin::Goblin(): Player(50,25,25) {}

std::string Goblin::name() const {
    return "Goblin";
}
