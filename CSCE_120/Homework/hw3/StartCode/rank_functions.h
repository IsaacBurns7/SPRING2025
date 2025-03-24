#ifndef RANKFUNCTIONS_H
#define RANKFUNCTIONS_H

#include <vector>

const unsigned int SIZE = 9;

struct driver {
	std::string lastname = "";
	std::string country = "";
	unsigned int number = 0;
	double time = -10.0;
	unsigned int rank = 1;
};

//-------------------------------------------------------
// Name: load_driver_data
// PostCondition: returned vector contains data gotten from standard in and rank initialized to 0
//---------------------------------------------------------
std::vector<driver> load_driver_data();


std::string trim(std::string);
//-------------------------------------------------------
// Name: load_driver_data
// PostCondition: returned string has no whitespace at the beginning or end, but keeps any whitespace in the middle
//---------------------------------------------------------

//-------------------------------------------------------
// Name: set_rankings
// PostCondition: returned vector has the rank set for each driver based on the time
//---------------------------------------------------------
std::vector<driver> set_rankings(std::vector<driver>);

//-------------------------------------------------------
// Name: print_results
// PostCondition: after a very inefficient nested loop to determine the ranks
// it then displays them along with a delta in time from the start
//---------------------------------------------------------
void print_results(std::vector<driver>);

#endif