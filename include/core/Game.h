//
// Created by romip on 4/17/2021.
//

#ifndef NAIVE_BAYES_GAME_H
#define NAIVE_BAYES_GAME_H
#include <core/Player.h>
#include <core/Card.h>
#include <core/Board.h>
namespace naivebayes {
    class Game {
    public:
        Game(size_t num_players);
        void print();
        void play_game();
    private:
        vector<Player> players;
        Board board;
    };
}


#endif //NAIVE_BAYES_GAME_H
