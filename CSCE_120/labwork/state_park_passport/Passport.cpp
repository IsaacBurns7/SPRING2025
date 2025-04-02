# include "Passport.h"

using std::string, std::vector;

// TODO: implement constructor using member initializer list

Passport::Passport(std::string camperName, bool isJuniorPassport): 
camperName(camperName), isJuniorPassport(isJuniorPassport), parksVisited()
{
}

string Passport::getCamperName() {
	return camperName;

	return "";
}

bool Passport::checkJuniorPassport() {
	// TODO: implement getter
	return isJuniorPassport;

}

void Passport::addParkVisited(StatePark* park) {
	INFO(park)

	// TODO: implement function
	parksVisited.push_back(park);
	park->addCamper(this);

	return;
}

double Passport::getMilesHiked() {
	double milesHiked = 0.0;

	for(const auto& park : parksVisited){
		milesHiked += park->getTrailMiles();
	}

	return milesHiked;
}

int Passport::getHikerLevel() {
	// TODO: (optional) implement function

	return 0;
}
