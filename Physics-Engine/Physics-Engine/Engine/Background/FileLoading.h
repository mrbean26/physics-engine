#pragma once

#include <vector>
#include <string>

using namespace std;

vector<string> readLines(const char* fileName);

vector<string> splitCharacter(string inputString, char character);

bool containsSubstring(string mainString, string subString);

string afterString(string mainString, string subString);