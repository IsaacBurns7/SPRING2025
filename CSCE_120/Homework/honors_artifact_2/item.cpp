#include <iostream>
#include <string>
#include "stock.h"
#include "item.h"

using std::cout, std::cin;

Item::Item(): price(0.00), name(""), quantity(0) {}

Item::Item(const Item& other){
    price = other.price;
    name = other.name;
    quantity = other.quantity;
}
void Item::updatePrice(std::string buff)
{
    for(const auto& ch: buff){
        if(!(ch.isnumeric() || ch == '.')){
            cout << "Failed to parse price, must be of type double-precision float\n";
            return;
        }
    }
    cout << "Setting new price as: " << price << '\n';
    price = stod(buff);
}

void Item::updateName(std::string buff)
{
    cin >> name;
    cout << "Setting new name as: " << name << '\n';
}

void Item::updateQuantity(std::string buff )
{
    for(const auto& ch: buff){
        if(!(ch.isnumeric())){
            cout << "Failed to parse quantity, must be of type double-precision float\n";
            return;
        }
    }
    cout << "Setting new quantity as: " << quantity << '\n';
    quantity = stod(buff);
}

std::string Item::getName()
{
    return name;
}

double Item::getPrice()
{
    return price;
}
