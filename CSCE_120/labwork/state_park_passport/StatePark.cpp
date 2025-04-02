# include "Passport.h"

using std::string, std::vector;

// TODO: implement constructor using member initializer list

StatePark::StatePark(std::string parkName, double entranceFee, double trailMiles):
	parkName(parkName), entranceFee(entranceFee), trailMiles(trailMiles), camperLog(){

}

string StatePark::getParkName() {
	return parkName;
}

double StatePark::getEntranceFee() {
	// TODO: implement getter

	return entranceFee;
}

double StatePark::getTrailMiles() {
	// TODO: implement getter
	
	return trailMiles;
}

void StatePark::addCamper(Passport* camper) {
	INFO(camper)
	camperLog.push_back(camper);
	return ;
}

double StatePark::getRevenue() {
	double revenue = 0.0;
	for(const auto& camper: camperLog){
		if(camper->checkJuniorPassport()){
			revenue += entranceFee / 2.0; 
		}else{
			revenue += entranceFee;
		}
	}

	return revenue;
}
