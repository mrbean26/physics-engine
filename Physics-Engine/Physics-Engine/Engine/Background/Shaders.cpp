#include <Engine/Background/Shaders.h>

#include <glm/gtc/type_ptr.hpp>

#include <fstream>
#include <iostream>
#include <string>

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

int CreateShader(const char* filePath, GLenum shaderType) {
	// get lines from file
	string allLines;
	vector<string> shaderLines = readLines(filePath);
	for (string line : shaderLines) {
		allLines = allLines + line + "\n";
	}
	const char* shaderSource = allLines.data();
	// compile
	int newShader = glCreateShader(shaderType);
	glShaderSource(newShader, 1, &shaderSource, NULL);
	glCompileShader(newShader);
	int compileResult;
	char infoLog[512];
	glGetShaderiv(newShader, GL_COMPILE_STATUS, &compileResult);
	if (!compileResult) {
		glGetShaderInfoLog(newShader, 512, NULL, infoLog);
		cout << "Shader compilation error: " << infoLog << endl;
		return 0;
	}
	return newShader;
}
int CreateProgram(vector<int> shaders) {
	int newProgram = glCreateProgram();
	int shaderCount = shaders.size();
	for (int i = 0; i < shaderCount; i++) {
		glAttachShader(newProgram, shaders[i]);
	}
	glLinkProgram(newProgram);
	return newProgram;
}

void SetShaderInt(int shader, const char* intName, int usedInt) {
	int location = glGetUniformLocation(shader, intName);
	glUniform1i(location, usedInt);
}
void SetShaderMat4(int shader, const char* matrixName, mat4 usedMatrix) {
	int location = glGetUniformLocation(shader, matrixName);
	glUniformMatrix4fv(location, 1, GL_FALSE, value_ptr(usedMatrix));
}
void SetShaderVec3(int shader, const char* vectorName, vec3 usedVector) {
	int location = glGetUniformLocation(shader, vectorName);
	glUniform3f(location, usedVector.x, usedVector.y, usedVector.z);
}