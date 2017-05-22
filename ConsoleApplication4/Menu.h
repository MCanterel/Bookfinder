#pragma once
class Menu
{

public:
	Menu();
	~Menu();
	void display();
	int getChoice();
	//int getInt();
	std::string getBookISBN();
};