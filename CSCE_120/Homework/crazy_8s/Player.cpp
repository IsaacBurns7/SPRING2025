#include<iostream>
#include<sstream>
#include "Player.h"
using std::vector, std::string, std::size_t, std::cout, std::cin;

Player::Player(bool isAI) : isAI(isAI), hand(){

}

void Player::addToHand(Card* c){
    hand.push_back(c);
}

size_t Player::getHandSize(){
    return hand.size();
}

std::string Player::getHandString(){
    string handString{""};
    for(auto* card: hand){
        string cardString {card->getRank() + " " + card->getSuit() + ", "};
        handString += cardString;
    }

    auto lastAlphaNum = handString.find_last_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789");

    if(lastAlphaNum == std::string::npos){
        return "";
    }

    return handString.substr(0, lastAlphaNum+1);
}

Card* Player::playCard(vector<string> const& suits, string& currentRank, string& currentSuit){
    // TODO: Choose a card to play and return the chosen card. Update currentRank and currentSuit.
    if(isAI){
        for(size_t i = 0;i<hand.size();i++){
            auto* Card = hand[i];
            if(Card->canBePlayed(currentRank, currentSuit)){
                currentRank = Card->getRank();
                currentSuit = Card->getSuit();
                hand.erase(hand.begin()+i);
                Card->play();
                return Card;
            }
        }
    }else{
        string rank;
        string suit;
        std::cout << "Your hand contains: " << this->getHandString() << '\n';
        std::cout << "The next card played must be a " << currentRank << " or " << currentSuit << '\n';
        std::cout << "What would you like to play? (enter \"draw card\" to draw a card)\n";

        while(true){
            std::cin >> rank >> suit;

            if(rank == "draw" && suit == "card"){
                return nullptr;
            }
            
            Card* card = nullptr;
            size_t i;

            for(i = 0;i<hand.size();i++){
                Card* card2 = hand[i];
                if(card2->getRank() == rank && card2->getSuit() == suit){
                    card = card2;
                    break;
                }
            }
            if(card == nullptr){
                cout << "That's not a card you have. Try again.\n";
                continue;
            }
            if(!card->canBePlayed(currentRank, currentSuit)){
                cout << "You can't play that card. Try again.\n";
                continue;
            }
            if(rank == "8"){
                cout << "What suit would you like to declare?\n";
                bool suitValid = false;
                while(!suitValid){
                    cin >> suit;
                    for(const auto& suit2: suits){
                        if(suit == suit2){
                            suitValid = true;
                        }
                    }
                    if(!suitValid){
                        cout << "That's not a suit in this deck. Try again.\n";
                    }
                }
            }
            currentRank = rank;
            currentSuit = suit;
            hand.erase(hand.begin()+i); //take card out of hand
            card->play();
            return card;
        }
    }
    return nullptr;
}