#include <iostream>
#include "character.h"
#include "player.h"
#include "shade.h"
#include "Enemy.h"
#include "orc.h"
#include "controller.h"
#include "grid.h"
#include "observer.h"
#include "unit.h"
#include "dragon.h"
#include "human.h"
#include "dwarf.h"
#include "half.h"
#include "elf.h"
#include "merchant.h"
#include <memory>

int main(int argc, const char * argv[]) {
    bool trade = false;
    bool warriors = false;
    if (argc == 2 || argc == 3){
        for (int i = 1; i < argc; ++i){
            std::string now = argv[i];
            if(now == "-trade"){
                trade = true;
            }else if (now == "-warrior"){
                warriors = true;
            }
        }
    }
    // cover page
    std::ifstream infile{"cover.txt"};
    std::string line;
    while(std::getline(infile,line)){
        std::cout << line << std::endl;
    }
    // create controller
    std::shared_ptr<controller> con = std::shared_ptr<controller> (new controller());
    
    std::shared_ptr<grid> new_grid = std::shared_ptr<grid>(new grid{con});
    
    
    char race;
    
    std::cout << "Welcome to ChamberCrawler3000!" << std::endl;
    std::cout << "Choose your player type: " << std::endl;
    std::cout << "Shade(s) 125 HP, 25 Atk, 25 Def " << std::endl;
    std::cout << "Drow(d) 150 HP, 25 Atk, 15 Def " << std::endl;
    std::cout << "Vampire(v) 50 HP, 25 Atk, 25 Def " << std::endl;
    std::cout << "Troll(t) 120 HP, 25 Atk, 15 Def " << std::endl;
    std::cout << "Goblin(g) 110 HP, 15 Atk, 20 Def " << std::endl;
    if (warriors){
        std::cout << "Warrior(w) 2020 HP, 135 Atk, 136 Def" << std::endl;
    }
    std::cout << "enter your player race: " << std::endl;
    
    int count = 0;
    
    while(1){
        std::cin >> race;
        std::cout << "entered value for race: " << race << std::endl;
        if (race == 's' || race == 'd' || race == 'v' || race == 'g' || race == 't'){
            con->create_all(race);
            break;
        }else if (race == 'w' && warriors){
            con->create_all(race);
            break;
        }
        else{
            std::cout << "This is not one of player race! Try again: " << std::endl;
        }
        if (count >= 5){
            std::cout << "Please be serious. You have tried " << count << " times!" << std::endl;
        }
        ++count;
    }
    int floornum = 1;
    con->notifyOb();
    new_grid->print_grid();
    con->print_annotation(floornum, "Player character has spwaned.");
    bool can_moving = true;
    std::string action;
    while(cin >> action){
        bool invalid = false;
       
        std::string moving_message; // annotation
        
        if(action == "q") { // when user enter "q", end the game
            std::ifstream infile{"byebye.txt"};
            std::string line;
            while(std::getline(infile,line)){
                std::cout << line << std::endl;
            }
            con->scoring(con->my_cell.at(con->rowplayer).at(con->colplayer)->get_ch()->name() == "Shade");
            break;
        } 
        else if (action == "no" || action == "so" || action == "ea" || action == "we" || action == "ne" || action == "nw"
                    || action == "se" || action == "sw"){ // when user enters a direction
           
            std::string move_message = con->player_move(action);  // store the message from move
            if(move_message == "next floor"){
                if(floornum == 5){
                    std::ifstream infile{"win.txt"};
                    std::string line;
                    while(std::getline(infile,line)){
                        std::cout << line << std::endl;
                    }
                    std::cout << "You win the Game!" << std::endl;
                    con->scoring(con->my_cell.at(con->rowplayer).at(con->colplayer)->get_ch()->name() == "Shade");
                    std::cout << "Congradulation!" << std::endl;
                    break;
                }
                floornum +=1;
                int player_hp = (con->my_cell.at(con->rowp).at(con->colp))->get_ch()->get_HP();// store the player's hp
                int player_gold = (con->my_cell.at(con->rowp).at(con->colp))->get_ch()->get_gold();// store the player's gold amount
                std::shared_ptr<controller> new_con = std::shared_ptr<controller> (new controller()); // reset the controller
                new_con->create_all(race);
                con = new_con;
                (con->my_cell.at(con->rowplayer).at(con->colplayer))->get_ch()->set_gold(player_gold);
                (con->my_cell.at(con->rowplayer).at(con->colplayer))->get_ch()->set_hp(player_hp);
                (con->my_cell.at(con->rowplayer).at(con->colplayer))->set_oldsymbol('.');
                std::shared_ptr<grid> new_new_grid = std::shared_ptr<grid>(new grid{con});
                new_grid = new_new_grid;
                moving_message = "You have moved to the next floor. ";
            }
            else if(move_message == "Player at door/passageway/tile"){
                moving_message = "Player move one unit to ";
                moving_message += action;
                moving_message += ". ";
                if (can_moving){
                    con->enemy_move();
                }
            } else if (move_message == "We can not move to wall or enemy"){
                moving_message = "We can not move to that direction.";
                invalid = true;
            } else if (move_message == "potion"){
                if (can_moving){
                    con->enemy_move();
                }
                moving_message = "You step on a potion without using it.";
            }
            else{
                if (can_moving){
                    con->enemy_move();
                }
                moving_message = move_message;
            }// else of move_message
        }// else if of action no/...
        else if (action == "u"){
            std::cin >> action;
            moving_message = con->use_wild_potion(action);
            if(!(moving_message == "not valid direction")){
                if (can_moving){
                    con->enemy_move();
                }
            }else{
                invalid = true;
            }
        }else if (action == "f"){
            can_moving = !can_moving;
            moving_message = "Enemy can ";
            if (!can_moving){
                moving_message += "not";
            }
            moving_message += " move now. ";
        }else if (action == "r"){
            con = std::shared_ptr<controller> (new controller());
            new_grid = std::shared_ptr<grid>(new grid{con});
                std::cout << "Rechoose your player type: " << std::endl;
                std::cout << "Shade(s) 125 HP, 25 Atk, 25 Def " << std::endl;
                std::cout << "Drow(d) 150 HP, 25 Atk, 15 Def " << std::endl;
                std::cout << "Vampire(v) 50 HP, 25 Atk, 25 Def " << std::endl;
                std::cout << "Troll(t) 120 HP, 25 Atk, 15 Def " << std::endl;
                std::cout << "Goblin(g) 110 HP, 15 Atk, 20 Def " << std::endl;
                if (warriors){
                    std::cout << "Warrior(w) 2020 HP, 135 Atk, 136 Def" << std::endl;
                }
                std::cout << "enter your player race: " << std::endl;
            count = 0;
            while(1){
                std::cin >> race;
                std::cout << "entered value for race: " << race << std::endl;
                if (race == 's' || race == 'd' || race == 'v' || race == 'g' || race == 't'){
                    con->create_all(race);
                    break;
                }else if (race == 'w' && warriors){
                    con->create_all(race);
                    break;
                }
                else{
                    std::cout << "This is not one of player race! Try again: " << std::endl;
                }
                if (count >= 5){
                    std::cout << "Please be serious. You have tried" << count << " times!" << std::endl;
                }
                ++count;
            }
            floornum = 1;
            moving_message = "Player character has spwaned.";
            can_moving = true;
        }else if (action == "a"){
            std::cin >> action;
            if (!(action == "no" || action == "so"||action == "ea"||action == "we"
            ||action == "ne"||action == "nw"||action == "se"||action =="sw")){
                moving_message = "Not a valid direction to attack.";
                invalid = true;
            }else{
                moving_message = con->attack(action);
                if (moving_message == " There is no enemy to be attacked in that direction. "){
                    invalid = true;
                }else{
                    if (can_moving){
                    con->enemy_move();
                    }
                }
            }// else in a
        }// else if for action a
        else if (trade && action == "t" && con->Mattack == true){
            moving_message = "You have already attacked a Merchant in this floor. No Merchant will make deal with you.";
            std::cin >> action;
            std::string kind;
            std::cin >> kind;
        }
        else if (trade && action == "t" && con->Mattack == false){
            std::cin >> action;
            std::string kind;
            std::cin >> kind;
           
            moving_message = con->price_potion(action,kind);
            std::string message = "Are you sure to buy ";
            message += kind;
            message += " increase potion with a price of ";
            if (message != moving_message){
                invalid = true;
            }else{
                int price = 1;
                if (kind == "hp"){
                    price = 2 * floornum;
                }else{
                    price *= floornum;
                }
                message += std::to_string(price);
                message += ". (y for yes, and all other input are treated as no.)";
                con->notifyOb();
                new_grid->print_grid();
                con->print_annotation(floornum, message);
                std::string decision;
                std::cin >> decision;
                if (decision == "y"){
                    if (con->my_cell.at(con->rowplayer).at(con->colplayer)->get_ch()->get_gold() < price){
                        moving_message = "Not enough money to buy";
                    }else{
                        con->my_cell.at(con->rowplayer).at(con->colplayer)->get_ch()->add_gold(-price);
                        int idp = 0;
                        if (kind == "hp"){
                            idp = 1;
                        }else if (kind == "atk"){
                            idp = 3;
                        }else{
                            idp = 5;
                        }
                        con->use_potion(idp,action); 
                        moving_message = "use ";
                        moving_message += kind;
                        moving_message += " increase potion.";
                    } // whether enough money to buy
                    
                }// choose to buy
                else{
                    moving_message = "You choose to not buy potion from Merchant.";
                }
            }// moving message is valid => can buy
        }
        else{
            std::string messaging = "Invalid command";
            if (con->my_cell.at(con->rowplayer).at(con->colplayer)->get_ch()->dead()){
                con->scoring(con->my_cell.at(con->rowplayer).at(con->colplayer)->get_ch()->name() == "Shade");
                std::cout << "Do you want to reset the game, or just quit now?" << std::endl;
                std::cout << "press r for rest and q for quit" << std::endl;
                continue;
            }
            con->notifyOb();
            new_grid->print_grid();
            con->print_annotation(floornum, messaging);
            continue;
        }

        std::shared_ptr<Character> mycurplayernow = con->my_cell.at(con->rowplayer).at(con->colplayer)->get_ch();
        if (mycurplayernow->name() == "Troll"){
            mycurplayernow->change_HP(5);
        }
        if (!invalid){
            moving_message += con->auto_attack();
        }
        if (con->my_cell.at(con->rowplayer).at(con->colplayer)->get_ch()->dead()){
            con->scoring(con->my_cell.at(con->rowplayer).at(con->colplayer)->get_ch()->name() == "Shade");
            std::cout << "Do you want to reset the game, or just quit now?" << std::endl;
            std::cout << "press r for rest and q for quit" << std::endl;
            continue;
        }
        con->notifyOb();
        new_grid->print_grid();
        con->print_annotation(floornum, moving_message);
    } // while
}// main
