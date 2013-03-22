#ifndef HASHFILE_HPP
#define HASHFILE_HPP

#include "file.hpp"

class HashFile
{
	File mFile;
public:
	explicit HashFile (const std::string& fileName, const std::string& mode);
	virtual ~HashFile (void);
	
	virtual void load (const std::string& fileName, hashtable& table);
	virtual void save (const std::string& fileName, const hashtable& table);
private:
};

#endif