//
// Created by romip on 4/17/2021.
//

#ifndef NAIVE_BAYES_BOARD_H
#define NAIVE_BAYES_BOARD_H
#include <core/Card.h>
#include <vector>
using std::vector;
namespace naivebayes {
    class Board {
    public:
        //stock pile deck of cards
        void get_deck(size_t num_decks);
        void shuffle();
        Card draw();
    private:
        vector<Card> stock;
    };
}

#endif //NAIVE_BAYES_BOARD_H
