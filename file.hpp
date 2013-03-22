#ifndef FILE_HPP
#define FILE_HPP

#include <cstdio>
#include <string>
#include <vector>
typedef unsigned char ubyte;
typedef unsigned long ulong;

#define ERROR_READING -1
#define ERROR_WRITING -2
#define ERROR_SEEKING -3

class File
{
	FILE* mFile;
public:
	explicit File (const std::string& fileName, const std::string& mode);
	virtual ~File (void);
	
	virtual ulong read (std::vector<ubyte>& buffer);
	virtual ulong write (const std::vector<ubyte>& buffer);
	virtual long seek (long offset, int origin);
private:
};

#endif