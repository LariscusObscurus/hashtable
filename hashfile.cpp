#include "hashfile.hpp"

HashFile::HashFile (const std::string& fileName, const std::string& mode)
{
}

HashFile::~HashFile (void)
{
}

bool HashFile::load (const std::string& fileName, hashtable& table)
{
	ulong read = 0;
	std::vector<hashtable::node>& hash = table.hsh_vector;
	FILE* file = fopen(fileName.c_str(), "r");
	// read variables
	char id[4];
	int intValue = 0;
	std::string str;
	float floatValue = 0;
	
	if (!file)
	{
		return false;
	}
}

bool HashFile::save (const std::string& fileName, const hashtable& table)
{
}