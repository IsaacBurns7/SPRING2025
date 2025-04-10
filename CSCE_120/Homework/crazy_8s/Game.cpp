#include<iostream>
#include<string>
#include<sstream>
#include<fstream>
#include "Game.h"
using std::string, std::vector, std::cout, std::cin;

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
            rank = "";
            suit = "";
        }
    } catch (std::invalid_argument& error){
        throw std::runtime_error("loadDeckFromFile: Error reading in deck.");
    }
    //drawPile needs to be in reverse order(last card is drawn first)
    for(size_t i = deck.size()-1;i>=0;i--){
        Card* card = deck[i];
        drawPile.push_back(card); //drawPile[0] = first to draw
    }
}

void Game::addPlayer(bool isAI){
    Player* player = new Player(isAI);
    players.push_back(player);
}
void Game::drawCard(Player* p){
    // TODO: Move the top card of the draw pile to Player p's hand
    // If the draw pile is empty, flip the discard pile to create a new one
    int n = drawPile.size();
    if(n > 0){
        p->addToHand(drawPile[n-1]);
        drawPile.erase(drawPile.end());
        return;
    }
    cout << "Draw pile, empty, flipping the discard pile.";
    int m = discardPile.size();
    if(m == 1){
        throw std::runtime_error("drawCard: Nothing to draw.");
    }
    for(size_t i = m-1;i>=0;i++){
        drawPile.push_back(discardPile[i]);
    }
    discardPile.erase(discardPile.begin()+1, discardPile.end());
    p->addToHand(drawPile[m-2]); //drawPile is of size m-1
    drawPile.erase(drawPile.end());
}

Card* Game::deal(int numCards){
    // TODO: Flip the top card of the draw pile to be the initial discard
    // then deal numCards many cards to each player
    size_t n = drawPile.size();
    Card* discard = drawPile[n-1];
    discardPile.push_back(discard);
    for(int i = 0;i<numCards;i++){
        for(auto* player: players){
            this->drawCard(player);
        }
    }
    return discard;
}

string Game::mostPlayedSuit(){
    // TODO: Return the suit which has been played the most times
    // if there is a tie, choose any of the tied suits
    size_t n = suits.size();
    std::vector<int> freq(n, 0);
    for(auto* card: deck){

    }
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