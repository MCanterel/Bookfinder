// process.cpp
//book data manip funcs

#include "stdafx.h"
#include <iostream>
#include <Windows.h>
#include "process.h"
using namespace std;

string getBookISBN() {
	string bookStr;
	cout << endl << "Enter ISBN number: " << endl;
	cin >> bookStr;
	cin.ignore();  //flushes extra characters in buffer so it's clean for next call to getChoice()
	return bookStr;
}

void getBookData(string _bookHTMLFile) {

	string line;

	const string searchPhrase1 = "<TD VALIGN=BOTTOM ALIGN=LEFT><B>TITLE: </B> <font FACE=ARIAL COLOR=#006699>";
	//capture this and the next 2 lines

	const string searchPhrase2 = "<B>Click<br> to Buy</B>";
	//capture the following line

	string bookTitle = "";
	string bookAuthor = "";
	string bookISBN = "";
	string bookPrice = "";

	int captureInfoCountdown = 0;
	int capturePriceCountdown = 0;

	ifstream bookFile;
	bookFile.open(_bookHTMLFile);

	while (std::getline(bookFile, line))
	{
		std::size_t foundTitle = line.find(searchPhrase1);
		std::size_t foundPrice = line.find(searchPhrase2);

		if (captureInfoCountdown == 1) {
			std::smatch m1;
			std::regex_search(line, m1, std::regex("(?:B> )[a-zA-Z0-9,-]+"));
			bookISBN.assign(m1.str());
			captureInfoCountdown--;
		}

		if (captureInfoCountdown == 2) {  //keep this item as is
			bookAuthor.assign(line);
			captureInfoCountdown--;
		}
		if (capturePriceCountdown >= 1) capturePriceCountdown--;
		if (capturePriceCountdown == 1) {
			std::smatch m2;
			std::regex_search(line, m2, std::regex("[0-9]*\.[0-9]+(?=<)"));
			bookPrice.assign(m2.str());
			capturePriceCountdown--;
		}

		if (foundTitle != std::string::npos) {
			std::smatch m3;
			std::regex_search(line, m3, std::regex("(?:006699> ).*(?=<\/font)"));
			string m3b = m3.str();
			m3b.erase(m3b.begin(), m3b.begin() + 8);
			bookTitle.assign(m3b);
			captureInfoCountdown = 2;
		}

		if (foundPrice != std::string::npos) {
			capturePriceCountdown = 5;
		}
	}

	cout << endl;
	cout << "................RESULTS................" << endl << endl;
	cout << "Title: " << bookTitle << endl;
	cout << "Author: " << bookAuthor << endl;
	cout << "ISBN: " << bookISBN << endl;
	cout << "PRICE: " << bookPrice << endl << endl;

	system("PAUSE");
}

int stepThroughResultsDir()
{
	WIN32_FIND_DATA data;
	//look in 'results' folder, created in query.cpp
	HANDLE h = FindFirstFile(L".\\results\\*.*", &data);

	if (h != INVALID_HANDLE_VALUE)
	{
		do
		{
			char*   nPtr = new char[lstrlen(data.cFileName) + 1];
			for (int i = 0; i < lstrlen(data.cFileName); i++)
				nPtr[i] = char(data.cFileName[i]);

			nPtr[lstrlen(data.cFileName)] = '\0';
			//cout << nPtr << endl;

			string fName = string(nPtr);
			if (fName != "." && fName != "..") {
				string fullPathtoResult;
				fullPathtoResult = ".\\results\\" + fName;
				//cout << "This is the full path to the file: " << fullPathtoResult << endl;
				getBookData(fullPathtoResult);
			}
		} while (FindNextFile(h, &data));
	}
	else
		cout << "Error: No such folder." << endl;

	FindClose(h);

	return 0;
}

