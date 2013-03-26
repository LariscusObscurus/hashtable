#include <cstdio>
#include <cstdarg>
#include <string>
#include <vector>
#include "filehandling.hpp"	
#include "hash.hpp"
#include "parser.hpp"
#include "plotter.hpp"
#include "share.hpp"


using namespace std;

int main (void)
{
	hashtable table = new hashtable();
	parser csvParser = new parser();
	IPlotter* plotter = new dynamic_cast<IPlotter*>(new Plotter());
	return 0;
}
