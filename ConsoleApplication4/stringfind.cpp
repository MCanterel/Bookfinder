// folder_manipulation.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <Windows.h>
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

int stepThroughResultsDir()
{
	WIN32_FIND_DATA data;
	//HANDLE h = FindFirstFile(L"c:\\*.*", &data);
	HANDLE h = FindFirstFile(L".\\results\\*.*", &data);

	if (h != INVALID_HANDLE_VALUE)
	{
		do
		{
			char*   nPtr = new char[lstrlen(data.cFileName) + 1];
			for (int i = 0; i < lstrlen(data.cFileName); i++)
				nPtr[i] = char(data.cFileName[i]);

			nPtr[lstrlen(data.cFileName)] = '\0';
			string coreFileName = string(nPtr);
			if (coreFileName != "." && coreFileName != "..") {
				string fullPathtoResult = ".\\results\\" + coreFileName;
				//fullPathtoResult = ".\\results\\" + string(nPtr);
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

int callRoutine() {
	stepThroughResultsDir();
	return 0;
}