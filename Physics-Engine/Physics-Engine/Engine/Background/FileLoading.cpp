#include <Engine/Background/FileLoading.h>

#include <fstream>
#include <iostream>
#include <sstream>

vector<string> readLines(const char* fileName) {
	vector<string> allLines;
	ifstream newFile(fileName);
	string currentLine;

	if (!newFile) {
		cout << "File could not be opened: " << fileName << endl;
	}
	while (getline(newFile, currentLine)) {
		allLines.push_back(currentLine);
	}

	return allLines;
}

vector<string> splitCharacter(string inputString, char character) {
	vector<string> result;
	stringstream stringStream(inputString);

	while (stringStream.good()) {
		string subString;
		getline(stringStream, subString, character);
		result.push_back(subString);
	}

	return result;
}

bool containsSubstring(string mainString, string subString) {
	if (mainString.find(subString) != string::npos) {
		return true;
	}
	return false;
}

string afterString(string mainString, string subString) {
	return mainString.substr(mainString.find(subString) + 1);
}