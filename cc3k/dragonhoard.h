#ifndef _DRAGONHOARD_H
#define _DRAGONHOARD_H
#include <memory>
#include "Gold.h"

class Character;


class dragonhoard : public Gold{
    int id;
    std::shared_ptr<Character> d;
    public:
    dragonhoard(int id, std::shared_ptr<Character> d);
    int getid() override;
    std::shared_ptr<Character> getdragon() override;
};

#endif
