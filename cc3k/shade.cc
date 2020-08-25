#include "shade.h"
#include <string>
using namespace std;


Shade::Shade(): Player(125,25,25) {}

std::string Shade::name() const {
  return "Shade";
}
