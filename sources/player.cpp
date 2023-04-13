#include "player.hpp"
#include <vector>

namespace ariel {
//Player::Player() {}

// Player::Player(const Player& other)
//     : name(other.name)
//     , hand(other.hand)
//     , stack(other.stack)
// {}
// Player& Player::operator=(const Player& other) {
//     if (this != &other) {
//         name = other.name;
//         hand = other.hand;
//         stack = other.stack;
//     }
//     return *this;
//}
Player::Player(std::string name_){
    this->name = name_;
    this->hand = std::vector<Card>();
    this->stack = std::vector<Card>();
}
void Player::addCardToHand(Card& card) {
    hand.push_back(card);
}

Card Player::drawCard() {
    // if (hand.empty()) {
    //     throw std::out_of_range("Hand is empty");
    // }
    Card drawnCard = hand.back();
    hand.pop_back();
    return drawnCard;
}

void Player::addCardsToStack(std::vector<Card>& cards) {
    this->stack.insert(stack.end(), cards.begin(), cards.end());
    // std::cout << "Player 1: " << this->stacksize() << " cards" << std::endl;
}
void Player::addToStack(Card& card) {
    stack.push_back(card);
}

int Player::cardesTaken() const {
    return this->stack.size();
}

int Player::stacksize() const{
    return this->hand.size();
}

} // namespace WarGame
