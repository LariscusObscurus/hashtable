#ifndef HASH_HPP
#define HASH_HPP

#include <string>
#include <cmath>

class Hash
{
public:
	inline unsigned operator() (const std::string& str)
	{
		unsigned result = 0;
		unsigned n = (unsigned)str.size();
		
		for (register unsigned i = 0; i < n; i++)
		{
			result += (unsigned)(str[i] * pow(13.0f, (float)(n-i)));
		}
		
		return result;
	}
};

#endif
