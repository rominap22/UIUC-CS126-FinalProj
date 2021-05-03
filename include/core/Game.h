#ifndef GARBAGE_GAME_H
#define GARBAGE_GAME_H
#include <core/Player.h>
#include <core/Card.h>
#include <core/Board.h>
namespace garbage {
    class Game {
    public:
        //for setting a game of any number of at least 2 players
        Game(size_t num_players);
        Game();
        //for setting a game of any number of at least 2 players
        //plus generating a seed for a random sequence of #'s for each game
        Game(size_t num_players, size_t seed);
        ~Game();
        /**
         * Prints the board for the passed in player
         * @param player_num the player we are referring to (e.g. Player 1)
         * @return printed player's hand as a string
         */
        string to_string(size_t player_num);
        /**
         * Prints the board for any player
         * @return printed player's hand as a string
         */
        string to_string();
        /**
         * Gets the summary of each player's hand on the screen.
         * @param hand list of 10 cards dealt to the player that constitutes their "board"
         * @param player_num the player we are referring to (e.g. Player 1)
         */
        void get_summary(Card* hand, size_t player_num);
        /**
         * Plays one iteration of the game with correctly stepping, placing jacks
         * as necessary by selecting best rank for jack
         */
        void play_game();
        /**
         * Takes one turn of the game for a player (call's board's turn function)
         * @return true if turn is over, false otherwise (card unplayable or player won)
         */
        bool turn();
        /**
         * Takes one step of the game for a player's turn (call's board's step function)
         * @return true if player has won, false otherwise
         */
        bool step();
        /**
         * Checks if game is over (call's board's is_over function)
         * @return true if the game is over, false otherwise
         */
        bool is_over();
        /**
         * Prints state of game (game summary) as a string w/ each player's hands
         * (calls board's game_summary function)
         * @return outputted player's hands and playable cards as a string
         */
        string game_summary();
        /**
         * Checks if the card is a jack (call's board's is_jack function)
         * @return true if card is jack, false if not
         */
        bool is_jack();
        /**
         * Places jack at the position of the passed in rank and replaces
         * the face down card at that position with jack
         * @param rank number of the card to be replaced by Jack
         */
        void place_jack(size_t rank);
        /**
         * Checks if rank is a valid rank - card should be face down
         * and player has not won yet
         * @param rank number of the card to be checked
         * @return true if the rank is valid based on above conditions
         */
        bool is_rank_good(size_t rank);
        /**
         * Selects best rank based on board's function for select_best_rank
         * @return optimal rank based on method from board
         */
        size_t select_best_rank();
        /**
         * Gets the last added card to the discard pile based on board's function
         * for get_last_discard
         * @return Card last added to discard pile
         */
        Card get_last_discard();
    private:
        Board* board;
    };
}


#endif //GARBAGE_GAME_H
