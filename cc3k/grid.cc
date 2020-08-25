#include "grid.h"

grid::grid(std::shared_ptr<controller> my_control){
    subject = my_control;
    for(int a = 0 ; a < 25 ; a ++){
        std::vector<char> thisrow;
        vec.emplace_back(thisrow);
        for(int b = 0 ;b < 80 ; b ++){
            if(b == 78){
                vec.at(a).emplace_back('\n');
            } else {
                vec.at(a).emplace_back('-');
            }
        }
    }
    subject->attachOb(this);
}

grid::~grid(){}

void grid::notify(int row, int col, char symbol) {
    vec.at(row).at(col) = symbol;
}

void grid::print_grid(){
    for(int a = 0; a < 25; a ++){
        for(int b = 0; b < 80;b++){
            cout << vec.at(a).at(b);
        }
    }
    cout << endl;
}
