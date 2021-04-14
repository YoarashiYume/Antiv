#pragma once
#include <stdint.h>
struct timeStruct
{
	int32_t hour;
	int32_t min;
	void setTime(size_t _hour,size_t _min);
	friend bool operator <(timeStruct ts1, timeStruct ts2);
	friend bool operator >(timeStruct ts1, timeStruct ts2);
	friend bool operator ==(timeStruct ts1, timeStruct ts2);
}; 


