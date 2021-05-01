#ifndef GARBAGE_PLAYER_H
#define GARBAGE_PLAYER_H
#include <string>
#include <core/Card.h>
using std::string;
using std::vector;
namespace garbage {
    class Board;
    class Player {
    public:
        Player();
        Player(string name, Board* board);
        void add_card(Card card);
        void print(ostream& out);
        void print_summary(ostream& out);
        void turn();
        string get_name();
        bool is_face_up(size_t rank);
        bool is_game_over();
        bool step();
        Card next_card();
        bool is_jack();
        void place_jack(size_t rank);
        bool is_rank_good(size_t rank);
        void get_summary(Card* hand);
    private:
        string name;
        vector<Card> hand;
        Board* board;
        bool is_playable;
        Card to_be_played;
        bool was_discarded;
        bool has_started;
        Card discarded_card;
        bool is_winner;
        bool is_rank_jack;
    };
}

#endif //GARBAGE_PLAYER_H
