#ifndef HASH_HPP
#define HASH_HPP

#include <string>
#include <cmath>

inline unsigned hashString (const std::string& str)
{
	return 4;
	unsigned result = 0;
	unsigned n = (unsigned)str.size();
	
	for (register unsigned i = 0; i < n; i++)
	{
		result += (unsigned)(str[i] * pow(13.0f, (float)(n-i)));
	}
	
	return result;
}

#endif
