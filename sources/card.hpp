#pragma once
#include <iostream>

namespace ariel {
class Card {
public:
    enum Suit { CLUBS, DIAMONDS, HEARTS, SPADES };
    enum Rank {TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, ACE };

    Card(Rank rank = ACE, Suit suit = SPADES);
    Rank getRank() const;
    Suit getSuit() const;
    int compare(Card& other) ;
    std::string toString() const;

private:
    Rank rank;
    Suit suit;
};
} // namespace WarGame
