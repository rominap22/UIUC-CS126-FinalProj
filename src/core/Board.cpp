//
// Created by romip on 4/17/2021.
//

#include "core/Board.h"
#include <core/Player.h>
using std::vector;
namespace naivebayes {
    Board::Board() {
    }
    void Board::add_players(vector<Player*> players) {
        this->players = players;
    }
    //stock pile deck of cards
    void Board::get_deck(size_t num_decks) {
        //clear stock
        stock.clear();
        //iterating over number of decks
        for (size_t nd = 0; nd < num_decks; nd++) {
            //iterating over enum suit types
            for (size_t i = 0; i < 4; i++) {
                Card::SUITS suit;
                switch (i) {
                    case 0:
                        suit = Card::CLUBS;
                    case 1:
                        suit = Card::DIAMONDS;
                    case 2:
                        suit = Card::HEARTS;
                    case 3:
                        suit = Card::SPADES;
                }
                //iterating over the ranks (Ace, 2-10, Jack, Queen, King)
                for (size_t rank = 1; rank <= 13; rank++) {
                    stock.push_back(Card(rank, suit));
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
        if (stock.empty()) {
            stock = discard;
            shuffle();
        }
        Card card = stock[stock.size() - 1];    //last card
        stock.pop_back();                   //remove last card from stock
        return card;
    }
    void Board::print() {
        for (size_t i = 0; i < players.size(); i++) {
            players[i]->print();
        }
    }
    bool Board::turn() {
        for (size_t i = 0; i < players.size(); i++) {
            players[i]->turn();
            std::cout<<players[i]->get_name()<<" turn over"<<std::endl;
            std::cout<<"################################"<<std::endl<<std::endl;
            if (players[i]->is_game_over()) {
                std::cout<<players[i]->get_name()<<" has won"<<std::endl;
                return true;
            }
        }
        return false;
    }
    size_t Board::select_best_rank(string for_player) { //for jacks
        //checks for first face down
        vector<size_t> count(10, 0);    //array of 10 zeros
        //iterate through players
        Player* this_player;
        for (size_t i = 0; i < players.size(); i++) {
            if (players[i]->get_name() == for_player) {
                this_player = players[i];
                continue;
            }
            for (size_t rank = 1; rank <= 10; rank++) { //counting all face up cards minus our own
                if (players[i]->is_face_up(rank)) {
                    count[rank - 1]++;
                }
            }
        }
        for (size_t rank = 1; rank <= 10; rank++) { //ignore already face up ones
            if (this_player->is_face_up(rank)) {
                count[rank - 1] = 0;
            }
        }
        //find max index in count
        size_t max_count = 0;
        size_t max_idx = 0;
        for (size_t i = 0; i < count.size(); i++) {
            if (count[i] > max_count) {
                max_count = count[i];
                max_idx = i;
            }
        }
        return max_idx + 1; //returns rank
    }
    void Board::discard_card(Card card) {
        discard.push_back(card);
    }
}