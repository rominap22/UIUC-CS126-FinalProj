//
// Created by romip on 4/17/2021.
//

#include "core/Player.h"
#include <iostream>
#include <core/Game.h>
using std::cout;
using std::endl;
namespace naivebayes {
    Player::Player(string name, Board* board):name{name}, board{board}, is_playable{false},
                        was_discarded{false}, has_started{false}, is_winner{false}, is_rank_jack{false} {
    }
    Player::Player():name{""}, board{new Board(1)} {

    }
    void Player::add_card(Card card) {
        hand.push_back(card);
    }
    void Player::print(ostream& out) {
        out<<name<<": ";
        /*if (is_playable) {
            out<<"Card to be played is "<<to_be_played<<": ";
        }*/
        for (size_t i = 0; i < hand.size(); i++) {
            if (i != 0) {
                out<<", ";
            }
            out<<hand[i];
        }
        if (is_winner) {
            out<<" has won";
        } else if (is_playable) {
            out<<" Card to be played: "<<to_be_played;
        } else {
            if (was_discarded) {
                discarded_card.set_face_up(true);
                out<<" Turn over. Could not play "<<discarded_card;
                was_discarded = false;
            } else {
                if (has_started) {
                    out<<" Turn over.";
                }
            }
        }
        out<<endl;
    }
    void Player::turn() {
        Card card = board->draw();
        card.set_face_up(true);
        std::cout<<name<<" is playing "<<card<<std::endl;

        while (!card.is_k_or_q() && !is_game_over()) {  //while Ace through Jack
            size_t selected_rank = card.get_rank_int(); //get the rank of the card
            if (card.get_rank_int() == 11) {    //jack / wild card
                //keeping track if the card is face up or face down (face up if it gets replaced)
                selected_rank = board->select_best_rank(name);
            } else {
                //skip over any non-Jack card that is already face up
                if (hand[selected_rank - 1].get_face_up() &&
                        (hand[selected_rank - 1].get_rank_int() != 11)) {
                    std::cout<<"did not play "<<card<<" since "<<hand[selected_rank - 1]
                                <<" was face up"<<std::endl;
                    break;
                }
            }
            Card layout_card = hand[selected_rank - 1]; //card that was replaced on the board
            //make card visible
            card.set_face_up(true);
            hand[selected_rank - 1] = card; //swaps card drawn with card on board
            card = layout_card;
            print(cout);
            card.set_face_up(true);
            std::cout<<name<<" is playing "<<card<<std::endl;
            //if same rank, then stop
            /*if (card.get_rank_int() == hand[selected_rank - 1].get_rank_int()) {
                break;
            }*/
        }
        card.set_face_up(false);
        board->discard_card(card);
    }
    string Player::get_name() {
        return name;
    }
    bool Player::is_face_up(size_t rank) {
        return hand[rank - 1].get_face_up();
    }
    bool Player::is_game_over() {
        //iterate over hand
        for (size_t i = 0; i < hand.size(); i++) {
            if (!hand[i].get_face_up()) {
                return false;
            }
        }
        //all should be face up
        is_winner = true;
        return true;
    }
    bool Player::step() {
        was_discarded = false;
        has_started = true;
        Card card = next_card();    //return playable card or draw new one
        std::cout<<name<<" is playing "<<card<<std::endl;
        is_playable = false;
        size_t selected_rank = 0; //get the rank of the card
        if (!card.is_k_or_q() && !is_game_over()) {  //while Ace through Jack
            is_playable = true;
            size_t selected_rank = card.get_rank_int(); //get the rank of the card
            if (card.get_rank_int() == 11) {    //jack / wild card
                //keeping track if the card is face up or face down (face up if it gets replaced)
                //selected_rank = board->select_best_rank(name);
                //is_rank_jack = true;
                //discarded_card = card;  //stores Jack temporarily
                std::cout<<"Jack should not be played from this point"<<std::endl;
            } else if (hand[selected_rank - 1].get_face_up() &&
                  (hand[selected_rank - 1].get_rank_int() != 11)) {
                is_playable = false;
            } else {
                Card layout_card = hand[selected_rank - 1]; //card that was replaced on the board
                //make card visible
                card.set_face_up(true);
                hand[selected_rank - 1] = card; //swaps card drawn with card on board
                card = layout_card;
                if (card.get_rank_int() == 11) {
                    is_rank_jack = true;
                }
                print(cout);
                card.set_face_up(true);
                //std::cout<<name<<" is playing "<<card<<std::endl;
                std::cout<<"player line 128: "<<is_rank_jack<<" "<<card<<" "<<is_playable<<std::endl;
            }
        }
        if (is_winner) {
            std::cout<<name<<" has won"<<std::endl;
            return false;
        }
        if (is_playable) {
            //save the card
            to_be_played = card;
        } else {
            //skip over any non-Jack card that is already face up
            if (selected_rank == 0) {
                std::cout<<card<<" is not playable"<<std::endl;
            } else {
                std::cout << "did not play " << card << " since " << hand[selected_rank - 1]
                          << " was face up" << std::endl;
            }
            was_discarded = true;
            discarded_card = card;
            card.set_face_up(false);
            board->discard_card(card);
        }
        std::cout<<"player line 155: "<<name<<" is playable"<<is_playable<<" is jack: "<<is_rank_jack
        <<" was discarded: "<<was_discarded<<" to be played: "<<to_be_played<<std::endl;
        return !is_playable;    //turn is over
    }
    Card Player::next_card() {  //for printing card to be drawn
        if (is_playable) {
            return to_be_played;
        }
        to_be_played = board->draw();
        to_be_played.set_face_up(true);
        is_rank_jack = to_be_played.get_rank_int() == 11;
        is_playable = true;
        return to_be_played;
    }
    bool Player::is_jack() {
        return is_rank_jack;
    }
    bool Player::is_rank_good(size_t rank) {
        //if rank face down
        std::cout<<"player line 172: "<<rank<<" "<<hand[rank - 1].get_face_up()<<std::endl;
        return (!hand[rank - 1].get_face_up());
    }
    void Player::place_jack(size_t rank) {
        Card jack = to_be_played;
        to_be_played = hand[rank - 1]; //card that was replaced on the board
        //make card visible
        jack.set_face_up(true);
        hand[rank - 1] = jack; //swaps card drawn with card on board
        print(cout);
        to_be_played.set_face_up(true);
        std::cout<<name<<" play jack next card is "<<to_be_played<<std::endl;
        is_rank_jack = to_be_played.get_rank_int() == 11;
    }
}
