#include <iostream>

#include <core/Card.h>
#include <core/Game.h>
using namespace garbage;
    int main() {
        //sample game with 6 players that shows up step-by-step in the console
        garbage::Game game(6, 1);
        std::cout<<game.to_string();
        std::cout<<"game begins: "<<std::endl;
        game.play_game();
        std::cout<<"game ends"<<std::endl;
        std::cout<<game.to_string();
        return 0;
    }