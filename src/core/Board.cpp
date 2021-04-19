//
// Created by romip on 4/17/2021.
//

#include "core/Board.h"
#include <core/Player.h>
#include <stdexcept>
using std::vector;
namespace naivebayes {
    Board::Board(size_t seed) { //forcing same random sequence
        srand(seed);    //seed random function
        std::cout<<"seed = "<<seed<<std::endl;
    }
    void Board::add_players(vector<Player*> players, size_t num_decks) {
        if (players.size() < 2) {
            throw std::invalid_argument("must have at least 2 players");
        }
        for (size_t i = 0; i < players.size(); i++) {
            if (players[i] == nullptr) {
                throw std::invalid_argument("player is null");
            }
        }
        this->players = players;
        this->get_deck(num_decks);     //number of decks
        this->shuffle();
    }
    //stock pile deck of cards
    void Board::get_deck(size_t num_decks) {
        //size_t num_decks = players.size() / 2;
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
                        break;
                    case 1:
                        suit = Card::DIAMONDS;
                        break;
                    case 2:
                        suit = Card::HEARTS;
                        break;
                    case 3:
                        suit = Card::SPADES;
                        break;
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
            std::cout<<"draw"<<std::endl;
            stock = discard;
            discard.empty();    //clear the discard
            shuffle();
            std::cout<<"XXXXXXXXXXXXXXXXXXXXX shuffle discard: size = "<<stock.size()<<std::endl;
        }
        Card card = stock[stock.size() - 1];    //last card
        stock.pop_back();                   //remove last card from stock
        return card;
    }
    void Board::print(ostream& out) {
        for (size_t i = 0; i < players.size(); i++) {
            players[i]->print(out);
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
                count[rank - 1] = -1;
            }
        }
        //find max index in count
        int max_count = -1;
        size_t max_idx = 0;
        for (size_t i = 0; i < count.size(); i++) {
            if ((int) count[i] > max_count) {
                max_count = count[i];
                max_idx = i;
            }
        }
        return max_idx + 1; //returns rank
    }
    void Board::discard_card(Card card) {
        discard.push_back(card);
    }
    void Board::start_game() {
        //dealing 10 cards face down to each player
        for (size_t i = 0; i < 10; i++) {
            for (size_t i = 0; i < players.size(); i++) {
                Card card = draw();
                players[i]->add_card(card);          //deal the card to the player
            }
        }
    }
}