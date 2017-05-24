//============================================================================
// Name        : stringfind.cpp
// Author      : jnc
// Version     :
// Copyright   : Your copyright notice
// Description : testing string parsing of html file
// to be integrated with booksearch
//============================================================================

#include "stdafx.h"
using namespace std;

void getBookData(string _bookHTMLFile) {

	string line;

	bool trigger = false;
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
			//cout << m3b << endl;
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


int stepThroughResultsDir(LPCSTR _resultsDir)
{
	WIN32_FIND_DATA data;
	//HANDLE hFind = FindFirstFile(".\\results\\*.*", &data);      // DIRECTORY
	HANDLE hFind = FindFirstFile(_resultsDir, &data);      // DIRECTORY

	if (hFind != INVALID_HANDLE_VALUE) {
		//int counter = 1;
		do {
			std::basic_string<TCHAR> myString(data.cFileName);
			if ((myString != ".") && (myString != "..")) {
				string fullPathtoResult = ".\\results\\" + myString;
				//cout << "Here: " <<fullPathtoResult << endl;
				getBookData(fullPathtoResult);
			}
		} while (FindNextFile(hFind, &data));
		FindClose(hFind);
	}
	return 0;
}

//int oldmain() {
//	//stepThroughResultsDir(".\\results\\*.*");
//	//stepThroughResultsDir(resultsDir);
//	return 0;
//}


