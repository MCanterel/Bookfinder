#include "stdafx.h"

int sendQuery(vector<string> bookNums) {
	int result = 0;
	for (unsigned int i = 0; i < bookNums.size(); i++) {
		string str = bookNums[i];
		if (webQuery(str) == 1) {
			result = 1;
		}
		else {
			result = 0;
		}
	}
	return result;
}

unsigned int write_data(const void *ptr, unsigned int size, unsigned int nmeb,
	FILE *stream) {
	return (fwrite(ptr, size, nmeb, stream));
}

string formQuery(string _str) {

	string in_prepend = "query=";
	string in_append = "&type=ISBN"; //&submit=Submit
	string fullString = in_prepend + _str + in_append;
	return fullString;
}

string formFileName(string _str) {

	string s = "./results/";
	std::wstring stemp = std::wstring(s.begin(), s.end());
	LPCWSTR sw = stemp.c_str();
	if (CreateDirectory(sw, 0) || ERROR_ALREADY_EXISTS == GetLastError()) {
		cout << "success" << endl;
		string fileName;
		fileName = s + _str + ".html";
		return fileName;
	}
	else {
		return NULL;
	}
}

int webQuery(string str) {

	int res = (curl_global_init(CURL_GLOBAL_ALL));
	if (res != 0) {
		printf("LibCurl sucks!\n");
	}
	else {

		string fileName = formFileName(str);
		const char * fName = fileName.c_str();

		FILE* file = fopen(fName, "w");

		if (fName != NULL) {
			FILE* file = fopen(fName, "w");

			CURL *myHandle = curl_easy_init();
			if (myHandle) {
				string in_string = formQuery(str);
				const char *query = in_string.c_str();

				curl_easy_setopt(myHandle, CURLOPT_URL, URL);
				curl_easy_setopt(myHandle, CURLOPT_POSTFIELDSIZE_LARGE,
					(curl_off_t)-1);
				curl_easy_setopt(myHandle, CURLOPT_POSTFIELDS, query);
				curl_easy_setopt(myHandle, CURLOPT_POST, 1);
				curl_easy_setopt(myHandle, CURLOPT_WRITEFUNCTION, write_data); //Gets data to be written to file
				curl_easy_setopt(myHandle, CURLOPT_WRITEDATA, file); //Writes result to file
				curl_easy_setopt(myHandle, CURLOPT_VERBOSE, 1L);

				CURLcode result;
				result = curl_easy_perform(myHandle); // We’ll store the result of CURL’s webpage retrieval, for simple error checking.
				fclose(file);

				curl_easy_cleanup(myHandle);

				printf("Success!\n");
			}
			return 1 ;
		}
		else {
			cout << "Unable to open file" << endl;
			return 0;
		}
	}
}
