#ifndef _GOLD_H
#define _GOLD_H
#include <memory>
class Character;

class Gold{
    int value;
    public:
    Gold(int value = -1);
    int getvalue();
    virtual int getid();
    virtual std::shared_ptr<Character> getdragon();
    virtual ~Gold();
};

#endif
