#include "stdafx.h"

Menu::Menu()
{
	//cout << "new menu" << endl;
}

Menu::~Menu()
{
}

void Menu::display() {
	cout << endl;
	cout << "_____________ book finder _____________" << endl;
	cout << endl;
	cout << "1- Enter book info." << endl;
	cout << "2- Review book info." << endl;
	cout << "3- Send query." << endl;
	cout << "4- Quit." << endl;
	cout << endl;
}

int Menu::getChoice() {
	int x = 0;
	bool loop = true;
	while (loop)
	{
		cout << "Select an option..." << endl<<endl;

		string s;
		
		getline(cin, s);

		std::stringstream stream(s);
		if (stream >> x)
		{
			if (x > 0 || x <= MENUCOUNT) {
				loop = false;
				continue;
			}
		}
		std::cout << "Invalid entry!" << std::endl;
	}

	return x;
}

string Menu::getBookISBN() {
	string bookStr;
	cout <<endl << "Enter ISBN number: " << endl;
	cin >> bookStr;
	cin.ignore();  //flushes extra characters in buffer so it's clean for next call to getChoice()
	return bookStr;
}