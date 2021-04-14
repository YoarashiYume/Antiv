#include "timeStruct.h"

void timeStruct::setTime(size_t _hour, size_t _min)
{
	hour = _hour < 24 ? _hour : 0;
	min = _min < 60 ? _min : 0;
}

bool operator<(timeStruct ts1, timeStruct ts2)
{
	if (ts1 == ts2)
		return false;
	if (ts1.hour < ts2.hour)
		return true;
	else if (ts1.min < ts2.min)
		return true;
	return false;
}

bool operator>(timeStruct ts1, timeStruct ts2)
{
	return ts2 < ts1;
}

bool operator==(timeStruct ts1, timeStruct ts2)
{
	return (ts1.hour == ts2.hour && ts1.min == ts2.min);
}
