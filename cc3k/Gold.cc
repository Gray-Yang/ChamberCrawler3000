#include "Gold.h"
#include <stdlib.h>
#include <random>
#include "dragon.h"
#include <iostream>
Gold::Gold(int value){
    if (value == -1){
        int num = rand() % 8 + 1;
        if (num == 1 || num == 2 || num == 3 || num == 4 || num == 5){
            this->value = 2;
        }else if (num == 6){
            this->value = 6;
        }else if (num == 7 || num == 8){
            this->value = 1;
        }
    }else{
        if (value == 1){
            this->value = 1;
        }else if (value == 2){
            this->value = 2;
        }else if (value == 4){
            this->value = 4;
        }else if (value == 6){
            this->value = 6;
        }else{
            std::cout << "incorrect value!" << std::endl;
        }
    }
} 

int Gold::getvalue(){ return value; }

int Gold::getid(){ return 0;}

std::shared_ptr<Character> Gold::getdragon(){ return nullptr;}

Gold::~Gold(){ }

