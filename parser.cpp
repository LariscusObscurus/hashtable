#include "parser.hpp"
#ifdef _DEBUG
#include <iostream>
#endif

parser::parser(void) 
{
}

parser::~parser (void)
{
}

std::vector<share_t> parser::parse_csv(const std::string& in, 
			const std::string& name, 
			const std::string& cont) 
{
	std::vector<std::string> tokens;
	std::vector<share_t> imp_share;
	std::string delimiters ("-,\n");

	/* Erste Zeile abtrennen */
	std::string::size_type l_pos = in.find_first_of("\n", 0);
	std::string::size_type pos = in.find_first_of(delimiters, l_pos+1);

	while (std::string::npos != pos || std::string::npos != l_pos) {
		tokens.push_back (in.substr(l_pos, pos - l_pos));
		l_pos = in.find_first_not_of (delimiters, pos);
		pos = in.find_first_of (delimiters, l_pos);
	}
	
	
	imp_share = std::vector<share_t>(tokens.size() / 9);
	
	for (unsigned j = 0; j < (tokens.size() / 9); j++) {
		
		imp_share[j].name = name;
		imp_share[j].cont = cont;
		
		for (int i = 0; i <= 9; i++) {
			switch(i){
			case 0:
				imp_share[j].date.year = str_to_int(tokens[j * 9 + i]);
				break;
			case 1:
				imp_share[j].date.month = str_to_int(tokens[j * 9 + i]);
				break;
			case 2:
				imp_share[j].date.day = str_to_int(tokens[j * 9 + i]);
				break;
			case 3:
				imp_share[j].open = str_to_flt(tokens[j * 9 +i]);
				break;
			case 4:
				imp_share[j].high = str_to_flt(tokens[j * 9 +i]);
				break;
			case 5:
				imp_share[j].low = str_to_flt(tokens[j * 9 +i]);
				break;
			case 6:
				imp_share[j].close = str_to_flt(tokens[j * 9 +i]);
				break;
			case 7:
				imp_share[j].volume = str_to_long(tokens[j * 9 +i]);
				break;
			case 8:
				imp_share[j].adjClose = str_to_flt(tokens[j * 9 +i]);
				break;
			}
		}
	}
	return imp_share;
}

/*std::vector<std::string> parser::split (const std::string& str, const std::string& del)
{
	std::stringstream ss(str);
	std::string item;
}*/

int parser::str_to_int (const std::string& str) 
{
	int result;
	std::stringstream sstr(str);
	sstr >> result;
	return result;
}

float parser::str_to_flt (const std::string& str) 
{
	float result;
	std::stringstream sstr(str);
	sstr >> result;
	return result;
}

long parser::str_to_long (const std::string& str)
{
	long result;
	std::stringstream sstr(str);
	sstr >> result;
	return result;
}
