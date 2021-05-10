//
// Created by romip on 4/17/2021.
//

#include "core/Player.h"
#include <iostream>
#include <core/Game.h>
using std::cout;
using std::endl;
namespace naivebayes {
    Player::Player(string name, Board* board):name{name}, board{board}, is_playable{false} {
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
        if (is_playable) {
            out<<" Card to be played: "<<to_be_played;
        } else {
            out<<" Turn over.";
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
        return true;
    }
    bool Player::step() {
        Card card = next_card();
        std::cout<<name<<" is playing "<<card<<std::endl;
        is_playable = false;
        if (!card.is_k_or_q() && !is_game_over()) {  //while Ace through Jack
            is_playable = true;
            size_t selected_rank = card.get_rank_int(); //get the rank of the card
            if (card.get_rank_int() == 11) {    //jack / wild card
                //keeping track if the card is face up or face down (face up if it gets replaced)
                selected_rank = board->select_best_rank(name);
            }
            if (hand[selected_rank - 1].get_face_up() &&
                  (hand[selected_rank - 1].get_rank_int() != 11)) {
                //skip over any non-Jack card that is already face up
                std::cout << "did not play " << card << " since " << hand[selected_rank - 1]
                          << " was face up" << std::endl;
                is_playable = false;
            } else {
                Card layout_card = hand[selected_rank - 1]; //card that was replaced on the board
                //make card visible
                card.set_face_up(true);
                hand[selected_rank - 1] = card; //swaps card drawn with card on board
                card = layout_card;
                print(cout);
                card.set_face_up(true);
                //std::cout<<name<<" is playing "<<card<<std::endl;
            }
        }
        if (is_playable) {
            //save the card
            to_be_played = card;
        } else {
            card.set_face_up(false);
            board->discard_card(card);
        }
        return !is_playable;    //turn is over
    }
    Card Player::next_card() {  //for printing card to be drawn
        if (is_playable) {
            return to_be_played;
        }
        to_be_played = board->draw();
        to_be_played.set_face_up(true);
        is_playable = true;
        return to_be_played;
    }
}
