#ifndef __unit__
#define __unit__
#include <memory>

class Character;

class Gold;

class unit {
    char symbol;
    bool is_moved;
    char oldsymbol;
    std::shared_ptr<Character> ch;
    std::shared_ptr<Gold> it;
    public:
    unit();
    void set_symbol(char tmp);
    char get_symbol();
    bool get_is_moved();
    void set_is_moved(bool move);
    char get_oldsymbol();
    void set_oldsymbol(char c);
    std::shared_ptr<Character> get_ch();
    void set_ch(std::shared_ptr<Character>);
    std::shared_ptr<Gold> get_it();
    void set_it(std::shared_ptr<Gold> ptr);
};


#endif
