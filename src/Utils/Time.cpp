#include "Time.h"

#include <fstream>
#include <iomanip>

using namespace std;

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

Time Time::operator+(const Time& t2) const {
	Time new_time = *this;

	new_time.second += t2.second;
	new_time.minute += t2.minute + (new_time.second / 60);
	new_time.hour += t2.hour + (new_time.minute / 60);
	new_time.second %= 60;
	new_time.minute %= 60;

	return new_time;
}

Time Time::addMinutes(int minutes) const {
	Time new_time = *this;
	new_time.minute += minutes;
	new_time.hour += (new_time.minute / 60);
	new_time.minute %= 60;

	return new_time;
}

Time Time::addSeconds(int seconds) const {
	Time new_time = *this;
	new_time.second += seconds;
	new_time.minute += (new_time.second / 60);
	new_time.hour += (new_time.minute / 60);
	new_time.second %= 60;
	new_time.minute %= 60;

	return new_time;
}

std::ostream& operator<<(std::ostream & ost, const Time & time) {
	ost << std::setfill('0') << std::setw(2) << time.hour;
	ost << ":";
	ost << std::setfill('0') << std::setw(2) << time.minute;
	ost << ":";
	ost << std::setfill('0') << std::setw(2) << time.second;
	return ost;
}
