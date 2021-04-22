#include <catch2/catch.hpp>

#include <core/Card.h>
#include <sstream>
#include <core/Board.h>
#include <core/Player.h>
#include <core/Game.h>
using std::stringstream;
namespace naivebayes {
    //CARD TESTS
    TEST_CASE("Card face up") {
        Card card(1, Card::SUITS::HEARTS);
        REQUIRE(card.get_face_up() == false);
        card.set_face_up(true);
        REQUIRE(card.get_face_up() == true);
        card.set_face_up(false);
        REQUIRE(card.get_face_up() == false);
    }
    TEST_CASE("Card get rank") {
        string ranks[13] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
        for (size_t rank = 1; rank <= 13; rank++) {
            Card card(rank, Card::SUITS::HEARTS);
            REQUIRE(card.get_rank_int() == rank);
            REQUIRE(card.get_rank() == ranks[rank - 1]);
        }
    }
    TEST_CASE("Card get suit") {
        string suits[4] = {"Clubs", "Diamonds", "Hearts", "Spades"};

        Card card(1, Card::CLUBS);
        REQUIRE(card.get_suit() == suits[0]);
        Card card1(1, Card::DIAMONDS);
        REQUIRE(card1.get_suit() == suits[1]);
        Card card2(1, Card::HEARTS);
        REQUIRE(card2.get_suit() == suits[2]);
        Card card3(1, Card::SPADES);
        REQUIRE(card3.get_suit() == suits[3]);
    }
    TEST_CASE("Card is king or queen") {
        string ranks[13] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
        bool is_k_or_q = false;
        for (size_t rank = 1; rank <= 13; rank++) {
            Card card(rank, Card::SUITS::HEARTS);
            if (rank == 12 || rank == 13) {
                is_k_or_q = true;
            }
            REQUIRE(card.is_k_or_q() == is_k_or_q);
        }
    }
    TEST_CASE("Card is face up") {
        Card card(1, Card::SUITS::HEARTS);
        REQUIRE(card.get_face_up() == false);
        card.set_face_up(true);
        REQUIRE(card.get_face_up() == true);
        card.set_face_up(false);
        REQUIRE(card.get_face_up() == false);
    }
    TEST_CASE("Card operator<<") {
        Card card(1, Card::SUITS::HEARTS);
        SECTION("Face down card") {
            stringstream ss;
            ss<<card;
            REQUIRE(ss.str() == "____");
        }
        SECTION("Face up card") {
            card.set_face_up(true);
            stringstream ss1;
            ss1<<card;
            REQUIRE(ss1.str() == " A H");
        }
    }
    //PLAYER TESTS
    TEST_CASE("Player add card") {
        Board* board = new Board(1);
        Player player("Name", board);
        for (size_t i = 0;i < 10; i++) {
            Card card(10 - i, Card::HEARTS);
            player.add_card(card);
        }
        stringstream ss;
        player.print(ss);
        REQUIRE(ss.str() == "Name: ____, ____, ____, ____, ____, ____, ____, ____, ____, ____\n");
    }
    TEST_CASE("Player turn") {
        Board* board = new Board(1);
        Player* player1 = new Player("Player 1", board);
        Player* player2 = new Player("Player 2", board);
        vector<Player*> players;
        players.push_back(player1);
        players.push_back(player2);
        board->add_players(players, players.size() / 2);
        board->start_game();
        stringstream ss;
        board->print(ss);
        REQUIRE(ss.str() == "Player 1: ____, ____, ____, ____, ____, ____, ____, ____, ____, ____\n"
                            "Player 2: ____, ____, ____, ____, ____, ____, ____, ____, ____, ____\n");
    }
    TEST_CASE("Player get name") {
        Board* board = new Board(1);
        Player* player1 = new Player("Player 1", board);
        REQUIRE(player1->get_name() == "Player 1");
    }
    TEST_CASE("Player card check face up/down") {
        Board *board = new Board(1);
        Player *player1 = new Player("Player 1", board);
        Player *player2 = new Player("Player 2", board);
        vector<Player *> players;
        players.push_back(player1);
        players.push_back(player2);
        board->add_players(players, players.size() / 2);
        board->start_game();
        bool is_face_up[] = {false, false, false, false, false, true, false, false, true, true};
        //all face down before any play is made
        for (size_t rank = 1; rank <= 10; rank++) {
            REQUIRE(player1->is_face_up(rank) == false);
        }
        board->turn();
        for (size_t rank = 1; rank <= 10; rank++) {
            REQUIRE(player1->is_face_up(rank) == is_face_up[rank - 1]);
        }
        stringstream ss;
        player1->print(ss);
        REQUIRE(ss.str() == "Player 1: ____, ____, ____, ____, ____,  6 S, ____, ____,  9 D, 10 H\n");
    }
    TEST_CASE("Player game over") {
        Board *board = new Board(1);
        Player *player1 = new Player("Player 1", board);
        Player *player2 = new Player("Player 2", board);
        vector<Player *> players;
        players.push_back(player1);
        players.push_back(player2);
        board->add_players(players, players.size() / 2);
        board->start_game();
        size_t next = players.size() - 1;    //index of next player
        while (!player1->is_game_over() && !player2->is_game_over()) {
            next = (next + 1) % players.size();    //increment player / alternate (to avoid 0 for next)
            players[next]->turn();      //next points to last player
        }

        //require that all are face up for the winning player
        for (size_t rank = 1; rank <= 10; rank++) {
            REQUIRE(players[next]->is_face_up(rank) == true);
        }
        stringstream ss;
        players[next]->print(ss);
        REQUIRE(ss.str() == "Player 2:  J S,  2 H,  3 D,  4 C,  5 C,  J C,  7 H,  J D,  9 C, 10 S has won\n");
    }
    TEST_CASE("Board less than 2 players") {
        Board *board = new Board(1);
        Player *player1 = new Player("Player 1", board);
        vector<Player *> players;
        players.push_back(player1);
        REQUIRE_THROWS_AS(board->add_players(players, players.size() / 2),
                          std::invalid_argument);
    }
    TEST_CASE("Board add players") {
        Board *board = new Board(1);
        Player *player1 = new Player("Player 1", board);
        Player *player2 = new Player("Player 2", board);
        Player *player3 = new Player("Player 3", board);
        vector<Player *> players;
        players.push_back(player1);
        players.push_back(player2);
        players.push_back(player3);
        board->add_players(players, players.size() / 2);
        stringstream ss;
        board->print(ss);
        REQUIRE(ss.str() == "Player 1: \n"
                            "Player 2: \n"
                            "Player 3: \n");
    }
    TEST_CASE("Board 1 null player, 1 correct player") {
        Board *board = new Board(1);
        Player *player1 = new Player("Player 1", board);
        vector<Player *> players;
        players.push_back(nullptr);
        players.push_back(player1);
        REQUIRE_THROWS_AS(board->add_players(players, players.size() / 2),
                          std::invalid_argument);
    }
    TEST_CASE("Board draw") {
        Board *board = new Board(1);
        Player *player1 = new Player("Player 1", board);
        Player *player2 = new Player("Player 2", board);
        Player *player3 = new Player("Player 3", board);
        vector<Player *> players;
        players.push_back(player1);
        players.push_back(player2);
        players.push_back(player3);
        board->add_players(players, players.size() / 2);
        Card card = board->draw();
        REQUIRE(card.get_rank_int() == 5);
        REQUIRE(card.get_suit() == "Diamonds");
        REQUIRE(card.get_face_up() == false);
    }
    TEST_CASE("Board print") {
        Board *board = new Board(1);
        Player *player1 = new Player("Player 1", board);
        Player *player2 = new Player("Player 2", board);
        Player *player3 = new Player("Player 3", board);
        vector<Player *> players;
        players.push_back(player1);
        players.push_back(player2);
        players.push_back(player3);
        board->add_players(players, players.size() / 2);
        stringstream ss;
        board->print(ss);
        REQUIRE(ss.str() == "Player 1: \n"
                            "Player 2: \n"
                            "Player 3: \n");
        board->start_game();
        stringstream ss1;
        board->print(ss1);
        REQUIRE(ss1.str() == "Player 1: ____, ____, ____, ____, ____, ____, ____, ____, ____, ____\n"
                             "Player 2: ____, ____, ____, ____, ____, ____, ____, ____, ____, ____\n"
                             "Player 3: ____, ____, ____, ____, ____, ____, ____, ____, ____, ____\n");
        SECTION("Board turn") {
            board->turn();
            stringstream ss1;
            board->print(ss1);
            REQUIRE(ss1.str() == "Player 1:  A D, ____, ____,  4 D,  5 D, ____, ____, ____, ____, ____\n"
                                 "Player 2: ____, ____, ____, ____, ____, ____, ____, ____, ____, ____\n"
                                 "Player 3:  J D,  2 C, ____,  4 S,  J C,  6 H, ____, ____, ____, ____\n");
        }
    }
    TEST_CASE("Player discard pile construction") {
        Board *board = new Board(1);
        Player *player1 = new Player("Player 1", board);
        Player *player2 = new Player("Player 2", board);
        Player *player3 = new Player("Player 3", board);
        Player *player4 = new Player("Player 4", board);
        vector<Player *> players;
        players.push_back(player1);
        players.push_back(player2);
        players.push_back(player3);
        players.push_back(player4);
        board->add_players(players, 1);
        board->start_game();
        size_t next = players.size() - 1;    //index of next player
        while (!player1->is_game_over() && !player2->is_game_over() && !player3->is_game_over()
                && !player4->is_game_over()) {
            next = (next + 1) % players.size();    //increment player / alternate (to avoid 0 for next)
            players[next]->turn();      //next points to last player
        }
        //require that all are face up for the winning player
        for (size_t rank = 1; rank <= 10; rank++) {
            REQUIRE(players[next]->is_face_up(rank) == true);
        }
        stringstream ss;
        players[next]->print(ss);
        REQUIRE(ss.str() == "Player 1:  A C,  2 D,  3 S,  4 S,  5 D,  6 C,  7 H,  8 S,  9 S, 10 H has won\n");
    }
    TEST_CASE("Select best rank") {
        Board *board = new Board(1);
        Player *player1 = new Player("Player 1", board);
        Player *player2 = new Player("Player 2", board);
        Player *player3 = new Player("Player 3", board);
        vector<Player *> players;
        players.push_back(player1);
        players.push_back(player2);
        players.push_back(player3);
        board->add_players(players, players.size() / 2);
        stringstream ss;
        board->print(ss);
        REQUIRE(ss.str() == "Player 1: \n"
                            "Player 2: \n"
                            "Player 3: \n");
        board->start_game();
        stringstream ss1;
        board->print(ss1);
        REQUIRE(ss1.str() == "Player 1: ____, ____, ____, ____, ____, ____, ____, ____, ____, ____\n"
                             "Player 2: ____, ____, ____, ____, ____, ____, ____, ____, ____, ____\n"
                             "Player 3: ____, ____, ____, ____, ____, ____, ____, ____, ____, ____\n");
        for (size_t i = 0; i < players.size(); i++) {
            std::cout<<players[i]->get_name()<<" before: ";
            players[i]->print(std::cout);
            players[i]->turn();
            std::cout<<players[i]->get_name()<<" AFTER: ";
            players[i]->print(std::cout);
        }
        stringstream ss2;
        players[2]->print(ss2);
        REQUIRE(ss2.str() == "Player 3:  J D,  2 C, ____,  4 S,  J C,  6 H, ____, ____, ____, ____\n");
    }
    TEST_CASE("Game print 2 players") {
        Game game(2, 1);
        stringstream ss;
        ss<<game.to_string();
        REQUIRE(ss.str() == "Player 1: ____, ____, ____, ____, ____, ____, ____, ____, ____, ____\n"
                            "Player 2: ____, ____, ____, ____, ____, ____, ____, ____, ____, ____\n");
    }
    TEST_CASE("Game play game 2 players") {
        Game game(2, 1);
        stringstream ss;
        game.play_game();
        ss<<game.to_string();
        REQUIRE(ss.str() == "Player 1:  A C,  2 C,  3 C, ____,  5 D,  6 S, ____,  8 C,  9 D, 10 H\n"
                            "Player 2:  J S,  2 H,  3 D,  4 C,  5 C,  J C,  7 H,  J D,  9 C, 10 S has won\n");    }
    TEST_CASE("Game print 6") {
        Game game(6, 1);
        stringstream ss;
        ss<<game.to_string();
        REQUIRE(ss.str() == "Player 1: ____, ____, ____, ____, ____, ____, ____, ____, ____, ____\n"
                            "Player 2: ____, ____, ____, ____, ____, ____, ____, ____, ____, ____\n"
                            "Player 3: ____, ____, ____, ____, ____, ____, ____, ____, ____, ____\n"
                            "Player 4: ____, ____, ____, ____, ____, ____, ____, ____, ____, ____\n"
                            "Player 5: ____, ____, ____, ____, ____, ____, ____, ____, ____, ____\n"
                            "Player 6: ____, ____, ____, ____, ____, ____, ____, ____, ____, ____\n");
    }
    TEST_CASE("Game play game 6 players") {
        Game game(6, 1);
        game.play_game();
        stringstream ss;
        ss<<game.to_string();
        REQUIRE(ss.str() == "Player 1:  A S,  2 D,  J C,  4 D, ____, ____,  7 S,  8 D, ____, ____\n"
                            "Player 2:  A D,  2 D,  3 C, ____, ____,  6 H,  J H,  8 H,  9 C, 10 C\n"
                            "Player 3:  A D,  2 H,  J D,  4 H, ____,  6 D,  7 D,  8 D,  9 S, 10 C\n"
                            "Player 4:  J C,  2 S,  3 S,  4 S, ____,  6 H,  7 C,  8 H, ____, 10 D\n"
                            "Player 5:  A C,  2 C,  3 S,  J H,  5 D,  6 C,  7 S,  8 H,  9 D, 10 H has won\n"
                            "Player 6: ____, ____,  3 H,  4 S,  5 H, ____,  7 H, ____,  9 H, 10 S\n");
    }
    TEST_CASE("Game step") {
        Game game(2, 1);
        //game.play_game();
        bool is_done = game.step();
        REQUIRE(is_done == false);

        stringstream ss;
        ss<<game.to_string();
        REQUIRE(ss.str() == "Player 1: ____, ____, ____, ____, ____, ____, ____, ____, ____, ____ Card to be played:  6 S\n"
                            "Player 2: ____, ____, ____, ____, ____, ____, ____, ____, ____, ____\n");
        while (!game.step()) {  //loop until turn is done for player 1
        }
        stringstream ss1;
        ss1<<game.to_string();
        REQUIRE(ss1.str() == "Player 1: ____, ____, ____, ____, ____,  6 S, ____, ____,  9 D, 10 H Turn over. Could not play  K S\n"
                             "Player 2: ____, ____, ____, ____, ____, ____, ____, ____, ____, ____\n");
        while (!game.step()) {  //loop until turn is done for player 2
        }
        stringstream ss2;
        ss2<<game.to_string();
        REQUIRE(ss2.str() == "Player 1: ____, ____, ____, ____, ____,  6 S, ____, ____,  9 D, 10 H Turn over.\n"
                             "Player 2: ____, ____, ____, ____,  5 C, ____,  7 H, ____, ____, ____ Turn over. Could not play  Q H\n");
    }
    TEST_CASE("Step game over") {
        Game game(2, 1);
        while (!game.is_over()) {
            game.step();
        }
        stringstream ss;
        ss<<game.to_string();
        REQUIRE(ss.str() == "Player 1:  A C,  2 C,  3 C, ____,  5 D,  6 S, ____,  8 C,  9 D, 10 H Turn over. Could not play  9 S\n"
                            "Player 2:  J S,  2 H,  3 D,  4 C,  5 C,  J C,  7 H,  J D,  9 C, 10 S has won\n");
        stringstream ss1;
        ss1<<game.game_summary();
        REQUIRE(ss1.str() == "Player 2 has won!");
    }
    TEST_CASE("Board step") {
        Board *board = new Board(1);
        Player *player1 = new Player("Player 1", board);
        Player *player2 = new Player("Player 2", board);
        vector<Player*> players;
        players.push_back(player1);
        players.push_back(player2);
        board->add_players(players, players.size() / 2);
        board->start_game();

        REQUIRE(board->step() == false);
        stringstream ss;
        board->print(ss);
        REQUIRE(ss.str() == "Player 1: ____, ____, ____, ____, ____, ____, ____, ____, ____, ____ Card to be played:  6 S\n"
                            "Player 2: ____, ____, ____, ____, ____, ____, ____, ____, ____, ____\n");
        while (!board->step()) { //while turn is still going for one player
        }
        stringstream ss1;
        board->print(ss1);
        REQUIRE(ss1.str() == "Player 1: ____, ____, ____, ____, ____,  6 S, ____, ____,  9 D, 10 H Turn over. Could not play  K S\n"
                             "Player 2: ____, ____, ____, ____, ____, ____, ____, ____, ____, ____\n");
        board->step();
        stringstream ss2;   ///player 2 does first turn
        board->print(ss2);
        REQUIRE(ss2.str() == "Player 1: ____, ____, ____, ____, ____,  6 S, ____, ____,  9 D, 10 H Turn over.\n"
                             "Player 2: ____, ____, ____, ____, ____, ____, ____, ____, ____, ____ Card to be played:  7 H\n");
        while (!board->step()) { //while turn is still going for one player
        }
        stringstream ss3;
        board->print(ss3);
        REQUIRE(ss3.str() == "Player 1: ____, ____, ____, ____, ____,  6 S, ____, ____,  9 D, 10 H Turn over.\n"
                             "Player 2: ____, ____, ____, ____,  5 C, ____,  7 H, ____, ____, ____ Turn over. Could not play  Q H\n");
        while (!board->is_over()) {
            board->step();
        }
        stringstream ss4;
        board->print(ss4);
        REQUIRE(ss4.str() == "Player 1:  A C,  2 C,  3 C, ____,  5 D,  6 S, ____,  8 C,  9 D, 10 H Turn over. Could not play  9 S\n"
                            "Player 2:  J S,  2 H,  3 D,  4 C,  5 C,  J C,  7 H,  J D,  9 C, 10 S has won\n");
        stringstream ss5;
        ss5<<board->game_summary();
        REQUIRE(ss5.str() == "Player 2 has won!");
    }
    TEST_CASE("Player step") {
        Board *board = new Board(1);
        Player *player1 = new Player("Player 1", board);
        Player *player2 = new Player("Player 2", board);
        vector<Player *> players;
        players.push_back(player1);
        players.push_back(player2);
        board->add_players(players, players.size() / 2);
        board->start_game();
        REQUIRE(player1->step() == false);
        stringstream ss;
        player1->print(ss);
        REQUIRE(ss.str() == "Player 1: ____, ____, ____, ____, ____,  6 S, ____, ____, ____, ____ Card to be played:  9 D\n");
        while (!player1->step()) {
        }
        stringstream ss1;
        player1->print(ss1);
        REQUIRE(ss1.str() == "Player 1: ____, ____, ____, ____, ____,  6 S, ____, ____,  9 D, 10 H Turn over. Could not play  K S\n");
    }
}