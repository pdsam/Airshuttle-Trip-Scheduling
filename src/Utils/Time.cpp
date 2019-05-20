#include "Time.h"

Time::Time() {
	this->hour = 0;
	this->minute = 0;
	this->second = 0;
}

Time::Time(int hour, int minute, int second) {
	this->hour = hour;
	this->minute = minute;
	this->second = second;
}

int Time::getHour() const {
	return hour;
}

int Time::getMinute() const {
	return minute;
}

int Time::getSecond() const {
	return second;
}

bool Time::operator<(const Time &t2) const {
    if (hour == t2.hour) {
    	if (minute == t2.minute) {
    		if (second == t2.second) {
    			return false;
    		} else {
    			return second < t2.second;
    		}
    	} else {
    		return minute < t2.minute;
    	}
    } else {
    	return hour < t2.hour;
    }
}
