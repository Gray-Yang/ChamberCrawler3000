#include "drow.h"
#include <string>


Drow::Drow(): Player(150,25,15) {}

std::string Drow::name() const {
    return "Drow";
}
