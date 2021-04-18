#include <catch2/catch.hpp>

#include <core/Card.h>

namespace naivebayes {
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
}
/*
 * bool get_face_up();
    friend ostream& operator<<(ostream& out, const Card& card);
    string get_rank() const;
    string get_suit() const;
    bool is_k_or_q();
    int get_rank_int();
    void set_face_up(bool is_face_up);
 */