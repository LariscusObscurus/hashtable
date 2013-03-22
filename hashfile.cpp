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
	std::vector<hashtable::node>& hash = table.hsh_vector;
	std::vector<size_t>& refTable = table.hsh_name;
	FILE* file = fopen(fileName.c_str(), "r");
	// read variables
	int intValue = 0;
	float floatValue = 0;
	// file settings
	int corpCount = 0;
	int shareCount = 0;
	
	if (!file)
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
		unsigned key = hashString(shares[0].cont) % table.size;
		// set node
		table::node node = {shares, true};
		// add to hash table
		hash[key] = node;
		// set reference
		key = hashString(shares[0].name) % table.size;
		// add to ref hash table
		refTable[key] = (size_t)(hashString(shares[0].cont) % table.size);
	}
	return true;
}

bool HashFile::save (const std::string& fileName, const hashtable& table)
{
	unsigned size = table.size;
	std::vector<hashtable::node> hash = table.hsh_vector;
	FILE* file = fopen(fileName.c_str(), "r");
	// write variables
	int intValue = 0;
	float floatValue = 0;
	// file settings
	int corpCount = 0;
	int shareCount = 0;
	// save indices
	std::vector<unsigned> indices(0);
	
	if (!file)
	{
		return false;
	}
	
	for (register unsigned i = 0; i < size; i++)
	{
		// check if hash is set
		if (hash[i].set)
		{
			corpCount++;
			indices.push_back(i);
		}
	}
	fwrite((const void*)&corpCount, sizeof(int), 1, file);
	
	for (register int i = 0; i < corpCount; i++)
	{
		std::vector<share_t> shares = hash[indices[i]].value;
		int shareSize = (int)shares.size();
		// write share count
		fwrite((const void*)&shareSize, sizeof(int), 1, file);
		// write shares
		for (register int j = 0; j < shareSize; j++)
		{
			// write name
			intValue = (int)shares[j].name.size();
			fwrite((const void*)&intValue, sizeof(int), 1, file);
			for (register int k = 0; k < intValue; k++)
			{
				fputc(shares[j].name[k], file);
			}
			// write cont
			intValue = shares[j].cont.size();
			fwrite((const void*)&intValue, sizeof(int), 1, file);
			for (register int k = 0; k < intValue; k++)
			{
				fputc(shares[j].cont[k], file);
			}
			// write day
			intValue = shares[j].date.day;
			fwrite((const void*)&intValue, sizeof(int), 1, file);
			// write month
			intValue = shares[j].date.month;
			fwrite((const void*)&intValue, sizeof(int), 1, file);
			// write year
			intValue = shares[j].date.year;
			fwrite((const void*)&intValue, sizeof(int), 1, file);
			// write open
			floatValue = shares[j].open;
			fwrite((const void*)&floatValue, sizeof(float), 1, file);
			// write high
			floatValue = shares[j].high;
			fwrite((const void*)&floatValue, sizeof(float), 1, file);
			// write low
			floatValue = shares[j].low;
			fwrite((const void*)&floatValue, sizeof(float), 1, file);
			// write close
			floatValue = shares[j].close;
			fwrite((const void*)&floatValue, sizeof(float), 1, file);
			// write volume
			floatValue = shares[j].volume;
			fwrite((const void*)&floatValue, sizeof(float), 1, file);
			// write adjClose
			floatValue = shares[j].adjClose;
			fwrite((const void*)&floatValue, sizeof(float), 1, file);
		}
	}
	return true;
}