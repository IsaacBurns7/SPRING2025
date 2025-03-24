/******************************************************************************

File: main.cpp
Author: Prof. Lupoli & Andrew Nemec
Date: 2/16/2021
Section: 
E-mail: slupoli@tamu.edu
Description:
This file contains C++  code that will simulate data collected from a track 
event with 9 lanes. The code will sort the order, then display the results

Updates
Author: J. Michael Moore & Paul Taele
Author: J. Michael Moore

Input information format
<Time (double)> <Abbreviated Country (String)> <Uniform number (int)> <Lastname (String)>
32.7 USA 12 Moore
36.5 RUS 35 Polsley
45.8 ENG 73 Teale
52.34 CHN 14 Nemec
76.45 ITY 23 Lupoli

*******************************************************************************/

#include <iostream>
#include <vector>
#include "rank_functions.h"

using std::cin; using std::cout; using std::endl; using std::vector;

int main()
{
    // TODO: create vector of type driver (see functions.h for struct details)

    // TODO: load the driver's data into the vectors ensuring all ranks are set to 0
    //         if unable to load return an empty vector
    std::vector<driver> drivers = load_driver_data();
	

    // if unable to load runner data
    //   1) output "Bad input" to standard out
    //   2) exit program by returning 1
    if(drivers.size() == 0){
        std::cout << "Bad input";
        return -1;
    }
    

    // TODO: determine ranking, notice the rank element in the struct is set
    drivers = set_rankings(drivers);

    // // TODO: Output results
    print_results(drivers);

    // this is not required in C++ but many people still explitly add it
    return 0; 
}

