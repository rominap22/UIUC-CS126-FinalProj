//
// Created by romip on 4/17/2021.
//

#ifndef NAIVE_BAYES_BOARD_H
#define NAIVE_BAYES_BOARD_H
#include <core/Card.h>
#include <vector>
//class naivebayes::Player;
#include <core/Player.h>
#include <stdexcept>
using std::vector;
namespace naivebayes {
    class Board {
    public:
        Board(size_t seed);
        Board();
        void add_players(vector<Player*> players, size_t num_decks);
        void add_players(vector<Player*> players);
        Card draw();
        void print(ostream& out);
        bool turn();
        size_t select_best_rank();
        void discard_card(Card card);
        void start_game();
        bool step();
        bool is_over();
        string game_summary();
        bool is_jack();
        void place_jack(size_t rank);
        bool is_rank_good(size_t rank);
        void get_summary(Card* hand, size_t player_num);
    private:
        vector<Card> stock;
        vector<Player*> players;
        vector<Card> discard;
        size_t current_player;
        bool is_done;
        //stock pile deck of cards based on # of players
        void get_deck(size_t num_decks);
        void shuffle();
    };
}

#endif //NAIVE_BAYES_BOARD_H
