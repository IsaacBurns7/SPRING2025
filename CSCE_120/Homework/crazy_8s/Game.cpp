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
    string str;
    if(!inFile){
        throw std::runtime_error("loadDeckFromFile: Cannot open file");
    }
    getline(inFile, str);
    std::istringstream suitsStream(str);
    getline(inFile, str);
    std::istringstream ranksStream(str); 

    std::string token;

    //suit and rank must be alnum
    while(suitsStream >> token){
        // for(const auto& ch : token){
        //     if(!std::isalnum(ch)){
        //         throw std::runtime_error("loadDeckFromFile: Non-Alphanumeric detected while reading in suits");
        //     }
        // }
        suits.push_back(token); 
    }
    if(!inFile){
        throw std::runtime_error("error while reading suits");
    }

    bool contains8 = false;
    while(ranksStream >> token){
        // for(const auto& ch : token){
        //     if(!std::isalnum(ch)){
        //         throw std::runtime_error("loadDeckFromFile: Non-Alphanumeric detected while reading in ranks");
        //     }
        // }
        if(token == "8"){
            contains8 = true;
        }
        ranks.push_back(token); 
    }

    if(!contains8){
        throw std::runtime_error("loadDeckFromFile: Deck does not contain a rank of 8");
    }
    while(!inFile.eof()){
        try{

            string rank;
            string suit;
            string extra;
            getline(inFile, str);
            std::stringstream cardStream (str);
            if(!(cardStream >> rank)){
                throw std::runtime_error("loadDeckFromFile: Failed to read in rank");
            }
            if(!(cardStream >> suit)){
                throw std::runtime_error("loadDeckFromFile: Failed to read in suit");
            }
            if(cardStream >> extra){
                throw std::runtime_error("loadDeckFromFile: Extra input in card");
            }


            bool suitValid = false; 
            bool rankValid = false;
            for(size_t i = 0; i<suits.size();i++){
                if(suits[i] == suit){
                    suitValid = true;
                }
            }
            for(size_t i = 0; i<ranks.size();i++){
                if(rank == ranks[i]){
                    rankValid = true;
                }
            }

            if(!(suitValid && rankValid)){
                throw std::runtime_error("loadDeckFromFile: Rank or Suit not Valid.");
            }
            Card* newCard = new Card{rank, suit};
            deck.push_back(newCard);
            drawPile.insert(drawPile.begin(),newCard);

        } catch (std::exception& error){
            throw std::runtime_error(error.what());
        }
    }
    //drawPile needs to be in reverse order(last card is drawn first)
    // for(size_t i = deck.size()-1;i!=0;i--){
    //     Card* card = deck[i];
    //     drawPile.push_back(card); //drawPile[0] = first to draw
    // }
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
        drawPile.pop_back();
        return;
    }
    int m = discardPile.size();
    if(m <= 1){
        throw std::runtime_error("drawCard: Nothing to draw.");
    }
    cout << "Draw pile, empty, flipping the discard pile.\n";
    Card* topCard = discardPile[m-1];
    for(size_t i = m-2;i<drawPile.size();i--){
        drawPile.push_back(discardPile[i]);
        if(i == 0){
            break;
        }
    }
    discardPile.clear();
    discardPile.push_back(topCard);

    p->addToHand(drawPile[drawPile.size()-1]); //drawPile is of size m-1
    drawPile.pop_back();
}

Card* Game::deal(int numCards){
    // TODO: Flip the top card of the draw pile to be the initial discard
    // then deal numCards many cards to each player
    size_t n = drawPile.size();
    Card* discard = drawPile[n-1];
    discardPile.push_back(discard);
    drawPile.pop_back();
    for(int i = 0;i<numCards;i++){
        for(auto* player: players){
           drawCard(player);
        }
    }
    return discard;
}

string Game::mostPlayedSuit(){
    // TODO: Return the suit which has been played the most times
    // if there is a tie, choose any of the tied suits
    int mx_played = 0;
    string mx_suit = "";
    size_t n = suits.size();
    std::vector<int> freq(n, 0);
    for(size_t i = 0;i < suits.size(); i++){
        int played = 0;
        for(size_t j = 0;j< deck.size(); j++){
            if(deck[j]->getSuit() == suits[i]){
                played += deck[j]->getTimesPlayed();
            }
        }
        if(played > mx_played){
            mx_suit = suits[i];
            mx_played = played;
        }
    }
    return mx_suit;
}

int Game::runGame(){
    // TODO: Run the game and return the number of the winning player
    int n = discardPile.size();
    string currSuit = discardPile[n-1]->getSuit();
    string currRank = discardPile[n-1]->getRank();

    while(true){

        for(size_t i = 0; i<players.size();i++){
            std::cout << "Player " << i << "'s turn!\n";
            Card* played = players[i]->playCard(suits, currRank, currSuit);

            if(played == nullptr){
                try{
                    //may throw std::runtime_error
                    std::cout << "Player " << i << " draws a card.\n";
                }catch(std::runtime_error e){
                    std::cout << "Player " << i << " cannot draw a card.\n";
                    return -1;
                }
                continue;
            }

            discardPile.push_back(played);
            std::cout << "Player " << i << " plays " << played->getRank() << " " << played->getSuit();
            if(currRank == "8"){
                std::cout << " and changes the suit to " << currSuit << ".\n";
            }else{
                std::cout << ".\n";
            }

            if(players[i]->getHandSize() == 0)
            {
                return i;
            }
            
        }
    }

    return 0;
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