#include <iostream>

#include <core/Card.h>
#include <core/Game.h>
#include <core/Player.h>
using namespace naivebayes;
    int main() {
        naivebayes::Game game(2);
        game.print();
        std::cout<<"game begins: "<<std::endl;
        game.play_game();
        std::cout<<"game ends"<<std::endl;
        game.print();
        return 0;
    }