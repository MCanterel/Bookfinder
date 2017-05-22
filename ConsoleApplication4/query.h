#pragma once

#define URL "http://www.addall.com/New/submitNew.cgi"

using namespace std;

int sendQuery(vector<string>);
string formFileName(string);
string formQuery(string);
int webQuery(string);

unsigned int write_data(const void *ptr, unsigned int size, unsigned int nmeb,
	FILE *stream);

