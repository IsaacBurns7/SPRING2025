#include <iostream>
#include <string>
#include "stock.h"
#include <sstream>


using std::cout;

//Stock constructor
Stock::Stock(): produce(ItemVector()), meat(ItemVector()), drinks(ItemVector()) {}
double Stock::getInventoryValue(){
    return produce.getSum() + meat.getSum() + drinks.getSum();
}
void Stock::printInventory(){ 
    cout << "\n\n---PRODUCE SECTION---\n\n";
    produce.printContents();
    cout << "\n\n---MEAT SECTION---\n\n";
    meat.printContents();
    cout << "\n\n---DRINKS SECTION---\n\n";
    drinks.printContents();
}
void Stock::addItem(string sectionName, const Item& item) noexcept(false){
    ItemVector& section = parseSectionName(sectionName); 

    section.push_back(item);
}
void Stock::deleteItem(string sectionName, string identifier) noexcept(false){ 
    ItemVector& section = parseSectionName(sectionName); //may throw std::invalid_argument

    int index;
    for(index = 0;index < section.getSize();index++){
        Item* item= &section[index];
        if(item->getName() == identifier){
            break;
        }
    }
    if(index == section.getSize()){
        throw std::invalid_argument("Was not able to find item with name: " + identifier);
    }
    section.removeItem(index);
}

void Stock::readSection(string sectionName) noexcept(false){
    ItemVector& section = parseSectionName(sectionName); //may throw std::invalid_argument
    section.printContents();
}

ItemVector& Stock::parseSectionName(string sectionName){
    ItemVector* sectionPtr = nullptr;
    if(sectionName == "p"){
        sectionPtr = &produce;
    }else if(sectionName == "m"){
        sectionPtr = &meat;
    }else if(sectionName == "d"){
        sectionPtr = &drinks;
    }
    if(sectionPtr == nullptr){
        std::ostringstream oss;
        oss << "Failed to parse sectionName, could not find section with sectionName: " << sectionName << '\n';
        throw std::invalid_argument(oss.str());
        //would probably better to throw an error ? 
    }
    ItemVector& section = *sectionPtr;

    return section;
}

Stock::~Stock(){
    //delete the 3 vectors
}