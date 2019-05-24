#ifndef VAN_H_
#define VAN_H_

#include <vector>
#include "Service.h"

#include "../Utils/Time.h"

class Van {
private:
	static int capacity;
	Time nextTimeAvailable;
	std::vector<Service> services;

public:

	static int getCapacity();
	std::vector<Service> getServices() const;

	Time getNextTimeAvailable() const;
	void setNextTimeAvailable(Time time);

	void addService(Service serv);
	void clearServices();
};

#endif
