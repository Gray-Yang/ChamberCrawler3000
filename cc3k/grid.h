#ifndef __grid__
#define __grid__



#include "controller.h"
#include "observer.h"
using namespace std;

class grid: public observer {
    std::shared_ptr<controller> subject;
    std::vector<std::vector<char>> vec;
    public:
    grid(std::shared_ptr<controller> my_control);
    ~grid();
    void notify(int row, int col, char symbol) override;
    void print_grid();
};

#endif
