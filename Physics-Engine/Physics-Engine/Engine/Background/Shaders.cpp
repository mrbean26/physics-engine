#include <Engine/Background/Shaders.h>
#include <Engine/Background/FileLoading.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <string>

int CreateShader(const char* filePath, GLenum shaderType) {
	if (!FileExists(filePath)) {
		throw ("File does not exist: " + string(filePath)).data();
	}

	// get lines from file
	vector<string> shaderLines = readLines(filePath);
	int LineCount = int(shaderLines.size());

	string allLines;
	for (int i = 0; i < LineCount; i++) {
		allLines = allLines + shaderLines[i] + "\n";
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
	int shaderCount = int(shaders.size());
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
void SetShaderFloat(int shader, const char* floatName, float usedFloat) {
	int location = glGetUniformLocation(shader, floatName);
	glUniform1f(location, usedFloat);
}

void OutputVec3(vec3 input) {
	cout << input.x << " " << input.y << " " << input.z << endl;
}

GLuint LoadTexture(const char* filePath) {
	if (!EndsInString(filePath, ".png")) {
		throw ("Incorrect Filetype for Image: " + string(filePath)).data();
	}
	if (!FileExists(filePath)) {
		throw ("File does not exist: " + string(filePath)).data();
	}

	// Load Image Data
	int width, height, channels;

	stbi_set_flip_vertically_on_load(true);
	unsigned char* imageData = stbi_load(filePath, &width, &height, &channels, 4);

	if (!imageData) {
		cout << "Failed Image Load: " << filePath << endl;
	}
	
	// Set Image Data 
	GLuint newTextureID;

	glGenTextures(1, &newTextureID);
	glBindTexture(GL_TEXTURE_2D, newTextureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
	glGenerateMipmap(GL_TEXTURE_2D);

	return newTextureID;
}