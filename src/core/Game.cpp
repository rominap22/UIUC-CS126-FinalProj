//
// Created by romip on 4/17/2021.
//

#include "core/Game.h"
#include "core/Card.h"
#include "core/Player.h"
#include "core/Board.h"

namespace naivebayes {
    Game::Game(size_t num_players) {
        board.get_deck(num_players / 2);     //number of decks
        board.shuffle();
        //number of players
        for (size_t i = 0; i < num_players; i++) {
            string name = "Player ";
            name.append(1, (char) ((size_t) '1' + i));
            players.push_back(Player(name, board));
        }
        //dealing 10 cards face down to each player
        for (size_t i = 0; i < 10; i++) {
            for (size_t i = 0; i < num_players; i++) {
                Card card = board.draw();
                players[i].add_card(card);          //deal the card to the player
            }
        }
    }

    void Game::print() {
        for (size_t i = 0; i < players.size(); i++) {
            players[i].print();
        }
    }
    void Game::play_game() {
        bool is_done = false;
        while (!is_done) {
            for (size_t i = 0; i < players.size(); i++) {
                players[i].turn();
            }
            is_done = true;
        }
    }
}