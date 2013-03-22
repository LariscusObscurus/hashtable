#include "hashfile.hpp"

HashFile::HashFile (const std::string& fileName, const std::string& mode)
{
}

HashFile::~HashFile (void)
{
}

bool HashFile::load (const std::string& fileName, hashtable& table)
{
	mFile = File(fileName, "r");
	
	if (!mFile.isOpen())
	{
		return false;
	}
}

bool HashFile::save (const std::string& fileName, const hashtable& table)
{
	mFile = File(fileName, "w");
	
	if (!mFile.isOpen())
	{
		return false;
	}
}