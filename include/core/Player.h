//
// Created by romip on 4/17/2021.
//

#ifndef NAIVE_BAYES_PLAYER_H
#define NAIVE_BAYES_PLAYER_H
#include <string>
#include <core/Card.h>
using std::string;
using std::vector;
namespace naivebayes {
    class Board;
    class Player {
    public:
        Player();
        Player(string name, Board* board);
        void add_card(Card card);
        void print(ostream& out);
        void turn();
        string get_name();
        bool is_face_up(size_t rank);
        bool is_game_over();
        bool step();
        Card next_card();
    private:
        string name;
        vector<Card> hand;
        Board* board;
        bool is_playable;
        Card to_be_played;
    };
}

#endif //NAIVE_BAYES_PLAYER_H
