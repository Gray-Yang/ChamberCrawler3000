#ifndef __controller__
#define __controller__

#include <iostream>
#include <vector>
#include <fstream>
#include <memory>
#include <random>
#include "unit.h"
class observer;

class controller {
    public:
    std::vector<std::vector<std::shared_ptr<unit>>> my_cell;
    int rowp;
    int colp;
    int rowplayer;
    int colplayer;
    int chamberp;
    bool Mattack;
    int id;
    std::vector<observer*> v;
    controller();
    void attachOb(observer* ob);
    void notifyOb();
    void create_map();
    void create_player(char name);
    void create_stair();
    std::string use_wild_potion(std::string direction);
    void create_potion();
    void choose_chamber(char c,int num);
    void create_gold();
    void create_enemy();
    void create_all(char name);
    std::string player_move(std::string direction);
    void enemy_move();
    void print_annotation(int floornum, std::string message);
    std::string auto_attack(); // for enemy attacking player
    std::string attack(std::string direction); // for player attacking enemy
    void scoring(bool isshade);
    std::string price_potion(std::string direction, std::string type);
    std::string use_potion(int potion_select, std::string direction);
};

#endif
