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
		
		Date (void);
		~Date (void);
	} Date_t;
	
	std::string name;
	std::string cont;
	float open;
	float high;
	float low;
	float close;
	long volume;
	float adjClose;
	Date_t date;
	
	Share (void);
	~Share (void);
} share_t;

#endif // SHARE_HPP
