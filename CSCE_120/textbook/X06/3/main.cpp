#include <chrono>
#include <iostream>

int time_loop(long long n){
    auto t0 = std::chrono::high_resolution_clock::now();
    std::atomic<int> sum = 0;

    for(long long i = 0;i<n;i++){
        sum++;
        std::cout << sum << '\n';
    }

    auto t1 = std::chrono::high_resolution_clock::now();

    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(t1-t0).count() << " milliseconds passed\n";
    return sum;
}
int main(){
    std::cout << "STARTING LOOP of 1e3" << '\n';
    time_loop(1e3);
    std::cout << "STARTING LOOP of 1e6" << '\n';
    time_loop(1e6);
    // std::cout << "STARTING LOOP of 1e9" << '\n';
    // time_loop(1e9);
}