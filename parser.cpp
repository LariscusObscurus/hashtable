#include "parser.hpp"
#include <sstream>

parser::parser(const std::string& input) 
{
	in = input;
}

parser::~parser (void)
{
}

std::vector<share_t> parser::parse_csv(const std::string& name, const std::string& cont) 
{
	std::vector<std::string> tokens;
	std::vector<share_t> imp_share;
	std::string delimiters ("-,\n");

	/* Erste Zeile abtrennen */
	std::string::size_type l_pos = in.find_first_of("\n", 0);
	std::string::size_type pos = in.find_first_of(delimiters, l_pos);

	while (std::string::npos != pos || std::string::npos != l_pos) {
		tokens.push_back (in.substr(l_pos, pos - l_pos));
		l_pos = in.find_first_not_of (delimiters, pos);
		pos = in.find_first_of (delimiters, l_pos);
	}
	
	imp_share = std::vector<share_t>(tokens.size() / 9);
	
	for (int j = 0; j < (tokens.size() / 9); j++) {
		
		imp_share[j].name = name;
		imp_share[j].cont = cont;
		
		for (int i = 0; i <= 9; i++) {
			switch(i){
			case 0:
				imp_share[j].date.year = token[j * 9 + i];
				break;
			case 1:
				imp_share[j].date.month = token[j * 9 + i];
				break;
			case 2:
				imp_share[j].date.day = token[j * 9 + i];
				break;
			case 3:
				imp_share[j].open = token[j * 9 +i];
				break;
			case 4:
				imp_share[j].high = token[j * 9 +i];
				break;
			case 5:
				imp_share[j].low = token[j * 9 +i];
				break;
			case 6:
				imp_share[j].close = token[j * 9 +i];
				break;
			case 7:
				imp_share[j].volume = token[j * 9 +i];
				break;
			case 8:
				imp_share[j].adjClose = token[j * 9 +i];
				break;
			}
		}
	}
	
	return imp_share;
}

std::vector<std::string> parser::split (const std::string& str, const std::string& del)
{
	using namespace std;
	stringstream ss(str);
	string item;
}