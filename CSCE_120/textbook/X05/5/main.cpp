// [5] (∗1.5) Write a program that reads a name (a string) and an age (an int) from the standard
// input stream cin. Then output a message including the name and age to the standard output
// stream cout.
// [6] (∗1.5) Redo §X.5[5], storing several (name,age) pairs in a class. Doing the reading and writing using your own >> and << operators.


#include <iostream>
#include <string>
#include <vector>
using std::string, std::cin, std::cout, std::vector;

struct Employee{
    string name;
    int age;

    Employee(const string& n, int a): name(n), age(a) {}
};

template <typename T>
class EmployeeTable{
    public:
        vector<T> employees;
        EmployeeTable(std::initializer_list<T> employee_list): employees(employee_list){
            std::cout << "employees vector initialized with " << employee_list.size() << " employees\n";
        }
    private:
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const EmployeeTable<T>& table) {
    for (const auto& employee : table.employees) {
        os << "Name: " << employee.name << ", Age: " << employee.age << std::endl;
    }
    return os;
}

template <typename T>
std::istream& operator>>(std::istream& is, EmployeeTable<T>& table){
    string name;
    int age;
    cout << "Enter name and age of employee seperated by a whitespace. To terminate input, input an age of -1.\n";
    cout << "Employee Info: ";
    while(is >> name >> age && age != -1){
        T employee{name, age};
        table.employees.push_back(employee);
        cout << "Employee Info: ";
    }
    return is;
}

int main(){
    // string name;
    // int age;
    // cin >> name >> age;
    // cout << name << " is " << age << '\n';

    std::initializer_list<Employee> employee_list = {
        {"John Doe", 28},
        {"Will smith", 40},
        {"Bobby green", 52},
        {"Random guy called jack", 12}
    };

    EmployeeTable<Employee> employeeTable(employee_list);

    cin >> employeeTable;
    cout << employeeTable;
};