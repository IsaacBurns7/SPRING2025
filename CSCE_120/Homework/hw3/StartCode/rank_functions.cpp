#include <iostream>
#include <iomanip>
#include <vector>
#include "rank_functions.h"

using std::cin, std::cout, std::endl, std::vector;

//-------------------------------------------------------
// Name: load_driver_data
// PostCondition: returned vector contains data gotten from standard in and rank initialized to 0
//---------------------------------------------------------

//32.7 USA 12 Moore
//36.5 RUS 35 Polsley
//45.8 ENG 73 Taele
//52.34 CHN 14 Nemec
//76.45 ITY 23 Lupoli
//33.4 TKY 82 Munson
//38.0 ARG 88 Reardon
//50.1 ICE 41 Darlington
//60.34 NIC 50 Da Silva

bool validate_time(std::string time){
	//no preceding + or - 
	try{
		double num = std::stod(time);
		if(num > 0.0){
			return true;
		}else{
			return false;
		}
	}catch(const std::invalid_argument& e){
		return false;
	}
}
bool validate_country(std::string country){
	if(country.size() != 3){
		return false;
	}
	for(const auto& ch: country){
		if(isalpha(ch) == false || isupper(ch) == false){
		}
	}
	return true;
}
bool validate_number(std::string number){
	try{
		int num = std::stoi(number);
		if(num <= 0.0 || num >= 100.0){
			return false;
		}else{
			return true;
		}
	}catch(const std::invalid_argument& e){
		return false;
	}
	return true;
}
bool validate_name(std::string name){
	name = trim(name);
	for(const auto& ch: name){
		if(!isalpha(ch) && !isspace(ch)){
			return false;
		}
	}
	if(name.size() < 2){
		return false;
	}
	return true;
}


std::vector<driver> load_driver_data() {
	std::vector<driver> drivers;
	std::string line;

	// while(std::getline(cin, line)){
	// 	line.append(" ");
	// 	std::vector<std::string> data;
	// 	driver driver_data;
	// 	while(line.size() > 0){
	// 		std::string data_point;
	// 		int i = 0;
	// 		while(!isspace(line.at(i))){
	// 			data_point.append(1, line.at(i));
	// 			i++;
	// 		}
	// 		line.erase(0, i+1);
	// 		data.push_back(data_point);
	// 	}
	// 	if(data.size() != 4){
	// 		return blank;	
	// 	}

	// 	if(validate_time(data[0])){
	// 		driver_data.time = std::stod(data[0]);
	// 	}else{
	// 		return blank;
	// 	}
	// 	if(validate_country(data[1])){
	// 		driver_data.country = data[1];
	// 	}else{
	// 		return blank;
	// 	}
	// 	if(validate_number(data[2])){
	// 		driver_data.number = std::stoi(data[2]);
	// 	}else{
	// 		return blank;
	// 	}
	// 	if(validate_name(data[3])){
	// 		driver_data.lastname = data[3];
	// 	}else{
	// 		return blank;

	// 	}
	// 	driver_data.rank = 0;
	// }
	int lanes = 9;
	for(int i = 0;i<lanes;i++){
		std::getline(cin, line);
		line.append(" ");
		std::vector<std::string> data;
		driver driver_data;
		while(line.size() > 0){
			std::string data_point;
			int i = 0;
			while(!isspace(line.at(i))){
				data_point.append(1, line.at(i));
				i++;
			}
			line.erase(0, i+1);
			data_point = trim(data_point);
			data.push_back(data_point);
		}
		while(data.size() > 4){
			data[3] = data[3] + " " + data[4];
			data.erase(data.begin()+4, data.begin()+5);
		}
		data[3] = trim(data[3]);
		if(data.size() != 4){
			drivers.clear();
			return drivers;
		}

		if(validate_time(data[0])){
			driver_data.time = std::stod(data[0]);
		}else{
			drivers.clear();
			//std::cout << "bad time!";
			return drivers;
		}
		if(validate_country(data[1])){
			driver_data.country = data[1];
		}else{
			drivers.clear();
			//std::cout << "bad country!";
			return drivers;
		}
		if(validate_number(data[2])){
			driver_data.number = std::stoi(data[2]);
		}else{
			drivers.clear();
			//std::cout << "bad number!";
			return drivers;
		}
		if(validate_name(data[3])){
			driver_data.lastname = data[3];
		}else{
			drivers.clear();
			//std::cout << "bad name!";
			return drivers;

		}
		driver_data.rank = 0;
		drivers.push_back(driver_data);
	}
	return drivers;
}

//-------------------------------------------------------
// Name: set_rankings
// PostCondition: after a very inefficient nested loop to determine the placements 
// and places sets the ranks. That updated vector is returned
//---------------------------------------------------------
std::vector<driver> set_rankings(std::vector<driver> v) {
	for(std::size_t i = 0;i<v.size();i++){
		int ith_time_pos = -1;
		double ith_time = 1e10;
		for(std::size_t j = 0;j<v.size();j++){
			if(v[j].time < ith_time && v[j].rank == 0){
				ith_time_pos = j;
				ith_time = v[j].time;
			}
		}
		v[ith_time_pos].rank = i+1;
	}
	return v;
}

std::string trim(std::string s){
	while(s.size() > 0 && isspace(s.at(0))){
		s.erase(0,1);
	}
	while(s.size() > 0 && isspace(s.at(s.size()-1))){
		s.erase(s.size()-1,s.size());
	}
	return s;
}

//-------------------------------------------------------
// Name: print_results
// PostCondition: after a very inefficient nested loop to determine the ranks
// it then displays then along with a delta in time from the start
//---------------------------------------------------------
void print_results(std::vector<driver> v)
{

	std::cout << "Final results!!";
	std::cout << std::setprecision(2) << std::showpoint << std::fixed << std::endl;
	double best_time = 0.0;
		
	// print the results, based on rank, but measure the time difference_type
	for(unsigned int j = 1; j <= v.size(); j++)
	{
		
		// go thru each array, find who places in "i" spot
		for(unsigned int i = 0; i < v.size(); i++)
		{
			if(v.at(i).rank == 1) // has to be a better way, but need the starting time
			{
				best_time = v.at(i).time;
			}
			
			
			if(v.at(i).rank == j) // then display this person's data
			{
				// this needs precision display
				std::cout << "[" << j << "]  " << v.at(i).time << " " << std::setw(15) << std::left << v.at(i).lastname << "\t" << "(" << v.at(i).country << ")  +" << (v.at(i).time - best_time) << std::endl; 
			}
			
		}
	}	
}