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
        ~Game();
        string to_string(size_t player_num);
        string to_string();
        void get_summary(Card* hand, size_t player_num);
        void play_game();
        bool turn();
        bool step();
        bool is_over();
        string game_summary();
        bool is_jack();
        void place_jack(size_t rank);
        bool is_rank_good(size_t rank);
        size_t select_best_rank();
        Card get_last_discard();
    private:
        Board* board;
    };
}


#endif //NAIVE_BAYES_GAME_H
