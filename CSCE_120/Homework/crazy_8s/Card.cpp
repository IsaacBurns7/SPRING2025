#include<cctype>
#include<stdexcept>
#include "Card.h"
using std::string;

Card::Card(string rank, string suit) : rank(rank), suit(suit), timesPlayed(0) {
    if(rank.empty() || suit.empty()){
        throw std::invalid_argument("rank or suit is empty.");
    }
    for(const auto& ch: rank){
        if(!std::isalnum(ch)){
            throw std::invalid_argument("Illegal char detected in rank.");
        }
    }
    for(const auto& ch: suit){
        if(!std::isalnum(ch)){
            throw std::invalid_argument("Illegal char detected in suit.");
        }
    }
}

string Card::getRank(){
    return rank;
}

string Card::getSuit(){
    return suit;
}

int Card::getTimesPlayed(){
    return timesPlayed;
}

bool Card::canBePlayed(string currentRank, string currentSuit){
    // TODO: return whether or not this card can legally be played given that the previous card
    //  played had rank currentRank and suit currentSuit
    if(rank == currentRank || suit == currentSuit || rank == "8"){
        return true;
    }
    return false;
}

//You don't need to modify this
void Card::play(){
    timesPlayed++;
}