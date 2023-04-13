#pragma once
#include <vector>
#include "card.hpp"
#include "player.hpp"
using namespace std;
namespace ariel {

class Game {
public:
    Game(Player& player1 , Player& player2);
    void playAll();
    void printWiner() const;
    void printLog() const;
    void printLastTurn() const;
    void addlastTurn() ;
    void printStats() const;
    void playTurn();

private:
    static const int NUM_CARDS = 52;

    Player& player1;
    Player& player2;
    std::vector<Card> deck;
    std::vector<Card> cardsOnTable;
    // std::vector<Card> lastPlayedCards;
    // std::vector<std::string> logMessages;
    string message;
    string last_turn;
    bool player1Turn;
    bool checkDraw;
    double turnCount;
    double draw_count;
    double player1_winCount;
    double player2_winCount;
    double hiddencards_count;
    bool gameOver;

    void shuffleDeck();
    //void dealCards();
    // void printCardsOnTable() const;
    //void log(const std::string& message);
};
}