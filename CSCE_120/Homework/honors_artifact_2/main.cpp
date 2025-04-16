#include <iostream>
#include <string>
#include <exception>
#include "stock.h"
#include "item.h"

using std::cin, std::cout, std::cerr;

int main()
{
    //Ask the user what mode they would like to be in
    Stock s; 
    std::cout << "Would you like to read inventory, add inventory, delete inventory, or quit (r/a/d/q)" << '\n';
    char mode;
            
    //Place in loop to check user input 
    while(mode != 'q')
    {
        std::cin >> mode;
        std::cin.clear();
        std::cin.ignore();
        std::cout << '\n';

        switch(mode)
        {
            case('r'): {
                char action;
                cout << "Provide an action - readSection(s) or readInventory(i): ";
                cin >> action;
                
                if(action == 's'){
                    string sectionName;
                    cout << "Provide a section name: ";
                    cin >> sectionName;

                    try{
                        s.readSection(sectionName); 
                    }catch(std::exception e){
                        cerr << e.what() << '\n';
                    }

                }else if(action == 'i'){
                    char readCommand;
                    cout << "Provide a read command - Inventory(p) or InventoryValue(v).\n";
                    cin >> readCommand;
                    if(readCommand == 'p'){
                        s.printInventory();
                    }else if(readCommand == 'v'){
                        cout << "Inventory value: " << s.getInventoryValue() << '\n';
                    }else{
                        cout << "Valid read command not found.\n";
                    }
                }else{
                    cout << "Valid action could not be found.\n";
                }
                break; 
            }
            case('a'): {
                string sectionName;
                cout << "Provide a section name: ";
                cin >> sectionName;
                
                string price;
                string name;
                string quantity;
                Item item{};

                cout << "Provide the price of the new item: " << '\n';
                cin >> price;
                cout << "Provide the name of the new item: " << '\n';
                cin >> name;
                cout << "Provide the quantity of the new item: " << '\n';
                cin >> quantity;

                item.updatePrice(price);
                item.updateName(name);
                item.updateQuantity(quantity);

                try{
                    s.addItem(sectionName, item); //may be better to parse vector, and then ask for item first, for better user experience
                }catch(std::exception e){
                    cerr << e.what() << '\n';
                }
                break;
            }
            case('d'):
            {
                string sectionName;
                cout << "Provide a section name: ";
                cin >> sectionName;    

                string identifier;
                cout << "Provide the name of the item you wish deleted: ";
                cin >> identifier;

                try{
                    s.deleteItem(sectionName, identifier); //may be better to parse vector, and then ask for item first, for better user experience
                }catch(std::exception e){
                    cerr << e.what() << '\n';
                }
            }
                break;
            case('q'):
                std::cout << "Quitting\n";
                break;
            default:
                std::cout << "Please respond with either 'r'(read), 'a'(add), or 'd'(delete)" << '\n'; 
        }

        std::cout << '\n';

    }
    
    return 0; 
}