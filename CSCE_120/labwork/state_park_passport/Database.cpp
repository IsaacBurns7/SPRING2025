# include "Database.h"

using std::string, std::vector;

// TODO: implement constructor using member initializer list

Database::Database(): stateParkList(), camperList()
{

}

Database::~Database() {
	for (unsigned int i = 0; i < stateParkList.size(); ++i) {
		delete stateParkList.at(i);
	}
	
	for (unsigned int i = 0; i < camperList.size(); ++i) {
		delete camperList.at(i);
	}
}

void Database::addStatePark(string parkName, double entranceFee, double trailMiles) {
	INFO(parkName)
	INFO(entranceFee)
	INFO(trailMiles)

	StatePark* statepark = new StatePark(parkName, entranceFee, trailMiles);

	stateParkList.push_back(statepark);

	return;
}

void Database::addPassport(string camperName, bool isJuniorPassport) {
	INFO(camperName)
	INFO(isJuniorPassport)

	// TODO: implement function

	Passport* passport = new Passport(camperName, isJuniorPassport);

	camperList.push_back(passport);

	return;
}

void Database::addParkToPassport(string camperName, string parkName) {
	INFO(camperName)
	INFO(parkName)

	// TODO: implement function
	Passport* camper = nullptr;
	StatePark* park = nullptr;

	for(size_t i = 0;i<camperList.size();i++){
		if(camperList[i]->getCamperName() == camperName){
			camper = camperList[i];
			//break;
		}
	}
	for(size_t i = 0;i<stateParkList.size();i++){
		if(stateParkList[i]->getParkName() == parkName){
			park = stateParkList[i];
			//break;
		}
	}
	if (camper&&park) {
        camper->addParkVisited(park);
    }
	return;
}

vector<string> Database::getParksInRevenueRange(double lowerBound, double upperBound) {
	INFO(lowerBound)
	INFO(upperBound)

	// TODO: (optional) implement function
	
	return {};
}

vector<string> Database::getHikersAtLeastLevel(int level) {
	INFO(level)

	// TODO: (optional) implement function

	return {};
}
