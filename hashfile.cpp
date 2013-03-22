#include "hashfile.hpp"

HashFile::HashFile (const std::string& fileName, const std::string& mode)
{
}

HashFile::~HashFile (void)
{
}

bool HashFile::load (const std::string& fileName, hashtable& table)
{
	long read = 0;
	std::vector<byte> buffer;
	File file(fileName, "r");
	
	if (!mFile.isOpen())
	{
		return false;
	}
	
	file.read(buffer, 4);
	
	while (true)
	{
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