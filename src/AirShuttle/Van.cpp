#include "Van.h"

using namespace std;

int Van::capacity = 10;

int Van::getCapacity() {
	return capacity;
}

vector<Service> Van::getServices() const {
	return services;
}

void Van::addService(Service service) {
	this->services.push_back(service);
}

void Van::clearServices() {
	this->services.clear();
}
