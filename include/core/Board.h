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
        void add_players(vector<Player*> players, size_t num_decks);
        Card draw();
        void print(ostream& out);
        bool turn();
        size_t select_best_rank(string for_player);
        void discard_card(Card card);
        void start_game();
    private:
        vector<Card> stock;
        vector<Player*> players;
        vector<Card> discard;

        //stock pile deck of cards based on # of players
        void get_deck(size_t num_decks);
        void shuffle();
    };
}

#endif //NAIVE_BAYES_BOARD_H
