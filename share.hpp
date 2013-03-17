#ifndef SHARE_HPP
#define SHARE_HPP
#include <string>

typedef struct Share
{
	typedef struct Date
	{
		int day;
		int month;
		int year;
	} Date_t;
	
	std::string name;
	std::string cont;
	Date_t date;
	float open;
	float high;
	float low;
	float close;
	float volume;
	float adjClose;
} share_t;

#endif // SHARE_HPP
