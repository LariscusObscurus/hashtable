#include <iostream>
#include <string>
#include <vector>
#include <sstream>
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

template <typename T>
std::string numberToString (T Number)
{
	std::stringstream ss;
	ss << Number;
	return ss.str();
}

template <typename T>
T stringToNumber (const std::string &Text)//Text not by const reference so that the function can be used with a 
{                               //character array as argument
	stringstream ss(Text);
	T result;
	return ss >> result ? result : 0;
}

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
		<< "8.) EXIT   - Exit this programm.\n"
		<< "Input: ";

		cin >> str;
		chosen = stringToNumber<int>(str);
		switch(chosen) {
			case ADD: {
				if (table->add(add()))
				{
					cout << "Added.\n";
				}
				else
				{
					cout << "Not added.\n";
				}
				break;
			}
			case DEL: {
				del(str, mode);
				
				if (table->del(str, mode))
				{
					cout << "Deleted.\n";
				}
				else
				{
					cout << "Not deleted.\n";
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
					cout << "An error occured.\n";
				}
				else
				{
					if (table->add(shares))
					{
						cout << "Added content from file '" << str << "'.\n";
					}
					else
					{
						cout << "Couldn't add content from file '" << str << "'.\n";
					}
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
					int size = shares.size() < 30 ? (int)shares.size() : 30;
					cout << "'" << str << "' exist and it's values are:\n";
					cout << "+------------------------------" << "\n";
					for (int i = 0; i < size; i++)
					{
						cout << shares[i].date.month << "/" << shares[i].date.day << "/" << shares[i].date.year << "\n";
						cout << "Open: " << shares[i].open << "\n";
						cout << "High: " << shares[i].high << "\n";
						cout << "Low: " << shares[i].low << "\n";
						cout << "Close: " << shares[i].close << "\n";
						cout << "Volume: " << shares[i].volume << "\n";
						cout << "Adjusted Close: " << shares[i].adjClose << "\n";
						cout << "+------------------------------\n";
					}
				}
				else
				{
					cout << "Couldn't find '" << str << "'.\n";
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
					cout << "Couldn't find '" << str << "'.\n";
				}
				break;
			}
			case SAVE: {
				cout << "Enter the file name to store the hash table: ";
				cin >> str;
				if (file_handling::save(str, *table))
				{
					cout << "File with name '" << str << "' were successfully saved.\n";
				}
				else
				{
					cout << "An error occured while writing process.\n";
				}
				break;
			}
			case LOAD: {
				cout << "Enter the file name to load content into the hash table: ";
				cin >> str;
				if (file_handling::load(str, *table))
				{
					cout << "File with name '" << str << "' were successfully loaded.\n";
				}
				else
				{
					cout << "An error occured while writing process.\n";
				}
				break;
			}
			case EXIT: {
				cout << "Bye.\n";
				break;
			}
			default:
				cout << "This is not an option\n";
				chosen = 0;
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
		std::string str;
		int result = 0;
		cout << "Input: ";
		cin >> str;
		result = stringToNumber<int>(str);
		
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
}

void getContraction (std::string& str)
{
	cout << "Please enter a contraction: ";
	cin >> str;
}

std::vector<share_t> add (void)
{
	std::string str;
	std::vector<share_t> result;
	share_t share;
	cout << "Enter a name: ";
	cin >> share.name;
	cout << "Enter a contraction: ";
	cin >> share.cont;
	cout << "Enter a date (m/d/y): ";
	scanf("%d/%d/%d", &share.date.month, &share.date.day, &share.date.year);
	cout << "Enter an open value: ";
	cin >> str;
	share.open = stringToNumber<float>(str);
	cout << "Enter an high value: ";
	cin >> str;
	share.high = stringToNumber<float>(str);
	cout << "Enter a low value: ";
	cin >> str;
	share.low = stringToNumber<float>(str);
	cout << "Enter a closing value: ";
	cin >> str;
	share.close = stringToNumber<float>(str);
	cout << "Enter a volume value: ";
	cin >> str;
	share.volume = stringToNumber<long>(str);
	cout << "Enter a adjusted closing value: ";
	cin >> str;
	share.adjClose = stringToNumber<float>(str);
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
