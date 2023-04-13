#include "game.hpp"
#include <algorithm>
#include <iostream>
#include <random>
#include <string>

namespace ariel {

Game::Game(Player& ply1,Player& ply2) :
player1(ply1),
player2(ply2),
deck(), 
cardsOnTable(),
player1Turn(true),
turnCount(0),checkDraw(false),
gameOver(false) {
    // this->player1 = &ply1;
    // this->player2 = &ply2;
    this->deck.reserve(NUM_CARDS);
    for (int i = Card::TWO; i <= Card::ACE; ++i) {
        for (int j = Card::CLUBS; j <= Card::SPADES; ++j) {
            deck.emplace_back(static_cast<Card::Rank>(i), static_cast<Card::Suit>(j));
        }
    }
    shuffleDeck();
    int numCardsPerPlayer = NUM_CARDS / 2;
    for (size_t i = 0; i < numCardsPerPlayer; ++i) {
        player1.addCardToHand(deck[static_cast<std::vector<Card>::size_type>(i) ]);
    }
    for (size_t i = 26; i < NUM_CARDS; ++i) {
        player2.addCardToHand(deck[static_cast<std::vector<Card>::size_type>(i)]);
        
    }
}

void Game::shuffleDeck() {
    std::random_device randomDevice;
    std::mt19937 rng(randomDevice());
    std::shuffle(deck.begin(), deck.end(), rng);
}
void Game::playAll() {
    while (player1.stacksize()> 0) {
        playTurn();
    }
}

void Game::playTurn() {
    
    if (player1.stacksize()== 0)
    {
        throw "the game is over";
    }
    else if (&player1 == &player2)
    {
        throw "we need two different players to play the game";
    }
    
    last_turn = "";
    Card playedCard1 = this->player1.drawCard();
    Card playedCard2 = this->player2.drawCard();
    cardsOnTable.push_back(playedCard1);
    cardsOnTable.push_back(playedCard2);
    Card revealedCard1;
    Card revealedCard2;
    last_turn += player1.getName()+" played: " + playedCard1.toString()+" "+player2.getName()+" played: " + playedCard2.toString() +" . " ;
    if (playedCard1.compare(playedCard2) > 0 ) {
        player1.addCardsToStack(cardsOnTable);
        last_turn += player1.getName()+" win " ;
        cardsOnTable.clear();
        player1_winCount++;
    } 
    else if (playedCard2.compare(playedCard1) > 0 ) {
        player2.addCardsToStack(cardsOnTable);
        last_turn += player2.getName()+" win ";
        cardsOnTable.clear();
        player2_winCount++;
    } 
    else {
         revealedCard1 = playedCard1;
         revealedCard2 = playedCard2;
        while (!gameOver && player1.stacksize()> 1 && revealedCard2.compare(revealedCard1) == 0 && (player1.cardesTaken()+player2.cardesTaken())<52)
        {
          last_turn += " Draw. ";
          draw_count++;
        // Both players place one card face down and one card face up
        Card hiddenCard1 = player1.drawCard();
        Card hiddenCard2 = player2.drawCard();
        hiddencards_count++;
        last_turn += player1.getName()+" played face down: " + hiddenCard1.toString()+" "+player2.getName()+" played face down: " + hiddenCard2.toString() +" . " ;
        cardsOnTable.push_back(hiddenCard1);
        cardsOnTable.push_back(hiddenCard2);

        revealedCard1 = player1.drawCard();
        revealedCard2 = player2.drawCard();
        last_turn += player1.getName()+" played face up: " + revealedCard1.toString()+" "+player2.getName()+" played face up: " + revealedCard2.toString() +" . " ;
        cardsOnTable.push_back(revealedCard1);
        cardsOnTable.push_back(revealedCard2);

        if (revealedCard1.compare(revealedCard2) > 0) {
            player1.addCardsToStack(cardsOnTable);
            last_turn += " "+player1.getName()+" win .";
            player1_winCount++;
            // log("Player 1 won this turn.");
        } 
        else if (revealedCard2.compare(revealedCard1) > 0) {
            player2.addCardsToStack(cardsOnTable);
            last_turn += " "+player2.getName()+" win .";
            player2_winCount++;
            
        } 
      }
    }
    if (revealedCard2.compare(revealedCard1) == 0 && player1.stacksize()==1 && cardsOnTable.size()!= 0 && (player1.cardesTaken()+player2.cardesTaken())<52)
    { 
        int sizeofSplit = cardsOnTable.size();
    for (size_t i = 0; (int)i < sizeofSplit; i++) {
        if (revealedCard2.compare(revealedCard1) == 0)
        {        
        if ((int)i % 2 == 0) {
            player1.addToStack(cardsOnTable[i]);
        } 
        else {
            player2.addToStack(cardsOnTable[i]);
        }
    }
    }
    gameOver = true;
    cardsOnTable.clear();
    }
    if (!gameOver && player1.stacksize() == 0 && revealedCard2.compare(revealedCard1) == 0 && (player1.cardesTaken()+player2.cardesTaken())<52 && cardsOnTable.size()!=0) {
        last_turn += " Draw.";
        draw_count++;
    // Split the cards on the table evenly between the players
    int sizeofSplit = cardsOnTable.size();
    for (size_t i = 0; (int)i < sizeofSplit; i++) {
        if (revealedCard2.compare(revealedCard1) == 0)
        {        
        if ((int)i % 2 == 0) {
            player1.addToStack(cardsOnTable[i]);
        } 
        else {
            player2.addToStack(cardsOnTable[i]);
        }
    }
    gameOver = true;
    cardsOnTable.clear();
    }
}
message += last_turn;
message += "\n";
    player1Turn = !player1Turn;
    turnCount++;
    cardsOnTable.clear();
}

void Game::printWiner() const {
    std::cout << "The game is over!" << std::endl;
    std::cout << "Player " << (player1.cardesTaken() > player2.cardesTaken() ? "1" : "2") << " wins!" << std::endl;
}
void Game::printStats() const {
    double win_rate_p1 = (player1_winCount*100)/turnCount;
    double win_rate_p2 = (player2_winCount*100)/turnCount;
    double draw_rate = (draw_count*100)/(turnCount-hiddencards_count);
    std::cout << player1.getName()+" win " << player1_winCount << " times,";
    std::cout << " win rate: " << win_rate_p1 << " % " << ",and won : "<<player1.cardesTaken()<<" cards "<< std::endl;
    std::cout << player2.getName()+" win " << player2_winCount << " times,";
    std::cout << " win rate: " << win_rate_p2 << " % " << ",and won : "<<player2.cardesTaken()<<" cards "<< std::endl;
    std::cout << "draw occur: " << draw_count << " times" << std::endl;
    std::cout << "draw rate: " << draw_rate << " %" << std::endl;
    std::cout << "in the game was : " << turnCount << " turns" << std::endl;
}

void Game::printLog() const {
    std::cout << "Game log:" << std::endl;
    std::cout << message << std::endl;
}

void Game::printLastTurn() const {
     std::cout << "Last turn:" << std::endl;
     std::cout << last_turn << std::endl;
   }
 }