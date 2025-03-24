#include <vector>
#include <iostream>

using std::cout;

int main(){
    std::vector<int> nums{5, 9, -1, 200};
    std::vector<std::string> names{"Kant", "Plato", "Aristotle", "Kierkegard", "Hume"};

    for(const auto& num: nums){
        cout << num << " ";
    }
    cout << '\n';
    for(const auto& name: names){
        cout << name << " ";
    }

    std::sort(nums.begin(),nums.end());
    std::sort(names.begin(),names.end());
    cout << "\n\n";

    for(const auto& num: nums){
        cout << num << " ";
    }
    cout << '\n';
    for(const auto& name: names){
        cout << name << " ";
    }
}