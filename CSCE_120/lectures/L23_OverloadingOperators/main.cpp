#include <string>
#include <iostream>

class Account{
    private:
        std::string name;
        double balance;
    public:
        Account(std::string name, double balance):
            name(name), balance(balance){}
        Account& deposit(double amount){
            balance += amount;
            return *this;
        }
        Account& withdraw(double amount){
            balance -= amount;
            return *this;
        }
        void printInfo(){
            std::cout << "Name: " << name << ", Balance: " << balance << std::endl;
        }
        //prefix increment(++x)
        Account& operator++(){
            this->balance++;
            return *this;
        }
        //postfix increment(x++)
        Account operator++(int num){
            Account result(this->name, this->balance);
            ++(*this);
            return result;
        }
};


int main(){
    Account a("a", 1.00);
    Account b = a++;
    Account c = ++a;
    a.printInfo();
    b.printInfo(); 
    c.printInfo();

}