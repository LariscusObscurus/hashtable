#include "file.hpp"

File::File (const std::string& fileName, const std::string& mode)
{
	mFile = fopen(fileName.c_str(), mode.c_str());
}

File::~File (void)
{
	fclose(mFile);
}

long File::read (std::vector<byte>& buffer)
{
	if (!mFile)
	{
		return ERROR_READING;
	}
	void* buf = (void*)&buffer[0];
	return (long) fread(buf, 1, buffer.max_size(), mFile);
}

long File::read (std::vector<byte>& buffer, ulong count)
{
	if (!mFile)
	{
		return ERROR_READING;
	}
	buffer = std::vector<byte>(count);
	void* buf = (void*)&buffer[0];
	return (long) fread(buf, 1, (size_t)count, mFile);
}

long File::write (const std::vector<byte>& buffer)
{
	if (!mFile)
	{
		return ERROR_WRITING;
	}
	const void* buf = (const void*)&buffer[0];
	return (long) fwrite(buf, 1, buffer.max_size(), mFile);
}

long write (const std::vector<byte>& buffer, ulong count)
{
	if (!mFile)
	{
		return ERROR_WRITING;
	}
	const void* buf = (const void*)&buffer[0];
	return (long) fwrite(buf, 1, count, mFile);
}

long File::seek (long offset, int origin)
{
	if (!mFile || fseek(mFile, offset, origin))
	{
		return ERROR_SEEKING;
	}
	return ftell(mFile);
}

long File::size (void)
{
	long result = 0;
	long position = 0;
	if (!mFile)
	{
		return ERROR_SEEKING;
	}
	position = ftell(mFile);
	if (fseek(mFile, 0, SEEK_END))
	{
		return ERROR_SEEKING;
	}
	result = ftell(mFile);
	if (fseek(mFile, position, SEEK_SET))
	{
		return ERROR_SEEKING;
	}
	return result;
}