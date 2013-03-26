#ifndef PARSER_HPP
#define PARSER_HPP

#include "share.hpp"
#include <iostream>
#include <sstream>
#include <vector>

class parser
{
	std::string in;

public:
	parser(const std::string& in);
	~parser();
	
	std::vector<share_t> parse_csv(const std::string& name, const std::string& cont);
private:
	std::vector<std::string> split (const std::string& str, const std::string& del);
	int str_to_int (const std::string& str);
	float str_to_flt (const std::string& str);
};
#endif
