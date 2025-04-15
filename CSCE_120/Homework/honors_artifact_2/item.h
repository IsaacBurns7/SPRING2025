# ifndef _ITEM_H
# define _ITEM_H

#include<string>
using std::string;

class Item
{
    private:
        double price; 
        string name; 
        int quantity;

    public:
        Item();
        Item(const Item& other); //copy assignment - copies over each member
        //below are setters and getters - trivial
        void updatePrice(string price);
        void updateName(string name);
        void updateQuantity (string quantity);
        double getPrice(); 
        string getName();
};
# endif