#include "unit.h"

unit::unit(): symbol{'-'}{}

char unit::get_symbol(){
    return symbol;
}

void unit::set_symbol(char tmp){
    symbol = tmp;
}

bool unit::get_is_moved(){ return is_moved; }

void unit::set_is_moved(bool move){ is_moved = move;}

char unit::get_oldsymbol(){ return oldsymbol;}

void unit::set_oldsymbol(char c){ oldsymbol = c;}


std::shared_ptr<Character> unit::get_ch(){ return ch;}

void unit::set_ch(std::shared_ptr<Character> ptr){ ch = ptr; }

std::shared_ptr<Gold> unit::get_it(){ return it;}

void unit::set_it(std::shared_ptr<Gold> ptr){ it = ptr;}

