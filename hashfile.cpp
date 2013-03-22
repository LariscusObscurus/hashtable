#include "hashfile.hpp"
#include "hash.hpp"

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
	std::vector<size_t>& refTable = table.hsh_name;
	FILE* file = fopen(fileName.c_str(), "r");
	// read variables
	char id[4];
	int intValue = 0;
	float floatValue = 0;
	// file settings
	int corpCount = 0;
	int shareCount = 0;
	
	if (!file)
	{
		return false;
	}
	
	fread((void*)&id[0], 1, 4, file);
	
	if (strcmp(&id[0], "hash"))
	{
		return false;
	}
	
	fread((void*)&corpCount, sizeof(int), 1, file);
	
	for (register int i = 0; i < corpCount; i++)
	{
		std::vector<share_t> shares(0);
		fread((void*)&shareCount, sizeof(int), 1, file);
		
		for (register int j = 0; j < shareCount; j++)
		{
			share_t share;
			char* buffer = 0;
			// share name
			fread((void*)&intValue, sizeof(int), 1, file);
			buffer = new char[intValue];
			fread((void*)buffer, 1, intValue, file);
			share.name += buffer;
			delete buffer;
			// cont name
			fread((void*)&intValue, sizeof(int), 1, file);
			buffer = new char[intValue];
			fread((void*)buffer, 1, intValue, file);
			share.cont += buffer;
			delete buffer;
			// day
			fread((void*)&intValue, sizeof(int), 1, file);
			share.date.day = intValue;
			// month
			fread((void*)&intValue, sizeof(int), 1, file);
			share.date.month = intValue;
			// year
			fread((void*)&intValue, sizeof(int), 1, file);
			share.date.year = intValue;
			// open
			fread((void*)&floatValue, sizeof(float), 1, file);
			share.open = floatValue;
			// high
			fread((void*)&floatValue, sizeof(float), 1, file);
			share.high = floatValue;
			// low
			fread((void*)&floatValue, sizeof(float), 1, file);
			share.low = floatValue;
			// close
			fread((void*)&floatValue, sizeof(float), 1, file);
			share.close = floatValue;
			// volume
			fread((void*)&floatValue, sizeof(float), 1, file);
			share.volume = floatValue;
			// adjClose
			fread((void*)&floatValue, sizeof(float), 1, file);
			share.adjClose = floatValue;
			
			// add to shares
			shares.push_back(share);
		}
		// get key
		unsigned key = Hash(shares[0].cont) % hashtable.size;
		// set node
		hashtable::node node = {shares, true};
		// add to hash table
		hash[key] = node;
		// set reference
		key = Hash(shares[0].name) % hashtable.size;
		// add to ref hash table
		refTable[key] = (size_t)(Hash(shares[0].cont) % hashtable.size);
	}
	
}

bool HashFile::save (const std::string& fileName, const hashtable& table)
{
}