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
  
  double maxTotalDonation = 0;
  int maxTotalCollector = 0;
  
  // read data
  while(!ifs.eof()){
    stringstream ssstream; 
    string str;
    getline(ifs, str);
    stringstream sstream(str);
    int collector;
    sstream >> collector;
    int numberOfDonations = 0;
    double donationTotal = 0;
    double donation;
    while(sstream >> donation){
      donationTotal += donation;
      numberOfDonations++;
    } 
    if(numberOfDonations > 1 && donationTotal > maxTotalDonation){
      maxTotalDonation = donationTotal;
      maxTotalCollector = collector;
    }
    
  }

  if(maxTotalCollector != 0){
    cout << "Highest donation total: " << maxTotalDonation << endl;
    cout << "-- collected by id: " << maxTotalCollector << endl;
  }else{
    cout << "Highest donation total: No donations" << endl;
  }
}
