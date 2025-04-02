#include "list.h"

list::list(): arr(new int(0)), size(1), capacity(1), 
{
}

void list::push_back(int num){
    if(size == capacity){
        capacity *= 2;
    }   
    arr[size] = num;
    size++;
}

