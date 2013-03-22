#ifndef FILEHANDLING_HPP
#define FILEHANDLING_HPP
#include <cstdio>
#include <string>
#include <vector>
#include "share.hpp"

class file_handling
{
	FILE * fp;
public:
	file_handling (const std::string& file_name, const std::string& mode);
	~file_handling ();

	std::vector<share_t> import(const std::string& name, const std::string& cont);
	int save();
	int load();
};
#endif
