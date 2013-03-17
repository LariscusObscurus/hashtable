#include "filehandling.hpp"

file_handling::file_handling (
	const std::string& file_name, 
	const std::string& mode)
{
	fp = fopen(file_name.c_str(), mode.c_str());
}

file_handling::~file_handling()
{
	if(fp) {
		fclose(fp);
	}
}

std::vector<share_t> file_handling::import(const std::string& name, const std::string& cont)
{
	if (fp)
	{
		fseek(fp, 0, SEEK_END);
		long f_size = ftell(fp);
		fseek(fp, 0, SEEK_SET);
		char *buf = new char[f_size];
		fread(buf, sizeof(char), f_size, fp);
		std::string text(buf);
		delete[] buf;
		parser prs_text(text);
		return prs_text.parse_csv(name, cont);
	}
	return std::vector<share_t>(0);
}
