#include "vampire.h"
#include <string>

Vampire::Vampire(): Player(50,25,25) { }

std::string Vampire::name() const {
   return "Vampire";
}
