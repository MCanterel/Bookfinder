// ConsoleApplication4.cpp : Defines the entry point for the console application.

#include "stdafx.h"

vector<string> bookNums;


int main()
{
	int input;

	Menu m;

	do {
		m.display();

		input = m.getChoice();
		if (input == 1) {  // INPUT ISBN INFO
			string bookInput = m.getBookISBN();
			bookNums.push_back(bookInput);
			cout << "You just inputted: " << bookInput << endl;
		}
		if (input == 2) {  // REVIEW ISBN INFO
			if (bookNums.size() > 0) {

				for ( unsigned int i = 0; i < bookNums.size(); i++) {
					cout << "Item # " << i + 1 << ": " << bookNums[i] << endl;
				}
			}
			else { cout << "No items to review." << endl; }
		}

		if (input == 3) { 	//SEND QUERY AND CLEAR BOOKNUMS
			if (sendQuery(bookNums) == 1) {
				bookNums.clear();
			}
			else {
				cout << "Unable to query web for these listings. Try again." << endl;
			}
		}

		if (input == 4) { 	//REVIEW DOWNLOADED BOOK DATA
			stepThroughResultsDir();
		}

	} while (input <= MENUCOUNT);

	cout << "Goodbye!" << endl;
	return 0;
}