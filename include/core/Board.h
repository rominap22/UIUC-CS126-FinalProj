#ifndef GARBAGE_BOARD_H
#define GARBAGE_BOARD_H
#include <core/Card.h>
#include <vector>
#include <core/Player.h>
#include <stdexcept>
using std::vector;
namespace garbage {
    class Board {
    public:
        Board(size_t seed);
        Board();
        /**
         * Adds players and number of decks to the game, shuffles the cards,
         * and sets the current player to the first player.
         * @param players number of players
         * @param num_decks number of decks of cards to be shuffled
         */
        void add_players(vector<Player*> players, size_t num_decks);
        /**
         * Adds players to game by calling above add_players function but
         * is extensible to more than 2 players.
         * @param players number of players
         */
        void add_players(vector<Player*> players);
        /**
         * Remove last card from top of stock pile.
         * (If empty stock, sets stock equal to discard, shuffles it,
         * and draws from stock)
         * @return Card drawn as top card from stock pile
         */
        Card draw();
        /**
         *
         * @param out
         * @param player_num
         */
        void print(ostream& out, size_t player_num);
        void print(ostream& out);
        bool turn();
        size_t select_best_rank();
        void discard_card(Card card);
        void start_game();
        bool step();
        bool is_over();
        string game_summary();
        bool is_jack();
        void place_jack(size_t rank);
        bool is_rank_good(size_t rank);
        void get_summary(Card* hand, size_t player_num);
        Card get_last_discard();
    private:
        vector<Card> stock;
        vector<Player*> players;
        vector<Card> discard;
        size_t current_player;
        bool is_done;
        //stock pile deck of cards based on # of players
        void get_deck(size_t num_decks);
        size_t num_of_suits;
        void shuffle();
    };
}

#endif //GARBAGE_BOARD_H
