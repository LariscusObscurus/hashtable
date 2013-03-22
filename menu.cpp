#include "menu.hpp"
#include <iostream>

using namespace std;
int menu()
{
	int chosen;
	bool finished = false;

	while(!finished) {
		cout << "MENU:\n"
		<< "1.) ADD - Add an additional entry to the hashtable.\n"
		<< "2.) DEL - Delete an entry in the hashtable.\n"
		<< "3.) LOAD - Load a previously saved hashtable\n"
		<< "4.) SAVE - Save the current hashtable\n"
		<< "5.) IMPORT - Import data from a csv file.\n"
		<< "0.) EXIT - Exit this programm." << endl;

		cin >> chosen;
		switch(chosen) {
		case ADD:
			break;
		case DEL:
			break;
		case LOAD:
			break;
		case SAVE:
			break;
		case IMPORT:
			break;
		case EXIT:
			finished = true;
		default:
			cout << "This is not an option";
		}
	}
	return 0;
}

