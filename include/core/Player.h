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
        //setting each player's name and hand
        Player(string name, Board* board);
        /**
         * Adds a card to a player's hand
         * @param card Card to be added to player's hand
         */
        void add_card(Card card);
        /**
         * For Cinder app:
         * Printing out if player has won, card to be played, or if the turn is over
         * and could not play a card, or if turn is over after sequence of played cards
         * @param out output from state of game based on played/unplayed cards
         */
        void print(ostream& out);
        /**
         * For console:
         * Printing out if player has won, card to be played, or if the turn is over
         * and could not play a card, or if turn is over after sequence of played cards
         * @param out output from state of game based on played/unplayed cards
         * @param out
         */
        void print_summary(ostream& out);
        /**
         * Takes a turn for a player by getting the rank, skipping over any card that
         * is not a Jack and face up, swaps drawn card with card on the board at that rank,
         * set card to face up, add replaced card to discard pile
         */
        void turn();
        /**
         * Gets the name of the player
         * @return name of player as a string
         */
        string get_name();
        /**
         * Checks if the passed in rank in the hand is face up
         * @param rank number of the card to be checked
         * @return true if card of that rank is face up, false if not
         */
        bool is_face_up(size_t rank);
        /**
         * Iterates over entire player's hand to ensure that all cards are face up
         * which means that game is over because that player won
         * @return true if all cards are face up in a hand, false otherwise
         */
        bool is_game_over();
        /**
         * Takes each intermediate step of a player's turn by getting rank of card,
         * asking for rank to replace if Jack, replace card on the board with drawn
         * or user-chosen card of that rank, sets card to face up, adds drawn card to discard,
         * checks if game is over or unplayable card
         * @return true if intermediate step is over and card successfully replaced,
         * false otherwise
         */
        bool step();
        /**
         * Checks if card is playable and draws the next card to be played
         * @return Card that should next be drawn from stock pile
         */
        Card next_card();
        /**
         * Check if card is a Jack
         * @return true if card is a jack, false if not
         */
        bool is_jack();
        /**
         * Replaces the card on the board at the passed in rank with Jack
         * @param rank number of card to be checked
         */
        void place_jack(size_t rank);
        /**
         * Checks if passed in rank is valid - card should be face down,
         * player should not have won yet
         * @param rank number of card to be checked
         * @return true if rank is valid based on above conditions, false otherwise
         */
        bool is_rank_good(size_t rank);
        /**
         * Gets the summary of the state of the game in terms of the player's hand,
         * card to be played if playable (or an empty Card obj if not playable)
         * @param hand list of 10 cards dealt to the player that constitutes their "board"
         */
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
