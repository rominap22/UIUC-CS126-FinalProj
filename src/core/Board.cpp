//
// Created by romip on 4/17/2021.
//

#include "core/Board.h"
namespace naivebayes {
    //stock pile deck of cards
    void Board::get_deck(size_t num_decks) {
        //clear stock
        stock.clear();
        //iterating over number of decks
        for (size_t nd = 0; nd < num_decks; nd++) {
            //iterating over enum suit types
            for (size_t i = 0; i < 4; i++) {
                //iterating over the ranks (Ace, 2-10, Jack, Queen, King)
                for (size_t rank = 1; rank <= 13; rank++) {
                    stock.push_back(Card(rank, SuitList[i]));
                }
            }
        }
    }
    void Board::shuffle() {
        //shuffle 100 times
        for (size_t i = 0; i < 100; i++) {
            //randomly shuffle cards
            size_t card1 = rand() % stock.size();
            size_t card2 = rand() % stock.size();
            if (card1 != card2) {   //swap
                Card temp = stock[card1];
                stock[card1] = stock[card2];
                stock[card2] = temp;
            }
        }
    }
    Card Board::draw() {
        Card card = stock[stock.size() - 1];    //last card
        stock.pop_back();                   //remove last card from stock
        return card;
    }
}