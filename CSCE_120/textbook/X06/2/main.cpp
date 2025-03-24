#include <iostream>
#include <thread>
#include <chrono>

void hello(){
    while(true){
        std::cout << "hello\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}
void world(){
    while(true){
        std::cout << "world!\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}

int main(){
    std::thread t1(hello);
    std::thread t2(world);
    t1.join();
    t2.join();

}