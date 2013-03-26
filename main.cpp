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
std::vector<share_t> add (void);
void del (std::string& str, omode_t& mode);

int main (void)
{
	hashtable* table = new hashtable();
	IPlotter* plotter = dynamic_cast<IPlotter*>(new Plotter());
	
	int chosen;
	std::string str;
	std::string name;
	std::string cont;
	omode_t mode;
	std::vector<share_t> shares;

	while(chosen != EXIT) {
		cout << "MENU:\n"
		<< "1.) ADD    - Add an additional entry to the hashtable.\n"
		<< "2.) DEL    - Delete an entry in the hashtable.\n"
		<< "3.) IMPORT - Import data from a csv file.\n"
		<< "4.) SEARCH - Search for a share.\n"
		<< "5.) PLOT   - Plot last 30 closings for a share.\n"
		<< "6.) SAVE   - Save the current hashtable.\n"
		<< "7.) LOAD   - Load a previously saved hashtable.\n"
		<< "8.) EXIT   - Exit this programm." << endl;

		cin >> chosen;
		switch(chosen) {
			case ADD: {
				if (table->add(add()))
				{
					cout << "Added." << endl;
				}
				else
				{
					cout << "Not added." << endl;
				}
				break;
			}
			case DEL: {
				del(str, mode);
				
				if (table->del(str, mode))
				{
					cout << "Deleted." << endl;
				}
				else
				{
					cout << "Not deleted." << endl;
				}
				break;
			}
			case IMPORT: {
				cout << "Enter the csv file name: ";
				cin >> str;
				getName(name);
				getContraction(cont);
				shares = file_handling::import(str, name, cont);
				
				if (!shares.size())
				{
					cout << "An error occured." << endl;
				}
				else
				{
					table->add(shares);
					cout << "Added content from file '" << str << "'." << endl;
				}
				break;
			}
			case SEARCH: {
				getMode(mode);
				
				switch (mode) {
				case NAME:
					getName(str);
					break;
				case CONT:
					getContraction(str);
					break;
				}
				
				if (table->find(str, shares, mode))
				{
					cout << "'" << str << "' exist and it's values are:\n";
					cout << "Open: " << shares[0].open << "\n";
					cout << "High: " << shares[0].high << "\n";
					cout << "Low: " << shares[0].low << "\n";
					cout << "Close: " << shares[0].close << "\n";
					cout << "Volume: " << shares[0].volume << "\n";
					cout << "Adjusted Close: " << shares[0].adjClose << endl;
				}
				else
				{
					cout << "Couldn't find '" << str << "'." << endl;
				}
				break;
			}
			case PLOT: {
				getMode(mode);
				
				switch (mode) {
				case NAME:
					getName(str);
					break;
				case CONT:
					getContraction(str);
					break;
				}
				
				if (table->find(str, shares, mode))
				{
					plotter->plot(shares);
				}
				else
				{
					cout << "Couldn't find '" << str << "'." << endl;
				}
				break;
			}
			case SAVE: {
				cout << "Enter the file name to store the hash table: ";
				cin >> str;
				if (file_handling::save(str, *table))
				{
					cout << "File with name '" << str << "' were successfull saved." << endl;
				}
				else
				{
					cout << "An error occured while writing process." << endl;
				}
				break;
			}
			case LOAD: {
				cout << "Enter the file name to load content into the hash table: ";
				cin >> str;
				if (file_handling::load(str, *table))
				{
					cout << "File with name '" << str << "' were successfull saved." << endl;
				}
				else
				{
					cout << "An error occured while writing process." << endl;
				}
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
		cout << endl;
		str = "";
		name = "";
		cont = "";
	}
	delete plotter;
	delete table;
	return EXIT_SUCCESS;
}

void getMode (omode_t& mode)
{
	cout << "Do you wish do enter a name or a contraction? (1 = name, 2 = contraction)" << endl;
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
			mode = CONT;
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

std::vector<share_t> add (void)
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