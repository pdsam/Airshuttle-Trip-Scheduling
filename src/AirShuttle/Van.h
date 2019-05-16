#ifndef VAN_H_
#define VAN_H_

#include <vector>
#include "Service.h"

class Van {
private:
	static int capacity;

	std::vector<Service> services;

public:

	static int getCapacity();
	std::vector<Service> getServices() const;

	void addService(Service serv);
};

#endif
