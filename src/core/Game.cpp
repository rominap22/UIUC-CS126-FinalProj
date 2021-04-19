//
// Created by romip on 4/17/2021.
//

#include "core/Game.h"
#include "core/Card.h"
#include "core/Player.h"
#include "core/Board.h"
#include <time.h>
using std::vector;
namespace naivebayes {
    Game::Game(size_t num_players) {
        //diff set of #'s every game
        board = new Board((size_t) time(NULL));  //time elapsed in unix time
        //number of players
        vector<Player*> players;
        for (size_t i = 0; i < num_players; i++) {
            string name = "Player ";
            name.append(1, (char) ((size_t) '1' + i));
            players.push_back(new Player(name, board));
        }
        board->add_players(players, players.size() / 2);
        board->start_game();
    }

    void Game::print() {
        board->print(std::cout);
    }
    void Game::play_game() {
        bool is_done = false;
        while (!is_done) {
            is_done = board->turn();
        }
    }
}