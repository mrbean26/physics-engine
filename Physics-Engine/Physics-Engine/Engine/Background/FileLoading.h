#pragma once

#include <vector>
#include <string>

using namespace std;

vector<string> readLines(const char* fileName);

vector<string> splitCharacter(string inputString, char character);

bool FileExists(string Filename);

bool containsSubstring(string mainString, string subString);
bool EndsInString(string MainString, string SubString);
string afterString(string mainString, string subString);