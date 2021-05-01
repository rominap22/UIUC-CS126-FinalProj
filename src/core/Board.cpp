//
// Created by romip on 4/17/2021.
//

#include "core/Board.h"
#include <core/Player.h>
#include <stdexcept>
#include <time.h>
using std::vector;
namespace garbage {
    Board::Board(size_t seed):current_player{0}, is_done{true},
                            num_of_suits{4} { //forcing same random sequence
        srand(seed);    //seed random function
        std::cout<<"seed = "<<seed<<std::endl;
    }
    Board::Board():Board((size_t) time(NULL)) {}

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
        current_player = players.size() - 1;
    }
    void Board::add_players(vector<Player*> players) {
        add_players(players, players.size() / 2);
    }
    //stock pile deck of cards
    void Board::get_deck(size_t num_decks) {
        //size_t num_decks = players.size() / 2;
        //clear stock
        stock.clear();
        //iterating over number of decks
        for (size_t nd = 0; nd < num_decks; nd++) {
            //iterating over enum suit types
            for (size_t i = 0; i < num_of_suits; i++) {
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
        std::cout<<"board line 79 draw: "<<stock.size()<<", "<<discard.size()<<std::endl;
        if (stock.empty()) {
            stock = discard;
            discard.empty();    //clear the discard
            shuffle();
        }
        Card card = stock[stock.size() - 1];    //last card
        stock.pop_back();                   //remove last card from stock
        return card;
    }
    void Board::print(ostream& out, size_t player_num) {
        //for (size_t i = 0; i < players.size(); i++) {
            players[player_num]->print(out);
        //}
    }
    void Board::print(ostream& out) {
        for (size_t i = 0; i < players.size(); i++) {
            players[i]->print_summary(out);
        }
    }
    bool Board::turn() {
        for (size_t i = 0; i < players.size(); i++) {
            players[i]->turn();
            std::cout<<players[i]->get_name()<<" turn over"<<std::endl;
            if (players[i]->is_game_over()) {
                std::cout<<players[i]->get_name()<<" has won"<<std::endl;
                return true;
            }
        }
        return false;
    }
    size_t Board::select_best_rank() { //for jacks
        //checks for first face down
        vector<size_t> count(10, 0);    //array of 10 zeros
        //iterate through players
        Player* this_player = players[current_player];
        for (size_t i = 0; i < players.size(); i++) {
            /*if (players[i]->get_name() == for_player) {
                this_player = players[i];
                continue;
            }*/
            if (i == current_player) {
                continue;
            }   //most frequently face up card is what we want
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
    bool Board::step() {    //intermediate sequence of replacing cards
        if (is_done) {  //if done, go to next player
            current_player = (current_player + 1) % players.size();
            players[current_player]->next_card();   //draws the next card

            is_done = false;
            return false;
        }
        is_done = players[current_player]->step();  //take turn
        if (is_done) {  //if 2nd player done, turn over
            std::cout<<players[current_player]->get_name()<<" turn over"<<std::endl;
        }
        if (players[current_player]->is_game_over()) {
            std::cout<<players[current_player]->get_name()<<" has won"<<std::endl;
            return true;
        }
        return is_done;
    }
    bool Board::is_over() {
        for (size_t i = 0; i < players.size(); i++) {
            if (players[i]->is_game_over()) {
                return true;
            }
        }
        return false;
    }
    string Board::game_summary() {
        for (size_t i = 0; i < players.size(); i++) {
            if (players[i]->is_game_over()) {
                return players[i]->get_name() + " has won!";
            }
        }
        return "no winner yet";
    }
    bool Board::is_jack() {
        std::cout<<"board line 182: "<<current_player<<" "<<players[current_player]->is_jack()<<std::endl;
        return players[current_player]->is_jack();
    }
    void Board::place_jack(size_t rank) {
        players[current_player]->place_jack(rank);
    }
    bool Board::is_rank_good(size_t rank) {
        return players[current_player]->is_rank_good(rank);
    }
    void Board::get_summary(Card* hand, size_t player_num) {
        players[player_num]->get_summary(hand);
    }
    Card Board::get_last_discard() {
        if (discard.empty()) {
            return Card();  //game has not started yet (no cards in discard)
        } else {
            return discard[discard.size() - 1]; //last discarded card
        }
    }
}