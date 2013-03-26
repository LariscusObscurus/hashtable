#ifndef FILEHANDLING_HPP
#define FILEHANDLING_HPP
#include <cstdio>
#include <string>
#include <vector>
#include "hash.hpp"
#include "hashtable.hpp"
#include "share.hpp"

class file_handling
{
public:
	static std::vector<share_t> import(const std::string& fileName, const std::string& name, const std::string& cont);
	static bool load (const std::string& fileName, hashtable& table);
	static bool save (const std::string& fileName, const hashtable& table);
};
#endif
