#include <iostream>
#include <string>
#include "itemVector.h"

// D stands for Dynamic
ItemVector::ItemVector(): capacity(1), size(0), begin(nullptr){
    this->end = this->begin;
}
ItemVector::ItemVector(size_t n, const Item& item): capacity(n), size(n), begin(nullptr), end(nullptr){
    begin = new Item*[n];
    end = &begin[size];
    for(int i = 0;i<n;i++){
        begin[i] = new Item(item); //copy constructor needed for item
    }
}
size_t ItemVector::getCap(){
    return this->capacity;
}
size_t ItemVector::getSize(){
    return this->size;
}
void ItemVector::push_back(const Item& item){
    if(size == capacity){
        Item** temp = begin;
        begin = new Item*[capacity*2];
        for(int i = 0;i<capacity;i++){
            begin[i] = temp[i]; 
        }
        capacity *= 2;
    }
    begin[size] = new Item(item);
    end = &begin[size];
}
Item& ItemVector::operator[](size_t index){
    return *begin[index];
}
const Item& ItemVector::operator[](size_t index) const {
    return *begin[index];
}
ItemVector::~ItemVector(){
    delete[] begin;
    delete end;
    begin = nullptr;
    end = nullptr;
}