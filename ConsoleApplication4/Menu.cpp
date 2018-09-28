#include "stdafx.h"

Menu::Menu() {
	menu = "\n_____________ book finder _____________\n1- Enter book info.\n2- Review book info.\n3- Send query.\n";
	menu += ("4- Review downloaded book data.\n5- Quit!\n\n");
}


void Menu::display() {
	cout << menu;
}

int Menu::getChoice() {
	int x = 0;
	bool loop = true;
	while (loop)
	{
		cout << "Select an option..." << endl << endl;

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
