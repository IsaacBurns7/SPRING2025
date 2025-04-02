#include<iostream>
#include<string>
#include<sstream>
#include<fstream>
#include "Game.h"
using std::string, std::vector;

Game::Game(): players({}), suits({}), ranks({}), 
    deck({}), drawPile({}), discardPile({}) {}

void Game::loadDeckFromFile(string filename){
    // TODO: initialize suits, ranks, deck, and drawPile from the given file
    std::ifstream inFile {filename};
    if(!inFile.is_open()){
        throw std::runtime_error("loadDeckFromFile: Cannot open file");
    }
    string suitsString;
    getline(inFile, suitsString);
    std::istringstream suitsStream(suitsString);
    string ranksString; 
    getline(inFile, ranksString);
    std::istringstream ranksStream(ranksString); 

    std::string token;

    //suit and rank must be alnum
    while(suitsStream >> token){
        for(const auto& ch : token){
            if(!std::isalnum(ch)){
                throw std::runtime_error("loadDeckFromFile: Non-Alphanumeric detected while reading in suits");
            }
        }
        this->suits.push_back(token); 
    }
    while(ranksStream >> token){
        for(const auto& ch : token){
            if(!std::isalnum(ch)){
                throw std::runtime_error("loadDeckFromFile: Non-Alphanumeric detected while reading in ranks");
            }
        }
        this->ranks.push_back(token); 
    }
    try {
        string token;
        string rank;
        string suit;
        while(getline(inFile, token)){
            std::istringstream cardStream(token); //this may be an issue
            cardStream >> rank; 
            cardStream >> suit;
            //IF NOT RANK OR SUIT NOT THERE!

            Card* card = new Card{rank, suit}; //can throw std::invalid_argument
            deck.push_back(card);
        }
    } catch (std::invalid_argument& error){
        throw std::runtime_error("loadDeckFromFile: Error reading in deck.");
    }
    //drawPile needs to be in reverse order(last card is drawn first)
    for(int i = deck.size()-1;i>=0;i--){
        Card* card = deck[i];
        drawPile.push_back(card);
    }
}

void Game::addPlayer(bool isAI){
    // TODO: add a new player to the game
}

void Game::drawCard(Player* p){
    // TODO: Move the top card of the draw pile to Player p's hand
    // If the draw pile is empty, flip the discard pile to create a new one
}

Card* Game::deal(int numCards){
    // TODO: Flip the top card of the draw pile to be the initial discard
    // then deal numCards many cards to each player
}

string Game::mostPlayedSuit(){
    // TODO: Return the suit which has been played the most times
    // if there is a tie, choose any of the tied suits
}

int Game::runGame(){
    // TODO: Run the game and return the number of the winning player
}

//Destructor--Deallocates all the dynamic memory we allocated
//You shouldn't touch this
Game::~Game(){
    for (unsigned int i = 0; i < deck.size(); i++){
        delete deck.at(i);
    }
    for (unsigned int i = 0; i < players.size(); i++) {
        delete players.at(i);
    }
}