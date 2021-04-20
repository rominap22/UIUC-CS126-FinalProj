#include <iostream>

#include <core/Card.h>
#include <core/Game.h>
#include <core/Player.h>
using namespace naivebayes;
    int main() {
        naivebayes::Game game(6, 1);
        std::cout<<game.to_string();
        std::cout<<"game begins: "<<std::endl;
        game.play_game();
        std::cout<<"game ends"<<std::endl;
        std::cout<<game.to_string();
        return 0;
    }