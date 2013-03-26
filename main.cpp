#include <cstdio>
#include <cstdarg>
#include <string>
#include <vector>
#include "filehandling.hpp"	
#include "hash.hpp"
#include "parser.hpp"
#include "plotter.hpp"
#include "share.hpp"

#define	ADD	1
#define	DEL	2
#define	LOAD	3
#define	IMPORT	4
#define SAVE	5
#define	EXIT	0

using namespace std;

std::vector<share_t> shares add (void);

int main (void)
{
	hashtable table = new hashtable();
	parser csvParser = new parser();
	IPlotter* plotter = new dynamic_cast<IPlotter*>(new Plotter());
	
	int chosen;
	bool finished = false;

	while(!finished) {
		cout << "MENU:\n"
		<< "1.) ADD    - Add an additional entry to the hashtable.\n"
		<< "2.) DEL    - Delete an entry in the hashtable.\n"
		<< "3.) IMPORT - Import data from a csv file.\n"
		<< "4.) SEARCH - Search for a share\n"
		<< "5.) PLOT   - Plot last 30 closings for a share\n"
		<< "6.) SAVE   - Save the current hashtable\n"
		<< "7.) LOAD   - Load a previously saved hashtable\n"
		<< "8.) EXIT   - Exit this programm." << endl;

		cin >> chosen;
		switch(chosen) {
		case ADD: {
			table.add(add());;
			break;
		}
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
	return EXIT_SUCCESS;
}

share_t add (void)
{
	std::vector<share_t> result;
	share_t share;
	cout << "Enter a name: ";
	cin >> share.name;
	cout << "Enter a contraction: ";
	cin >> share.cont;
	cout << "Enter a date (m/d/y): ";
	cin >> share.date.month;
	cin >> share.date.day;
	cin >> share.date.year;
	cout << "Enter an open value: ";
	cin >> share.open;
	cout << "Enter an high value: ";
	cin >> share.high;
	cout << "Enter a low value: ";
	cin >> share.low;
	cout << "Enter a closing value: ";
	cin >> share.close;
	cout << "Enter a volume value: ";
	cin >> share.volume;
	cout << "Enter a adjusted closing value: ";
	cin >> share.adjClose;
	cout << "Finished with manual input" << endl;
	result = std::vector<share_t>(1, share);
	return result;
}