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
    static const SUITS SuitList[4];
    Card(size_t rank, SUITS suits);
    friend ostream& operator<<(ostream& out, const Card& card);
    string get_rank() const;
    string get_suit() const;
    bool is_k_or_q();
    int get_rank_int();
private:
    size_t rank;
    SUITS suits;
};
    static const Card::SUITS SuitList[4] =
            {
                    Card::CLUBS,
                    Card::DIAMONDS,
                    Card::HEARTS,
                    Card::SPADES
            };
}  // namespace naivebayes
#endif //NAIVE_BAYES_CARD_H
