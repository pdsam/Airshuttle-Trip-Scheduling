#ifndef TIME_H_
#define TIME_H_

class Time {
private:
	int hour, minute, second;
public:
	Time();
	Time(int hour, int minute, int second);

	int getHour() const;
	int getMinute() const;
	int getSecond() const;

	bool operator<(const Time& t2);
};

#endif
