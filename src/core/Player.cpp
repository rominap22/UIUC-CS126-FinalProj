//
// Created by romip on 4/17/2021.
//

#include "core/Player.h"
#include <iostream>
#include <core/Game.h>
using std::cout;
using std::endl;
namespace naivebayes {
    Player::Player(string name, Board& board):name{name}, board{board} {
    }
    void Player::add_card(Card card) {
        hand.push_back(card);
    }
    void Player::print() {
        cout<<name<<": ";
        for (size_t i = 0; i < hand.size(); i++) {
            cout<<hand[i]<<", ";
        }
        cout<<endl;
    }
    void Player::turn() {
        Card card = board.draw();
        while (!card.is_k_or_q()) {  //while Ace through Jack
            Card hand_card = hand[card.get_rank_int()];
            if (card.get_rank() == "11") {    //jack / wild card
                //keeping track if the card is face up or face down (face up if it gets replaced)
            }
        }
    }
}
