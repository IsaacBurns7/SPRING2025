# ifndef _DARR_H
# define _DARR_H

#include <iostream>
#include <string>
#include "stock.h"
#include "item.h"
#include <vector>

class ItemVector
{
    private:
    //double pointer, b/c each element is a pointer to an item
    //REASON: easier for OS to allocate contiguous block of 8-byte or 4-byte pointers than contiguous block of 32-byte or KB-size items.
        Item** begin; 
        Item** end;
        size_t capacity;
        size_t size;


    public:
        ItemVector();
        ItemVector(size_t n, const Item& item = Item()); 
        size_t getCap(); //return capacity
        size_t getSize(); //return size
        double getSum(); //return sum of all items in vector, taking into account listed quantity and price
        //bonus: account for potential duplicate items(by name)
        void printContents(); //print all items
        void removeItem(int index); //find index and remove the item, making sure to delete item, and shift rest of vector leftward 
        void push_back(const Item& item); //place item at end of vector, making sure to account for overflow(capacity == size)
        Item*& operator[](size_t index); //allow for modification of vector's pointers
        Item* operator[](size_t index) const; //const -> return pointer to item, cant modify
        ~ItemVector(); 
};

# endif 