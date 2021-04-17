//
// Created by romip on 4/17/2021.
//

#ifndef NAIVE_BAYES_PLAYER_H
#define NAIVE_BAYES_PLAYER_H
#include <string>
#include <core/Card.h>
#include <core/Board.h>
class Game;
using std::string;
namespace naivebayes {
    class Player {
    public:
        Player(string name, Board& board);
        void add_card(Card card);
        void print();
        void turn();
    private:
        string name;
        vector<Card> hand;
        vector<bool> face_up;
        Board& board;
    };
}

#endif //NAIVE_BAYES_PLAYER_H
