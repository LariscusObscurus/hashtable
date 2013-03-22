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
	
	virtual long read (std::vector<ubyte>& buffer);
	virtual long write (const std::vector<ubyte>& buffer);
	virtual long seek (long offset, int origin);
	virtual long size (void);
	virtual inline bool isOpen (void) { return !mFile; }
private:
};

#endif