//
// Created by romip on 4/17/2021.
//

#ifndef NAIVE_BAYES_BOARD_H
#define NAIVE_BAYES_BOARD_H
#include <core/Card.h>
#include <vector>
//class naivebayes::Player;
#include <core/Player.h>
using std::vector;
namespace naivebayes {
    class Board {
    public:
        Board();
        void add_players(vector<Player*> players);
        //stock pile deck of cards
        void get_deck(size_t num_decks);
        void shuffle();
        Card draw();
        void print();
        bool turn();
        size_t select_best_rank(string for_player);
        void discard_card(Card card);
    private:
        vector<Card> stock;
        vector<Player*> players;
        vector<Card> discard;
    };
}

#endif //NAIVE_BAYES_BOARD_H
