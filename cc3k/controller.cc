#include "controller.h"
#include "observer.h"
#include "unit.h"
#include "shade.h"
#include "Gold.h"
#include "character.h"
#include "dragon.h"
#include <memory>
#include <time.h>
#include "orc.h"
#include "human.h"
#include "dwarf.h"
#include "half.h"
#include "elf.h"
#include "orc.h"
#include "merchant.h"
#include "drow.h"
#include "vampire.h"
#include "troll.h"
#include "goblin.h"
#include <math.h>
#include <vector>
#include <algorithm>
#include "final.h"
#include "warrior.h"
#include "dragonhoard.h"

controller::controller(){
    Mattack = false;
    id = 0;
    std::ifstream infile{"map.txt"};
    char i;
    infile >> std::noskipws;
    for(int a = 0 ; a < 25 ; a ++) {
        std::vector<std::shared_ptr<unit>> newrow;
        my_cell.emplace_back(newrow);
        for(int b = 0 ; b < 80 ; b ++){ // row and column map.at(a).at(b)
            infile >> i;
            std::shared_ptr<unit> newu = std::shared_ptr<unit>(new unit());
            my_cell.at(a).emplace_back(newu);
            my_cell.at(a).at(b)->set_symbol(i);
        }
    }
}

void controller::attachOb(observer* ob){
   v.emplace_back(ob); 
}

void controller::notifyOb(){
    for(auto n : v){
        for(int a = 0; a < 25; a ++){
            for(int b = 0; b < 80; b ++) {
                n->notify(a,b,my_cell.at(a).at(b)->get_symbol());
            }
        }
    }
}

void controller::choose_chamber(char c, int chamber_select){
    if(chamber_select ==  0){
         rowp = rand() % 4 + 3;
         colp = rand() % 26 + 3;
        while(my_cell.at(rowp).at(colp)->get_symbol() != '.'){
            rowp = rand() % 4 + 3;
            colp = rand() % 26 + 3;
        }
        my_cell.at(rowp).at(colp)->set_symbol(c);
    } else if (chamber_select == 1){
         rowp = rand() % 10 + 3;
         colp = rand() % 37 + 39;
        while((rowp >= 10 && colp <= 50) || my_cell.at(rowp).at(colp)->get_symbol() != '.'){
            colp = rand() % 10 + 3;
            colp = rand() % 37 + 40;
        } 
        my_cell.at(rowp).at(colp)->set_symbol(c);
    } else if (chamber_select == 2){
         rowp = rand() % 3 + 10;
         colp = rand() % 12 + 38;
         while(my_cell.at(rowp).at(colp)->get_symbol() != '.'){
         rowp = rand() % 3 + 10;
         colp = rand() % 12 + 38;
        }
        my_cell.at(rowp).at(colp)->set_symbol(c);
    } else if (chamber_select == 3){
         rowp = rand() % 7 + 15;
         colp = rand() % 21 + 4;
         while(my_cell.at(rowp).at(colp)->get_symbol() != '.'){
         rowp = rand() % 7 + 15;
         colp = rand() % 21 + 4;
        }
        my_cell.at(rowp).at(colp)->set_symbol(c);
    }  else if (chamber_select == 4){
         rowp = rand() % 6 + 16;
         colp = rand() % 39 + 37;
        while(my_cell.at(rowp).at(colp)->get_symbol() != '.'){
             rowp = rand() % 6 + 16;
             colp = rand() % 39 + 37;
        }
        my_cell.at(rowp).at(colp)->set_symbol(c);
    } //return chamber_select
}

void controller::create_player(char name){
    int chamber_select = rand() % 5;
    choose_chamber('@',chamber_select);
    chamberp = chamber_select;
    rowplayer = rowp;
    colplayer = colp;
    if (name == 's'){
        my_cell.at(rowp).at(colp)->set_ch(std::shared_ptr<Character>(new Shade()));
    }
    else if (name == 'd'){
        my_cell.at(rowp).at(colp)->set_ch(std::shared_ptr<Character>(new Drow()));
    }
    else if (name == 'v'){
        my_cell.at(rowp).at(colp)->set_ch(std::shared_ptr<Character>(new Vampire()));
    }
    else if (name == 'g'){
        my_cell.at(rowp).at(colp)->set_ch(std::shared_ptr<Character>(new Goblin()));
    }
    else if (name == 't'){
        my_cell.at(rowp).at(colp)->set_ch(std::shared_ptr<Character>(new Troll()));
    }else if (name == 'w'){
        my_cell.at(rowp).at(colp)->set_ch(std::shared_ptr<Character>(new Warrior()));
    }
}

void controller::create_stair() {
    int chamber_select = rand() % 5;
    while(chamber_select == chamberp){
        chamber_select = rand() % 5;
    }
    choose_chamber('\\',chamber_select);
}



void controller::create_potion(){
    int chamber_select = rand() % 5;
    for (int i = 0; i < 10; ++i){
        chamber_select = rand() % 5;
        choose_chamber('P',chamber_select);
    }
}

std::string find_direction(int &currow,int &curcol, std::string direction){
   if (direction == "no"){ // no
        --currow;
    }else if (direction == "so"){ //so
        ++currow;
    }else if (direction == "ea"){ // ea
        ++curcol;
    }else if(direction == "we"){ //we
        --curcol;
    }else if (direction == "ne"){ //ne
        --currow;
        ++curcol;
    }else if (direction == "nw"){ //nw
        --currow;
        --curcol;
    }else if(direction == "sw"){ //sw
        ++currow;
        --curcol;
    }else if (direction == "se"){ // se
        ++currow;
        ++curcol;
    }
    else{
        return  "not valid direction";
    }
    if (currow < 0 || curcol < 0 || currow > 24 || curcol > 79){
        return "out of map";
    }
    return "ok";
}

std::string controller::price_potion(std::string direction, std::string type){
    if (!(type == "hp" || type == "atk"|| type == "def")){
        return "Invalid potion type.";
    }
    int currow = rowplayer;
    int curcol = colplayer;
    std::string message = find_direction(currow,curcol,direction);
    if (message != "ok"){
        return message;
    }
    if(my_cell.at(currow).at(curcol)->get_symbol() != 'M'){
        std::string error = "In ";
        error += direction;
        error += ", there is no Merchant.";
        return error;
    }
    message = "Are you sure to buy ";
    message += type;
    message += " increase potion with a price of ";
    return message;
}




std::string controller::use_wild_potion(std::string direction){
    int currow = rowplayer;
    int curcol = colplayer;
    std::string message = find_direction(currow,curcol,direction);
    if (message != "ok"){
        return message;
    }
    if(my_cell.at(currow).at(curcol)->get_symbol() != 'P'){
        std::string error = "In ";
        error += direction;
        error += ", there is no Potion.";
        return error;
    }
    int potion_select = rand() % 6 + 1;
    message = use_potion(potion_select,direction);
    my_cell.at(currow).at(curcol)->set_symbol('.');
    return message;
}

std::string controller::use_potion(int potion_select, std::string direction){
    int currow = rowplayer;
    int curcol = colplayer;
    find_direction(currow,curcol,direction);
    std::string message = "";
    std::shared_ptr<Character> playernow = my_cell.at(rowplayer).at(colplayer)->get_ch();
    bool is_drow = (playernow->name() == "Drow");

    if (potion_select == 1){
        playernow->change_HP(10);
        if (is_drow){
            playernow->change_HP(5);
            message = "Use Restore Health (RH),up max 15 HP.";
        }else{
            message = "Use Restore Health (RH),up max 10 HP.";
        }
        return message;
    }
    else if (potion_select == 2){
        playernow->change_HP(-10);
        if (is_drow){
            playernow->change_HP(-5);
        }
        if (playernow->get_HP() == 0){
            std::string message = "Use Poison health (PH), the player is DEAD.";
            return message;
        }
        if (is_drow){
            message = "Use Poison health (PH), decrease 15 HP.";
        }else{
            message = "Use Poison health (PH), decrease 10 HP.";
        }
        return message;
    }
    else if (potion_select == 3){
        playernow->change_Atk(5);
        if (is_drow){
            playernow->change_Atk(2.5);
            message = "Use Boost Atk (BA), increase 7.5 Atk.";
        }else{
            message = "Use Boost Atk (BA), increase 5 Atk.";
        }
        return message;
    }
    else if (potion_select == 4){
        if (is_drow){
            playernow->change_Atk(-2.5);
        }
        playernow->change_Atk(-5);
        if (is_drow){
            message = "Use Wound Atk (WA), decrease 7.5 Atk.";
        }else{
            message = "Use Wound Atk (WA), decrease 5 Atk.";
        }
        return message;
    }
    else if (potion_select == 5){
        if (is_drow){
            playernow->change_Def(2.5);
        }
        playernow->change_Def(5);
        if (is_drow){
            message = "Use Boost Def (BD), increase 7.5 Def.";
        }else{
            message = "Use Boost Def (BD), increase 5 Def.";
        }
        return message;
    }
    else {
        if (is_drow){
            playernow->change_Def(-2.5);
        }
        playernow->change_Def(-5);
        if (is_drow){
            message = "Use Wound (WD), decrease 7.5 Def.";
        }else{
            message = "Use Wound (WD), decrease 5 Def.";
        }
        return message;
    }
}


void position(int& currow,int& curcol,int direction){
    if (direction == 0){ // no
        --currow;
    }else if (direction == 1){ //so
        ++currow;
    }else if (direction == 2){ // ea
        ++curcol;
    }else if(direction == 3){ //we
        --curcol;
    }else if (direction == 4){ //ne
        --currow;
        ++curcol;
    }else if (direction == 5){ //nw
        --currow;
        --curcol;
    }else if(direction == 6){ //sw
        ++currow;
        --curcol;
    }else { // se
        ++currow;
        ++curcol;
    }
}


void controller::create_gold(){
    int chamber_select = rand() % 5;
    for (int i = 0; i < 10; ++i){
        chamber_select = rand() % 5;
        choose_chamber('G',chamber_select);
        my_cell.at(rowp).at(colp)->set_it(std::shared_ptr<Gold>(new Gold()));
        if (my_cell.at(rowp).at(colp)->get_it()->getvalue() == 6){
            this->id += 1;
            int row_d = rowp;
            int col_d = colp;
            int dir1 = rand() % 8;
            position(row_d,col_d,dir1);
            while(my_cell.at(row_d).at(col_d)->get_symbol() != '.'){
                row_d = rowp;
                col_d = colp;
                int dir2 = rand() % 8;
                position(row_d,col_d,dir2);
            }
            my_cell.at(row_d).at(col_d)->set_symbol('D');
            my_cell.at(row_d).at(col_d)->set_ch(std::shared_ptr<Character> (new Dragon(rowp,colp)));
            my_cell.at(rowp).at(colp)->set_it(nullptr);
            my_cell.at(rowp).at(colp)->set_it(std::shared_ptr<Gold>(new dragonhoard(this->id,my_cell.at(row_d).at(col_d)->get_ch())));
        }
    }
}

void controller::create_enemy(){
    int chamber_select = rand() % 5;
    if (my_cell.at(rowplayer).at(colplayer)->get_ch()->name() == "Warrior"){
        choose_chamber('F',chamber_select);
        my_cell.at(rowp).at(colp)->set_ch(std::shared_ptr<Character>(new Final()));
    }
    for (int i = 0; i < 20; ++i){
        chamber_select = rand() % 5;
        int enemy_select = rand() % 18 + 1;
        if (enemy_select == 1 || enemy_select == 2 || enemy_select == 3 || enemy_select == 4){ 
            choose_chamber('H',chamber_select);
            my_cell.at(rowp).at(colp)->set_ch(std::shared_ptr<Character>(new Human()));
        }else if (enemy_select == 5 || enemy_select == 6 || enemy_select == 7){
            choose_chamber('W',chamber_select);
            my_cell.at(rowp).at(colp)->set_ch(std::shared_ptr<Character>(new Dwarf()));
        }else if (enemy_select == 8 || enemy_select == 9 || enemy_select == 10 || enemy_select == 11 || enemy_select == 12){
            choose_chamber('L',chamber_select);
            my_cell.at(rowp).at(colp)->set_ch(std::shared_ptr<Character>(new Half()));
        }else if (enemy_select == 13 || enemy_select == 14){
            choose_chamber('E',chamber_select);
            my_cell.at(rowp).at(colp)->set_ch(std::shared_ptr<Character>(new Elf()));
        }else if (enemy_select == 15 || enemy_select == 16){
            choose_chamber('O',chamber_select);
            my_cell.at(rowp).at(colp)->set_ch(std::shared_ptr<Character>(new Orc()));
        }else{
            choose_chamber('M',chamber_select);
            my_cell.at(rowp).at(colp)->set_ch(std::shared_ptr<Character>(new Merchant()));
        }
    }
}

void controller::create_all(char name){
    srand(time(NULL));
    create_player(name);
    create_stair();
    create_potion();
    create_gold();
    create_enemy();
}

int dir_to_int(std::string direction){
    if (direction == "no"){
        return 0;
    }else if (direction == "so"){
        return 1;
    }else if (direction == "ea"){
        return 2;
    }else if (direction == "we"){
        return 3;
    }else if (direction == "ne"){
        return 4;
    }else if (direction == "nw"){
        return 5;
    }else if (direction == "sw"){
        return 6;
    }else {
        return 7;
    }
}


std::string controller::player_move(std::string direction){
    int dir = dir_to_int(direction);
    rowp = rowplayer; // represent row number before movement
    colp = colplayer; // represent col number before movement
    position(rowplayer,colplayer,dir);
    if(my_cell.at(rowplayer).at(colplayer)->get_symbol() == '\\'){
        rowplayer = rowp;
        colplayer = colp;
        return "next floor";
    }else if (my_cell.at(rowplayer).at(colplayer)->get_symbol() == 'P'){
        if (my_cell.at(rowp).at(colp)->get_oldsymbol() == 'P'||my_cell.at(rowp).at(colp)->get_oldsymbol()=='G'
        || my_cell.at(rowp).at(colp)->get_oldsymbol() == '+'||my_cell.at(rowp).at(colp)->get_oldsymbol()=='#'){
            my_cell.at(rowp).at(colp)->set_symbol(my_cell.at(rowp).at(colp)->get_oldsymbol());
        }else{
            my_cell.at(rowp).at(colp)->set_symbol('.');
        }
        my_cell.at(rowplayer).at(colplayer)->set_ch(my_cell.at(rowp).at(colp)->get_ch());
        my_cell.at(rowp).at(colp)->set_ch(nullptr); // last unit player pointer back to nullptr
        my_cell.at(rowplayer).at(colplayer)->set_oldsymbol('P'); // past is P, not used
        my_cell.at(rowplayer).at(colplayer)->set_symbol('@'); // now occupy by player
        return "potion";
    } else if (my_cell.at(rowplayer).at(colplayer)->get_symbol() == '+' 
                || my_cell.at(rowplayer).at(colplayer)->get_symbol() == '#'
                || my_cell.at(rowplayer).at(colplayer)->get_symbol() == '.'){ // change original rowp(ast) to past symbol 
        if (my_cell.at(rowp).at(colp)->get_oldsymbol() == 'P'||my_cell.at(rowp).at(colp)->get_oldsymbol()=='G'
        || my_cell.at(rowp).at(colp)->get_oldsymbol() == '+'||my_cell.at(rowp).at(colp)->get_oldsymbol()=='#'){
            my_cell.at(rowp).at(colp)->set_symbol(my_cell.at(rowp).at(colp)->get_oldsymbol());
        }else{
            my_cell.at(rowp).at(colp)->set_symbol('.');
        }
        my_cell.at(rowplayer).at(colplayer)->set_ch(my_cell.at(rowp).at(colp)->get_ch()); // player pointer in current unit
        my_cell.at(rowp).at(colp)->set_ch(nullptr); // last unit player pointer back to nullptr
        my_cell.at(rowplayer).at(colplayer)->set_oldsymbol(my_cell.at(rowplayer).at(colplayer)->get_symbol()); // past is # or + or . , not used and saved tp get_oldsymbol()
        my_cell.at(rowplayer).at(colplayer)->set_symbol('@');// now occupy by player
        std::string message = "Player at door/passageway/tile";
        return message;
    }else if (my_cell.at(rowplayer).at(colplayer)->get_symbol() == 'G' ){
        if (my_cell.at(rowp).at(colp)->get_oldsymbol() == 'P'||my_cell.at(rowp).at(colp)->get_oldsymbol()=='G'
        ||my_cell.at(rowp).at(colp)->get_oldsymbol()=='+'||my_cell.at(rowp).at(colp)->get_oldsymbol() == '#'){
            my_cell.at(rowp).at(colp)->set_symbol(my_cell.at(rowp).at(colp)->get_oldsymbol());
        }else{
            my_cell.at(rowp).at(colp)->set_symbol('.');
        }
        my_cell.at(rowplayer).at(colplayer)->set_ch(my_cell.at(rowp).at(colp)->get_ch());
        my_cell.at(rowp).at(colp)->set_ch(nullptr);
        my_cell.at(rowplayer).at(colplayer)->set_symbol('@');
        if (my_cell.at(rowplayer).at(colplayer)->get_it()->getvalue() != 6){ // when land on treasure other than dragon hoard
            my_cell.at(rowplayer).at(colplayer)->get_ch()->add_gold(my_cell.at(rowplayer).at(colplayer)->get_it()->getvalue()); 
            my_cell.at(rowplayer).at(colplayer)->set_oldsymbol('.');
            return "picked up gold";
        }else{ // when land on dragon hoard
            if (!my_cell.at(rowplayer).at(colplayer)->get_it()->getdragon()->dead()){
                my_cell.at(rowplayer).at(colplayer)->set_oldsymbol('G');
                return "dragon alive, cannot pick up gold";
            }else{
                my_cell.at(rowplayer).at(colplayer)->get_ch()->add_gold(6); // dragon dies, pick up the gold
                my_cell.at(rowplayer).at(colplayer)->set_oldsymbol('.');
                return "dragon dead, picked 6 gold";
            }            
        }
    }
    else{ // enemy or wall
        std::string message = "We can not move to wall or enemy";
        rowplayer = rowp;
        colplayer = colp;
        return message;
    }               
}

void controller::enemy_move(){
    srand(time(NULL));  
    for (int i = 0; i < 8; ++i){ // surrounding enemy will not move and be ready to attack player
        int closerow = rowplayer;
        int closecol = colplayer;
        position(closerow,closecol,i);
        if(my_cell.at(closerow).at(closecol)->get_symbol() == 'H' || my_cell.at(closerow).at(closecol)->get_symbol() == 'W'
            || my_cell.at(closerow).at(closecol)->get_symbol() == 'O' || my_cell.at(closerow).at(closecol)->get_symbol() == 'E'
            || my_cell.at(closerow).at(closecol)->get_symbol() == 'M' || my_cell.at(closerow).at(closecol)->get_symbol() == 'L' 
            || my_cell.at(closerow).at(closecol)->get_symbol() == 'F'){
            my_cell.at(closerow).at(closecol)->set_is_moved(true);
        }
    } 
    for(int a = 0 ; a < 25 ; a ++){
        for(int b = 0 ; b < 79 ; b ++){
            if(my_cell.at(a).at(b)->get_symbol() == 'H' || my_cell.at(a).at(b)->get_symbol() == 'W'
            || my_cell.at(a).at(b)->get_symbol() == 'O' || my_cell.at(a).at(b)->get_symbol() == 'E'
            || my_cell.at(a).at(b)->get_symbol() == 'M' || my_cell.at(a).at(b)->get_symbol() == 'L' 
            || my_cell.at(a).at(b)->get_symbol() == 'F' ){
                int direction = rand() % 8;
                rowp = a;
                colp = b;
                position(rowp,colp,direction);
                int counter = 0;
                while(my_cell.at(rowp).at(colp)->get_symbol() != '.'){
                    if(counter > 100000){
                        return;
                    }
                    direction = rand() % 8;
                    rowp = a;
                    colp = b;
                    position(rowp,colp,direction);
                    counter++;
                }
                if(my_cell.at(a).at(b)->get_is_moved()){
                    my_cell.at(a).at(b)->set_is_moved(false);
                } else {
                    my_cell.at(rowp).at(colp)->set_is_moved(true);
                    my_cell.at(rowp).at(colp)->set_oldsymbol('.');
                    my_cell.at(rowp).at(colp)->set_symbol(my_cell.at(a).at(b)->get_symbol());
                    my_cell.at(rowp).at(colp)->set_ch(my_cell.at(a).at(b)->get_ch());
                    my_cell.at(a).at(b)->set_symbol('.');
                    my_cell.at(a).at(b)->set_ch(nullptr);
                }
            }
        }
    }
}

// controller's new method auto_attack (all enemy surrouding attack player)
std::string controller::auto_attack(){
    std::shared_ptr<Character> myplayernow = my_cell.at(rowplayer).at(colplayer)->get_ch();
    double player_def = myplayernow->get_Def();
    std::string message = " ";
    srand(time(NULL));
    std::vector<int> arrindex;
    for (int i = 0; i < 8; ++i){ // surrounding enemy will not move and be ready to attack player
        bool attack = rand() % 2;
        if (attack){
            int closerow = rowplayer;
            int closecol = colplayer;
            position(closerow,closecol,i);
            if(my_cell.at(closerow).at(closecol)->get_symbol() == 'E'){
                my_cell.at(closerow).at(closecol)->set_is_moved(true);
                double enemy_atk = 30;
                double downvalue = ceil((100/(100+player_def)) * enemy_atk);
                if(myplayernow->name() == "Drow"){
                    myplayernow->change_HP(-downvalue);
                    message += "Elf attacks player Drow, and ";
                    message += std::to_string(downvalue);
                    message += " damage is made to player Drow. ";
                } else {
                    myplayernow->change_HP(- downvalue * 2);
                    message += "Elf attacks player, and ";
                    message += std::to_string(downvalue*2);
                    message += " damage is made to player. ";
                }
            } else if(my_cell.at(closerow).at(closecol)->get_symbol() == 'O'){
                my_cell.at(closerow).at(closecol)->set_is_moved(true);
                double enemy_atk = 30;
                double downvalue = ceil((100/(100+player_def)) * enemy_atk);
                if(myplayernow->name() == "Goblin"){
                    myplayernow->change_HP(-1.5* downvalue);
                    message += "Orcs attacks player Goblin, and ";
                    message += std::to_string(downvalue*1.5);
                    message += " damage is made to player. ";
                } else {
                    myplayernow->change_HP(-downvalue);
                    message += "Orcs attacks player, and ";
                    message += std::to_string(downvalue);
                    message += " damage is made to player. ";
                }
            } else if(my_cell.at(closerow).at(closecol)->get_symbol() == 'M'){
                if(Mattack){
                    double enemy_atk = 70;
                    double downvalue = ceil((100/(100+player_def)) * enemy_atk);
                    myplayernow->change_HP(-downvalue);
                    message += "Merchant attacks player, and ";
                    message += std::to_string(downvalue);
                    message += " damage is made to player. ";
                }
            } else if( my_cell.at(closerow).at(closecol)->get_symbol() == 'W'
            || my_cell.at(closerow).at(closecol)->get_symbol() == 'H'  
            || my_cell.at(closerow).at(closecol)->get_symbol() == 'L' 
            || my_cell.at(closerow).at(closecol)->get_symbol() == 'F'){
                    my_cell.at(closerow).at(closecol)->set_is_moved(true);
                    double enemy_atk = my_cell.at(closerow).at(closecol)->get_ch()->get_Atk();
                    double downvalue = ceil((100/(100+player_def)) * enemy_atk);
                    my_cell.at(rowplayer).at(colplayer)->get_ch()->change_HP(-downvalue);
                    message += "Enemy attacks player, and ";
                    message += std::to_string(downvalue);
                    message += " damage is made to player. "; //ceil((100/(100+player_def)) * enemy_atk);
            }else if (my_cell.at(closerow).at(closecol)->get_symbol() == 'D'
            ||(my_cell.at(closerow).at(closecol)->get_symbol() == 'G'
               && my_cell.at(closerow).at(closecol)->get_it()->getvalue() == 6)){
                int idd;
                if (my_cell.at(closerow).at(closecol)->get_symbol() == 'G' ){
                    idd = my_cell.at(closerow).at(closecol)->get_it()->getid();
                    if (my_cell.at(closerow).at(closecol)->get_it()->getdragon()->dead()){
                        continue;
                    }
                }else{
                    Character* mydragonhere = &(*my_cell.at(closerow).at(closecol)->get_ch());
                    int hoardrow1 = dynamic_cast<Dragon*>(mydragonhere)->hoardrow;
                    int hoardcol1 = dynamic_cast<Dragon*>(mydragonhere)->hoardcol;
                    idd = my_cell.at(hoardrow1).at(hoardcol1)->get_it()->getid();
                }
                if (arrindex.size() == 0){
                    arrindex.emplace_back(idd);
                    my_cell.at(closerow).at(closecol)->set_is_moved(true);
                    double downvalue = ceil((100/(100+player_def)) * 20);
                    myplayernow->change_HP(-downvalue);     
                    message += "Dragon attacks player, and ";
                    message += std::to_string(downvalue);
                    message += " damage is made to player. ";
                }
                else{
                    std::vector<int>::iterator ite = std::find(arrindex.begin(),arrindex.end(),idd);
                    if (ite == arrindex.end()){
                        arrindex.emplace_back(idd);
                        my_cell.at(closerow).at(closecol)->set_is_moved(true);
                        double enemy_atk = 20;
                        double downvalue = ceil((100/(100+player_def)) * enemy_atk);
                        myplayernow->change_HP(-downvalue);     
                        message += "Dragon attacks player, and ";
                        message += std::to_string(downvalue);
                        message += " damage is made to player. ";
                    } // not found
                } // else for finding vector
            }// else if for gold and dragon
        }   
    } // all direction
    // check if the current cell is an enemy
    return message;
}

// player attack enemy
std::string controller::attack(std::string direction){
    srand(time(NULL));
    std::string message = "Player attacks ";
    int erow = rowplayer;
    int ecol = colplayer;
    int dir = dir_to_int(direction);
    position(erow,ecol,dir);
    char ensymbol = my_cell.at(erow).at(ecol)->get_symbol();// unit position
    std::shared_ptr<Character> hate = my_cell.at(erow).at(ecol)->get_ch();
    std::shared_ptr<Character> myplayer = my_cell.at(rowplayer).at(colplayer)->get_ch();
    if (ensymbol == 'H'){ 
        message += "Human. "; // human drop golds.
        double result = (100/(100+hate->get_Def()))*myplayer->get_Atk();
        hate->change_HP(-result);
        //shade has no special powers
        // drow can magnified potion 1.5 times, so nothing special in attacking enemies
        if(myplayer->name() == "Vampire"){ // vampire gain special hp every sucessful attack
            myplayer->change_HP(5);
        }
        if (hate->dead()){
            //hate->HP = 0;
            if (myplayer->name() == "Goblin"){ // goblin steals gold from every slain enemy
                myplayer->add_gold(5);
            }
            // hate is dead. Human enemy is dead.
            my_cell.at(erow).at(ecol)->set_symbol('G');
            my_cell.at(erow).at(ecol)->set_oldsymbol('.');
            my_cell.at(erow).at(ecol)->set_ch(nullptr);
            my_cell.at(erow).at(ecol)->set_it(std::shared_ptr<Gold>(new Gold(4)));
            message += " Human is dead. 2 normal piles drop.";
            return message;
        }
        message += " Human has ";
        message += std::to_string(hate->get_HP());
        message += " hp left.";
    }else if (ensymbol == 'W'){ 
        message += "Dwarf. "; // dwarf special power is vampire will lose 5 HP each successful attack
        double result = (100/(100+hate->get_Def()))*myplayer->get_Atk();
        hate->change_HP(-result);
        if(myplayer->name() == "Vampire"){ 
            myplayer->change_HP(-5);
        }
        if (hate->dead()){
            if (myplayer->name() == "Goblin"){ // goblin steals gold from every slain enemy
                myplayer->add_gold(5);
            }
            // hate is dead. Human enemy is dead.
            my_cell.at(erow).at(ecol)->set_symbol('.');
            my_cell.at(erow).at(ecol)->set_oldsymbol('.');
            my_cell.at(erow).at(ecol)->set_ch(nullptr);
            int amt = rand() % 2 + 1;
            myplayer->add_gold(amt);
            message += " Dwarf is dead. Player pick up ";
            message += std::to_string(amt);
            message += " gold.";
            return message;
        }
        message += " Dwarf has ";
        message += std::to_string(hate->get_HP());
        message += " hp left.";
    }else if (ensymbol == 'E'){
        message += "Elf";
        // Elf gets 2 attacks against every race except drow not related to player attacking it
        double result = (100/(100+hate->get_Def()))*myplayer->get_Atk();
        hate->change_HP(-result);
        if(myplayer->name() == "Vampire"){ 
            myplayer->change_HP(5);
        }
        if (hate->dead()){
            if (myplayer->name() == "Goblin"){ // goblin steals gold from every slain enemy
                myplayer->add_gold(5);
            }
            // hate is dead. Human enemy is dead.
            my_cell.at(erow).at(ecol)->set_symbol('.');
            my_cell.at(erow).at(ecol)->set_oldsymbol('.');
            my_cell.at(erow).at(ecol)->set_ch(nullptr);
            int amt = rand() % 2 + 1;
            myplayer->add_gold(amt);
            message += " Elf is dead. Player pick up ";
            message += std::to_string(amt);
            message += " gold.";
            return message;
        }
        message += " Elf has ";
        message += std::to_string(hate->get_HP());
        message += " hp left";
    }else if (ensymbol == 'O' || ensymbol == 'F'){
        message += hate->name();
        message += ". ";
        double result = (100/(100+hate->get_Def()))*myplayer->get_Atk();
        hate->change_HP(-result);
        if(myplayer->name() == "Vampire"){ 
            myplayer->change_HP(5);
        }
        if (hate->dead()){
            if (myplayer->name() == "Goblin"){ // goblin steals gold from every slain enemy
                myplayer->add_gold(5);
            }
            my_cell.at(erow).at(ecol)->set_symbol('.');
            my_cell.at(erow).at(ecol)->set_oldsymbol('.');
            my_cell.at(erow).at(ecol)->set_ch(nullptr);
            int amt = rand() % 2 + 1;
            if (ensymbol == 'F'){
                amt = 100;
            }
            myplayer->add_gold(amt);
            message += " ";
            message += hate->name();
            message += " is dead. Player pick up ";
            message += std::to_string(amt);
            message += " gold.";
            return message;
        }
        message += " ";
        message += hate->name();
        message += " has ";
        message += std::to_string(hate->get_HP());
        message += " hp left.";
    }
    else if (ensymbol == 'M'){
        message += "Merchant. ";
        Mattack = true;
        double result = (100/(100+hate->get_Def()))*myplayer->get_Atk();
        hate->change_HP(-result);
        if(myplayer->name() == "Vampire"){ 
            myplayer->change_HP(5);
        }
        if (hate->dead()){
            if (myplayer->name() == "Goblin"){ // goblin steals gold from every slain enemy
                myplayer->add_gold(5);
            }
            my_cell.at(erow).at(ecol)->set_symbol('G');
            my_cell.at(erow).at(ecol)->set_oldsymbol('.');
            my_cell.at(erow).at(ecol)->set_ch(nullptr);
            my_cell.at(erow).at(ecol)->set_it(std::shared_ptr<Gold>(new Gold(4)));
            message += " Merchant is dead. 4 merchant piles drop";
            return message;
        }
        message += " Merchant has ";
        message += std::to_string(hate->get_HP());
        message += " hp left. ";
    }else if (ensymbol == 'D'){
        message += "Dragon. ";
        double result = (100/(100+hate->get_Def()))*myplayer->get_Atk();
        hate->change_HP(-result);
        if(myplayer->name() == "Vampire"){ 
            myplayer->change_HP(5);
        }
        if (hate->dead()){
            if (myplayer->name() == "Goblin"){ // goblin steals gold from every slain enemy
                myplayer->add_gold(5);
            }
            my_cell.at(erow).at(ecol)->set_symbol('.');
            my_cell.at(erow).at(ecol)->set_oldsymbol('.');
            my_cell.at(erow).at(ecol)->set_ch(nullptr);
            message += " Dragon is dead. Player can pick up dragon hoard now.";
            if (my_cell.at(rowplayer).at(colplayer)->get_oldsymbol() == 'G'){
                if (my_cell.at(rowplayer).at(colplayer)->get_it()->getvalue() == 6){
                    my_cell.at(rowplayer).at(colplayer)->set_it(nullptr);
                    my_cell.at(rowplayer).at(colplayer)->set_oldsymbol('.');
                    my_cell.at(rowplayer).at(colplayer)->get_ch()->add_gold(6);
                    message += " 6 Gold picked up. ";
                }
            }
            return message;
        }
        message += " Dragon has ";
        message += std::to_string(hate->get_HP());
        message += " hp left. ";
    }else if (ensymbol == 'L'){
        message += "Halfling. ";
        bool notmiss = rand() % 2;
        if (!notmiss){
            message += " However, Player miss attack. ";
            return message;
        }
        double result = (100/(100+hate->get_Def()))*myplayer->get_Atk();
        hate->change_HP(-result);
        if(myplayer->name() == "Vampire"){ 
            myplayer->change_HP(5);
        }
        if (hate->dead()){
            if (myplayer->name() == "Goblin"){ // goblin steals gold from every slain enemy
                myplayer->add_gold(5);
            }
            my_cell.at(erow).at(ecol)->set_symbol('.');
            my_cell.at(erow).at(ecol)->set_oldsymbol('.');
            my_cell.at(erow).at(ecol)->set_ch(nullptr);
            int amt = rand() % 2 + 1;
            myplayer->add_gold(amt);
            message += " Halfing is dead. Player pick up ";
            message += std::to_string(amt);
            message += " gold.";
            return message;
        }
        message += " Halfling has ";
        message += std::to_string(hate->get_HP());
        message += " hp left. ";
    }else{
        message = " There is no enemy to be attacked in that direction. ";
        return message;
    }
    return message;
}


void controller::print_annotation(int floornum, std::string message){
    std::shared_ptr<Character> myplayer = my_cell.at(rowplayer).at(colplayer)->get_ch();
    std::cout << "Floor " << floornum << std::endl;
    std::cout << "Race: ";
    std::cout <<  myplayer->name();
    std::cout << " Gold: " << myplayer->get_gold() << std::endl;
    std::cout << "HP: ";
    std::cout <<  myplayer->get_HP() << std::endl;
    std::cout << "Atk: ";
    std::cout <<  myplayer->get_Atk() << std::endl;
    std::cout << "Def: ";
    std::cout <<  myplayer->get_Def() << std::endl;
    std::cout << "Action: ";
    std::cout << message << std::endl;
}  

void controller::scoring(bool isshade){
    std::cout << "The game is end. Your score is ";
    double goldamt = (double) my_cell.at(rowplayer).at(colplayer)->get_ch()->get_gold();
    if (isshade){
        goldamt *= 1.5;
    }
    std::cout << goldamt << "." << std::endl;
}

