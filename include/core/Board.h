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
         * Prints each player's list of ranks
         * @param out output of the player's ranks
         * @param player_num the player we are referring to (e.g. Player 1)
         */
        void print(ostream& out, size_t player_num);
        /**
         * Prints player's hand, printing each card,
         * otherwise prints if player has won or if card cannot be played
         * since it is already face up
         * @param out output of the player's hand
         */
        void print(ostream& out);
        /**
         * Takes one turn of the player, going through as many steps of a turn
         * as necessary before the turn is over or if the player has won
         * @return true if the player is won, false otherwise
         */
        bool turn();
        /**
         * For jacks, checks for first face down card and also the most frequently
         * face up card among other players since this selected card is less likely
         * to not come up again
         * @return rank that results from the above strategy
         */
        size_t select_best_rank();
        /**
         * Adds the passed in card to the top of the discard pile.
         * @param card Card to be added to the discard pile
         */
        void discard_card(Card card);
        /**
         * Draws cards from the stock pile and deals ten to each player.
         * Adds each card to their respective player's hand.
         */
        void start_game();
        /**
         * Intermediate steps of replacing cards per turn of a player.
         * Keeps replacing until card cannot be played because either
         * player has won or card is already face up
         * @return true if the turn is done, false otherwise
         */
        bool step();
        /**
         * Checks if the game is over for each player.
         * @return true if game is over, false otherwise
         */
        bool is_over();
        /**
         * Checks if each player won, outputs if a player has won
         * or if there is no winner yet
         * @return string output that either a player has won
         * or string output that there is no winner yet
         */
        string game_summary();
        /**
         * Checks if the current player's card is a Jack.
         * @return true if Jack, false if not
         */
        bool is_jack();
        /**
         * Places Jack at the specified location on the player board based on
         * passed in rank
         * @param rank number of the card to be replaced by Jack
         */
        void place_jack(size_t rank);
        /**
         * Checks if the rank passed in is a valid rank to be played
         * (i.e. card is face down and player has not won yet)
         * @param rank number of the card to be checked
         * @return true if the rank is a valid one as described above, false otherwise
         */
        bool is_rank_good(size_t rank);
        /**
         * Gets the summary of the hand of the passed in player (e.g. Player 2's hand)
         * @param hand list of 10 cards dealt to the player that constitutes their "board"
         * @param player_num the player we are referring to (e.g. Player 1)
         */
        void get_summary(Card* hand, size_t player_num);
        /**
         * Puts the latest discarded card into the discard pile
         * or puts an empty Card obj if the discard pile is empty
         * @return latest added card that is added to discard pile
         */
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
