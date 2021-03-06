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
		if (input == 1) {
			string bookInput = m.getBookISBN();
			bookNums.push_back(bookInput);
			cout << "You inputted: " << bookInput << endl;
		}
		if (input == 2) {
			if (bookNums.size() > 0) {

				for (unsigned int i = 0; i < bookNums.size(); i++) {
					cout << "Item # " << i + 1 << ": " << bookNums[i] << endl;
				}
			}
		}

		if (input == 3) {
			//send query and clear bookNums
			if (sendQuery(bookNums) == 1) {
				bookNums.clear();
			}
			else {
				cout << "Unable to query web for these listings. Try again." << endl;
			}
		}
		
	} while (input < MENUCOUNT);

	cout << "Goodbye!" << endl;
	return 0;
}

