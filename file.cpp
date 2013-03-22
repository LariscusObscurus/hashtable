#include "file.hpp"

File::File (const std::string& fileName, const std::string& mode)
{
	mFile = fopen(fileName.c_str(), mode.c_str());
}

File::~File (void)
{
	fclose(mFile);
}

long File::read (std::vector<ubyte>& buffer)
{
	if (!mFile)
	{
		return ERROR_READING;
	}
	void* buf = (void*)&buffer[0];
	return (long) fread(buf, 1, buffer.max_size(), mFile);
}

long File::write (const std::vector<ubyte>& buffer)
{
	if (!mFile)
	{
		return ERROR_WRITING;
	}
	const void* buf = (const void*)&buffer[0];
	return (long) fwrite(buf, 1, buffer..max_size(), mFile);
}

long seek File::seek (long offset, int origin)
{
	if (!mFile || fseek(mFile, offset, origin))
	{
		return ERROR_SEEKING;
	}
	return ftell(mFile);
}