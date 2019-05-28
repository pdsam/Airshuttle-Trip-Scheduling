#ifndef TIME_H_
#define TIME_H_

#include <fstream>

class Time {
private:
	int hour, minute, second;
public:
	Time();
	Time(int hour, int minute, int second);

	int getHour() const;
	int getMinute() const;
	int getSecond() const;

	bool operator<(const Time& t2) const;
	Time operator+(const Time& t2) const;
	Time operator-(const Time& t2) const;

	Time addMinutes(int minutes) const;
	Time addSeconds(int seconds) const;

	int toSeconds() const;

	friend std::ostream& operator<<(std::ostream & ostream, const Time & time);
};

#endif
