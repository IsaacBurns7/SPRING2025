#include <iostream>
#include <sstream>
#include <fstream>
using std::cin, std::cout, std::endl, std::string, std::getline,
      std::ifstream, std::istringstream, std::stringstream;

int main() {
  string filename;
  cout << "Enter donation filename: ";
  cin >> filename;
  ifstream ifs(filename);
  if (!ifs.is_open()) {
    cout << "Failed to open file " << filename << "." << endl;
    return 1;
  }
  
  double maxUniqueDonations = 0;
  int maxUniqueCollector = 0;
  
  // read data
  while(!ifs.eof()){
    stringstream ssstream; 
    string str;
    getline(ifs, str);
    stringstream sstream(str);
    int collector;
    sstream >> collector;
    int numberOfDonations = 0;
    double donation;
    while(sstream >> donation){
      numberOfDonations++;
    } 
    if(numberOfDonations > maxUniqueDonations){
      maxUniqueDonations = numberOfDonations;
      maxUniqueCollector = collector;
    }
    
  }

  if(maxUniqueCollector != 0){
    cout << "Most unique donations: " << maxUniqueDonations << endl;
    cout << "-- collected by id: " << maxUniqueCollector << endl;
  }else{
    cout << "Most unique donations: No donations" << endl;
  }
}
