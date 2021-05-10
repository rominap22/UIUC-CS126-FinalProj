#ifndef NAIVE_BAYES_CARD_H
#define NAIVE_BAYES_CARD_H
#include <string>
#include <vector>
#include <iostream>
using std::vector;
using std::ostream;
using std::string;
namespace naivebayes {

class Card {
 public:
  std::string GetBestClass() const;
  enum SUITS {
      CLUBS,
      DIAMONDS,
      HEARTS,
      SPADES
  };
    Card(size_t rank, SUITS suits);
    Card();
    bool get_face_up();
    friend ostream& operator<<(ostream& out, const Card& card);
    string get_rank() const;
    string get_suit() const;
    bool is_k_or_q();
    int get_rank_int();
    void set_face_up(bool is_face_up);
    void print(ostream& out);   //shows card, either face up or face down
private:
    size_t rank;
    SUITS suits;
    bool is_face_up;
};
}  // namespace naivebayes
#endif //NAIVE_BAYES_CARD_H
