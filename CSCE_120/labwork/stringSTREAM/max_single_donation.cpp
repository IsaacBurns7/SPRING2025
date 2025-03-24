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
  
  double maxDonation = 0;
  int maxCollector = 0;
  
  // read data
  while(!ifs.eof()){
    stringstream ssstream; 
    string str;
    getline(ifs, str);
    stringstream sstream(str);
    int collector;
    sstream >> collector;
    double donation;
    while(sstream >> donation){
        if(donation > maxDonation){
            maxDonation = donation;
            maxCollector = collector;
        }
    }
    
  }

  if(maxCollector != 0){
    cout << "Highest single donation: " << maxDonation << endl;
    cout << "-- collected by id: " << maxCollector << endl;
  }else{
    cout << "Highest single donation: No donations" << endl;
  }
}
