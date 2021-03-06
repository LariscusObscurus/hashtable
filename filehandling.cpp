#include "filehandling.hpp"
#include "parser.hpp"

std::vector<share_t> file_handling::import(const std::string& fileName, const std::string& name, const std::string& cont)
{
	FILE* fp = fopen(fileName.c_str(), "r+");
	if (fp)
	{
		fseek(fp, 0, SEEK_END);
		long f_size = ftell(fp);
		fseek(fp, 0, SEEK_SET);
		char *buf = new char[f_size];
		fread(buf, sizeof(char), f_size, fp);
		std::string text(buf);
		fclose(fp);
		delete[] buf;
		parser prs_text;
		return prs_text.parse_csv(text, name, cont);
	}
	return std::vector<share_t>(0);
}

bool file_handling::load (const std::string& fileName, hashtable& table)
{
	std::vector<hashtable::node>& hash = table.hsh_vector;
	std::vector<size_t>& refTable = table.hsh_name;
	FILE* file = fopen(fileName.c_str(), "rb");
	// read variables
	int intValue = 0;
	long longValue = 0;
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
		char* name = 0;
		char* cont = 0;
		std::vector<share_t> shares(0);
		fread((void*)&shareCount, sizeof(int), 1, file);
		// share name
		fread((void*)&intValue, sizeof(int), 1, file);
		name = new char[intValue];
		fread((void*)name, 1, intValue, file);
		// cont name
		fread((void*)&intValue, sizeof(int), 1, file);
		cont = new char[intValue];
		fread((void*)cont, 1, intValue, file);
		// read share
		for (register int j = 0; j < shareCount; j++)
		{
			share_t share;
			// name
			share.name += name;
			// cont
			share.cont += cont;
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
			fread((void*)&longValue, sizeof(long), 1, file);
			share.volume = longValue;
			// adjClose
			fread((void*)&floatValue, sizeof(float), 1, file);
			share.adjClose = floatValue;
			// add to shares
			shares.push_back(share);
		}
		// get key
		unsigned key = hashString(shares[0].cont) % table.size;
		// set node
		hashtable::node node;
		node.value = shares;
		node.set = true;
		// add to hash table
		hash[key] = node;
		// set reference
		key = hashString(shares[0].name) % table.size;
		// add to ref hash table
		refTable[key] = (size_t)(hashString(shares[0].cont) % table.size);
		// delete memory
		delete[] name;
		delete[] cont;
	}
	return true;
}

bool file_handling::save (const std::string& fileName, const hashtable& table)
{
	unsigned size = table.size;
	std::vector<hashtable::node> hash = table.hsh_vector;
	FILE* file = fopen(fileName.c_str(), "wb");
	// write variables
	int intValue = 0;
	long longValue = 0;
	float floatValue = 0;
	// file settings
	int corpCount = 0;
	// save indices
	std::vector<unsigned> indices(0);
	
	if (!file)
	{
		return false;
	}
	
	for (unsigned i = 0; i < size; i++)
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
		std::string name = shares[0].name;
		std::string cont = shares[0].cont;
		int shareSize = (int)shares.size();
		// write share count
		fwrite((const void*)&shareSize, sizeof(int), 1, file);
		// write name
		intValue = (int)name.size();
		fwrite((const void*)&intValue, sizeof(int), 1, file);
		for (register int j = 0; j < intValue; j++)
		{
			fputc(name[j], file);
		}
		// write cont
		intValue = (int)cont.size();
		fwrite((const void*)&intValue, sizeof(int), 1, file);
		for (register int j = 0; j < intValue; j++)
		{
			fputc(cont[j], file);
		}
		// write share
		for (register int j = 0; j < shareSize; j++)
		{
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
			longValue = shares[j].volume;
			fwrite((const void*)&longValue, sizeof(long), 1, file);
			// write adjClose
			floatValue = shares[j].adjClose;
			fwrite((const void*)&floatValue, sizeof(float), 1, file);
		}
	}
	return true;
}