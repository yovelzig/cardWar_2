#pragma once
#include <string>
#include <vector>
#include "card.hpp"

namespace ariel {
class Player {
public:
   // Player();
    //Player(const Player& other);
    //Player& operator=(const Player& other);
    Player(std::string name_);
    void addCardToHand(Card& card);
    Card drawCard();
    void addCardsToStack(std::vector<Card>& cards);
    int cardesTaken() const;
    int stacksize() const;
    void addToStack(Card& card) ;
    std::string getName(){return this->name;};
    // bool operator==(const Player& other) const {
    //     return name == other.name && stacksize() == other.stacksize();
    // }

private:
    std::string name;
    std::vector<Card> hand;
    std::vector<Card> stack;
};

} 
