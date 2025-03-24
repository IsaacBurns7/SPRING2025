#include <iostream>
#include <random>
#include <vector>

int main(){
    std::default_random_engine random_engine{};
    std::normal_distribution<double> one_to_thirty{15.0,15.0};
    auto dist = bind(one_to_thirty, random_engine);

    std::vector<int> histogram(30);

    for(int i = 0;i<1e3;i++){
        ++histogram[std::round(dist())];
    }

    for(int i = 0;i<histogram.size();i++){
        std::cout << i << '\t';
        for(int j = 0;j<histogram[i];j++){
            std::cout << "*";
        }
        std::cout << '\n';
    }
}