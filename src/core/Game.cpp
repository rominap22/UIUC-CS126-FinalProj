//
// Created by romip on 4/17/2021.
//

#include "core/Game.h"
#include "core/Card.h"
#include "core/Player.h"
#include "core/Board.h"
#include <time.h>
#include <sstream>
using std::vector;
using std::stringstream;
namespace naivebayes {
    Game::Game(size_t num_players):Game(num_players, (size_t) time(NULL)) {
    }
    Game::Game():Game(2) {

    }
    Game::Game(size_t num_players, size_t seed) {
        //diff set of #'s every game
        board = new Board(seed);  //time elapsed in unix time
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
    string Game::to_string() {
        stringstream ss;
        board->print(ss);
        return ss.str();
    }
    void Game::play_game() {
        bool is_done = false;
        while (!is_done) {
            is_done = board->turn();
        }
    }
    bool Game::turn() {
        return board->turn();
    }
    bool Game::step() {
        return board->step();
    }
    bool Game::is_over() {
        return board->is_over();
    }
    string Game::game_summary() {
        return board->game_summary();
    }
}