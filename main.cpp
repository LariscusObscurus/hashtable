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

int main(int argc, const char *argv[])
{
	string chosen;
	bool finished = false;

	while(!finished) {
		cout << "MENU:\n"
		<< "ADD - Add an additional entry to the hashtable.\n"
		<< "DEL - Delete an entry in the hashtable.\n"
		<< "LOAD - Load a previously saved hashtable\n"
		<< "SAVE - Save the current hashtable\n"
		<< "IMPORT - Import data from a csv file.\n"
		<< "EXIT - Exit this programm." << endl;

		cin >> chosen;
		switch(chosen) {
		case ADD:
		case add:
			break;
		case DEL:
		case del:
			break;
		case LOAD:
		case load:
			break;
		case SAVE:
		case save:
			break;
		case IMPORT:
		case import:
			break;
		case EXIT:
		case exit:
			finished = true;
		default:
			cout << "This is not an option";
		}
	}
	return 0;
}
