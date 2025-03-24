#include <iostream>
#include <string>
#include <list>
#include <vector>

using std::cout, std::vector, std::list, std::string, std::cin;

template <typename T, typename... Tail>
class Less_than{
    const T val;
    public:
        Less_than(const T& v): val(v) { }
        bool operator()(const T& x) const { return x < val; }
        Tail... func(Tail... v) { return v; }
};

template <typename Container, typename Predicate> //C = Container, P = predicate

int count(const Container& c, Predicate pred){
    int cnt = 0;
    for(const auto& x: c){
        if(pred(x)){
            ++cnt;
        }
    }
    return cnt;
}

void f(const vector<int>& vector, const list<string>& list, int x, const string& s){
    cout << "number of values less than " << x
    << ": " << count(vector, Less_than<int>{x})
    << '\n';

    cout << "number of values less than " << s 
    << ": " << count(list, Less_than<string>{s})
    << '\n';
}

int main(){
    vector<int> vec = {1,2,3,4,5,6,7,8,9,10};
    list<string> list = {"a", "b", "c", "d", "e"};
    int x = 4;
    string str = "b";
    f(vec, list, x, str);
}