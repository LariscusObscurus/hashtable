#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>
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
};
#endif
