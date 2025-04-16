# ifndef _STOCK_H
# define _STOCK_H

#include <string>
#include "item.h"
#include "itemVector.h"

class Stock
{
    private:
        ItemVector produce;
        ItemVector meat;
        ItemVector drinks; 
        
    public:
        Stock();
        double getInventoryValue(); //print combined value of all item vector members
        void printInventory(); //print all item vector members
        void addItem(string sectionName, const Item& item); //add item to specific section
        //throw std::invalid_argument if section not found
        void deleteItem(string sectionName, string identifier); //delete item from section, find item by matching name with identifier
        //throw std::invalid_argument if section not found
        void readSection(string sectionName);  //print contents of section's ItemVector
        //throw std::invalid_argument if section not found
        ItemVector& parseSectionName(string sectionName); //use sectionName string to create reference to itemvector
        //if section not found, throw std::invalid_argument
        ~Stock(); 
};
# endif