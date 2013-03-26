#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include "filehandling.hpp"	
#include "hash.hpp"
#include "parser.hpp"
#include "plotter.hpp"
#include "share.hpp"

#define	ADD	1
#define	DEL	2
#define IMPORT	3
#define SEARCH	4
#define PLOT	5
#define SAVE	6
#define	LOAD	7
#define	EXIT	8

using namespace std;

void getMode (omode_t& mode);
void getName (std::string& str);
void getContraction (std::string& str);
std::vector<share_t> shares add (void);
void del (std::string& str, omode_t& mode);

int main (void)
{
	hashtable table = new hashtable();
	parser csvParser = new parser();
	IPlotter* plotter = new dynamic_cast<IPlotter*>(new Plotter());
	
	int chosen;

	while(chosen != EXIT) {
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
				if (table.add(add()))
				{
					cout << "added" << endl;
				}
				else
				{
					cout << "not added" << endl;
				}
				break;
			}
			case DEL: {
				std::string str;
				omode_t mode;
				del(str, mode);
				
				if (table.del(str, mode))
				{
					cout << "deleted" << endl;
				}
				else
				{
					cout << "not deleted" << endl;
				}
				break;
			}
			case IMPORT: {
				break;
			}
			case SEARCH: {
				break;
			}
			case PLOT: {
				break;
			}
			case SAVE: {
				break;
			}
			case LOAD: {
				break;
			}
			case EXIT: {
				cout << "Bye." << endl;
				break;
			}
			default:
			cout << "This is not an option" << endl;
			break;
		}
	}
	return EXIT_SUCCESS;
}

void getMode (omode_t& mode)
{
	cout << "Do you wish do enter a new or a contraction? (1 = name, 2 = contraction)" << endl;
	while (true)
	{
		int result = 0;
		cout << "Input: ";
		cin >> result;
		
		if (result == 1)
		{
			mode = NAME;
			break;
		}
		else if (result == 2)
		{
			mode == CONT;
			break;
		}
		else
		{
			cout << "Couldn't verify input, please enter again." << endl;
		}
	}
}

void getName (std::string& str)
{
	cout << "Please enter a name: ";
	cin >> str;
	cout << endl;
}

void getContraction (std::string& str)
{
	cout << "Please enter a contraction: ";
	cin >> str;
	cout << endl;
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

void del (std::string& str, omode_t& mode)
{
	getMode(mode);
	
	switch (mode)
	{
	case NAME: {
		getName(str);
		break;
	}
	case CONT: {
		getContraction(str);
	}
	}
}