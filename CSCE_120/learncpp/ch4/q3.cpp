#include <iostream>

int main(){
    double height = 0;
    double fallen = 0;
    std::cout << "Enter the height of the tower in meters: ";
    std::cin >> height;
    int t = 0;
    while((height-fallen) > 0){
        std::cout << "At " << t << " seconds, the ball is at height: " << height-fallen << " meters\n";
        t++;
        fallen = (9.8 * (t*t))/2.0;
    }
    std::cout << "At " << t << " seconds, the ball is on the ground.\n"; 
}