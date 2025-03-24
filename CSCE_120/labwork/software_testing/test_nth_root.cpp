#include <iostream>
#include <cmath>
#include "./nth_root.h"
#include "test_helpers.h"
//#include <string>

int main() {
    //bool pass = true;
    // std::string str = "pineapple";
    // EXPECT_THROW(str.at(10), std::out_of_range);
    {   // MINIMUM REQUIREMENT (for this lab)
        // just call the function with various values of n and x
        try{
        //nth root of x
            nth_root(2, 1);
            nth_root(0,1);
            nth_root(2,-1);
            nth_root(-1,0);
            nth_root(1,10);
            nth_root(-1,10);
            nth_root(-10,11);
            nth_root(-4,11);
            nth_root(2,11);
            nth_root(6,111);
            nth_root(1,0);
            nth_root(10,1);
            nth_root(1,-3);
            nth_root(10,123);
            nth_root(10,12.123);
            nth_root(11,1.213);
        } catch(...){

        }
    }

    {   // TRY HARD
        // report the value
        try{
            double actual = nth_root(2, 1);
            std::cout << "nth_root(2, 1) = " << actual << std::endl;
        }catch(std::domain_error const& e){
            std::cout << e.what() << std::endl;
        }
        try{
            double actual = nth_root(-1, 0);
            std::cout << "nth_root(-1, 0) = " << actual << std::endl;
        }catch(std::domain_error const& e){
            std::cout << e.what() << std::endl;
        }
        try{
            double actual = nth_root(1, 10);
            std::cout << "nth_root(1, 10) = " << actual << std::endl;
        }catch(std::domain_error const& e){
            std::cout << e.what() << std::endl;
        }
        try{
            double actual = nth_root(2, -1);
            std::cout << "nth_root(2, -1) = " << actual << std::endl;
        }catch(std::domain_error const& e){
            std::cout << e.what() << std::endl;
        }
        try{
            double actual = nth_root(-1, 10);
            std::cout << "nth_root(-1, 10) = " << actual << std::endl;
        }catch(std::domain_error const& e){
            std::cout << e.what() << std::endl;
        }
    }

    {   // TRY HARDER
        // compare the actual value to the expected value
        double actual = nth_root(2, 1);
        double expected = 1;
        if (std::fabs(actual - expected) > 0.00005) {
            std::cout << "[FAIL] (n=2, x=1)" << std::endl;
            std::cout << "  expected nth_root(2, 1) to be " << expected << std::endl;
            std::cout << "  got " << actual << std::endl;
        } else {
            std::cout << "[PASS] (n=2, x=1)" << std::endl;
        }
    }
}
