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
        Game();
        Game(size_t num_players, size_t seed);
        string to_string();
        void play_game();
        bool turn();
        bool step();
        bool is_over();
        string game_summary();
    private:
        Board* board;
    };
}


#endif //NAIVE_BAYES_GAME_H
