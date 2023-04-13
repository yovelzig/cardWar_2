#include "card.hpp"

namespace ariel {
    Card::Card(Rank rank, Suit suit) : rank(rank), suit(suit) {}

    Card::Rank Card::getRank() const {
        return rank;
    }

    Card::Suit Card::getSuit() const {
        return suit;
    }

    int Card::compare(Card& other) {
        int rankDiff = rank - other.rank;
        if (rankDiff != 0) {
            if (rankDiff == 12)
            {
                rankDiff = -1;
            }
            else if (rankDiff == -12)
            {
                rankDiff = 1;
            }
            
            return rankDiff;
        } 
        else {
            return 0;
        }
    }

    std::string Card::toString() const {
        std::string result;
        switch(rank) {
            case ACE:
                result += "Ace";
                break;
            case TWO:
                result += "Two";
                break;
            case THREE:
                result += "Three";
                break;
            case FOUR:
                result += "Four";
                break;
            case FIVE:
                result += "Five";
                break;
            case SIX:
                result += "Six";
                break;
            case SEVEN:
                result += "Seven";
                break;
            case EIGHT:
                result += "Eight";
                break;
            case NINE:
                result += "Nine";
                break;
            case TEN:
                result += "Ten";
                break;
            case JACK:
                result += "Jack";
                break;
            case QUEEN:
                result += "Queen";
                break;
            case KING:
                result += "King";
                break;
        }
        result += " of ";
        switch(suit) {
            case CLUBS:
                result += "Clubs";
                break;
            case DIAMONDS:
                result += "Diamonds";
                break;
            case HEARTS:
                result += "Hearts";
                break;
            case SPADES:
                result += "Spades";
                break;
        }
        return result;
    }
} // namespace ariel