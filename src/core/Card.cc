#include <core/Card.h>
#include <sstream>
#include <iomanip>
using std::stringstream;
namespace naivebayes {


    Card::Card(size_t rank, SUITS suits):rank{rank}, suits{suits}, is_face_up{false} {

    }
    bool Card::get_face_up() {
        return is_face_up;
    }
    string Card::get_rank() const {
        if (rank == 1) {    //ace
            return "A";
        }
        if (rank == 13) {   //king
            return "K";
        }
        if (rank == 12) {   //queen
            return "Q";
        }
        if (rank == 11) {   //jack
            return "J";
        }
        //rest of the ranks (2 to 10)
        stringstream ss;
        ss<<rank;
        return ss.str();
    }
    string Card::get_suit() const {
        switch (suits) {
            case CLUBS:
                return "Clubs";
            case DIAMONDS:
                return "Diamonds";
            case HEARTS:
                return "Hearts";
            case SPADES:
                return "Spades";
        }
        return "";
    }
    ostream& operator<<(ostream& out, const Card& card) {
        if (card.is_face_up) {
            out<<std::setw(2)<<card.get_rank()<<" "<<card.get_suit()[0];   //e.g. "K C" if King of Clubs
        } else {
            out<<"____";
        }
        return out;
    }
    bool Card::is_k_or_q() {
        return rank >= 12;
    }
    int Card::get_rank_int() {
        return rank;
    }
    void Card::set_face_up(bool is_face_up) {
        this->is_face_up = is_face_up;
    }
    void Card::print(ostream& out) {
        out<<std::setw(2)<<get_rank()<<" "<<get_suit()[0];   //e.g. "K C" if King of Clubs
    }
}  // namespace naivebayes