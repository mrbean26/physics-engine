#include <Engine/Engine.h>

#include <Engine/Background/Shaders.h>
#include <Engine/Background/FileLoading.h>

#include <Engine/Components/ViewModel.h>
#include <Engine/Components/Transform.h>
#include <Engine/Components/PointLight.h>
#include <Engine/Components/DirectionalLight.h>

#include <GLM/gtc/matrix_transform.hpp>

void ViewModel::Mainloop() {
	Initialise();
	Render();
}
void ViewModel::Initialise() {
	if (initialised) {
		return;
	}
	
	if (verticesType == VERTICES_POINTS_TEXTURE) {
		ObjectTextureID = LoadTexture(texturePath.data());
	}

	// Set Shaders To Uninitialised
	initialiseShader();
	InitialiseVertices();

	initialised = true;
}

void ViewModel::LoadOBJ(const char* filePath) {
	vertices.clear();

	vector<vec3> vertices;
	vector<vec2> textureVertices;
	vector<vec3> vertexNormals;

	vector<string> fileLines = readLines(filePath);
	int lineCount = fileLines.size();

	for (int i = 0; i < lineCount; i++) {
		vector<string> lineData = splitCharacter(fileLines[i], ' ');

		if (lineData[0] == "v") {
			vec3 newVertex = vec3(
				stof(lineData[1]),
				stof(lineData[2]),
				stof(lineData[3])
			);

			vertices.push_back(newVertex);
		}
		if (lineData[0] == "vt") {
			vec2 newTextureVertex = vec2(
				stof(lineData[1]),
				stof(lineData[2])
			);
			
			textureVertices.push_back(newTextureVertex);
		}
		if (lineData[0] == "vn") {
			vec3 newVertexNormal = vec3(
				stof(lineData[1]),
				stof(lineData[2]),
				stof(lineData[3])
			);

			vertexNormals.push_back(newVertexNormal);
		}

		if (lineData[0] == "f") {
			LoadOBJFace(lineData, vertices, textureVertices, vertexNormals);
		}
	}
}
void ViewModel::LoadOBJFace(vector<string> faceData, vector<vec3> fileVertices, vector<vec2> textureVertices, vector<vec3> vertexNormals) {
	ivec3 faceOne = LoadOBJFacePoint(faceData[1]);
	ivec3 faceTwo = LoadOBJFacePoint(faceData[2]);
	ivec3 faceThree = LoadOBJFacePoint(faceData[3]);

	if (verticesType == VERTICES_POINTS_ONLY) {
		// Face 1
		vertices.push_back(fileVertices[faceOne.x].x);
		vertices.push_back(fileVertices[faceOne.x].y);
		vertices.push_back(fileVertices[faceOne.x].z);
		
		vertices.push_back(fileVertices[faceOne.z].x);
		vertices.push_back(fileVertices[faceOne.z].y);
		vertices.push_back(fileVertices[faceOne.z].z);
		
		// Face 2
		vertices.push_back(fileVertices[faceTwo.x].x);
		vertices.push_back(fileVertices[faceTwo.x].y);
		vertices.push_back(fileVertices[faceTwo.x].z);

		vertices.push_back(fileVertices[faceTwo.z].x);
		vertices.push_back(fileVertices[faceTwo.z].y);
		vertices.push_back(fileVertices[faceTwo.z].z);

		// Face 3
		vertices.push_back(fileVertices[faceThree.x].x);
		vertices.push_back(fileVertices[faceThree.x].y);
		vertices.push_back(fileVertices[faceThree.x].z);

		vertices.push_back(fileVertices[faceThree.z].x);
		vertices.push_back(fileVertices[faceThree.z].y);
		vertices.push_back(fileVertices[faceThree.z].z);
	}
	if (verticesType == VERTICES_POINTS_TEXTURE) {
		// Face 1
		vertices.push_back(fileVertices[faceOne.x].x);
		vertices.push_back(fileVertices[faceOne.x].y);
		vertices.push_back(fileVertices[faceOne.x].z);

		vertices.push_back(textureVertices[faceOne.y].x);
		vertices.push_back(textureVertices[faceOne.y].y);

		vertices.push_back(fileVertices[faceOne.z].x);
		vertices.push_back(fileVertices[faceOne.z].y);
		vertices.push_back(fileVertices[faceOne.z].z);
		
		// Face 2
		vertices.push_back(fileVertices[faceTwo.x].x);
		vertices.push_back(fileVertices[faceTwo.x].y);
		vertices.push_back(fileVertices[faceTwo.x].z);

		vertices.push_back(textureVertices[faceTwo.y].x);
		vertices.push_back(textureVertices[faceTwo.y].y);

		vertices.push_back(fileVertices[faceTwo.z].x);
		vertices.push_back(fileVertices[faceTwo.z].y);
		vertices.push_back(fileVertices[faceTwo.z].z);
		
		// Face 3
		vertices.push_back(fileVertices[faceThree.x].x);
		vertices.push_back(fileVertices[faceThree.x].y);
		vertices.push_back(fileVertices[faceThree.x].z);
		
		vertices.push_back(textureVertices[faceThree.y].x);
		vertices.push_back(textureVertices[faceThree.y].y);

		vertices.push_back(fileVertices[faceThree.z].x);
		vertices.push_back(fileVertices[faceThree.z].y);
		vertices.push_back(fileVertices[faceThree.z].z);
	}
}
ivec3 ViewModel::LoadOBJFacePoint(string point) {
	ivec3 result = ivec3(-1, -1, -1);
	vector<string> indexes = splitCharacter(point, '/');
	
	result.x = stoi(indexes[0]) - 1;
	
	if (indexes[1] != "") {
		result.y = stoi(indexes[1]) - 1;
	}
	if (indexes[2] != "") {
		result.z = stoi(indexes[2]) - 1;
	}
	
	return result;
}

void ViewModel::initialiseShader() {
	if (verticesType == VERTICES_POINTS_ONLY && ViewModelPointsShader == -1) {
		int vertex = CreateShader("Assets/Shaders/ViewModelPoints_v.txt", GL_VERTEX_SHADER);
		int fragment = CreateShader("Assets/Shaders/ViewModelPoints_f.txt", GL_FRAGMENT_SHADER);

		ViewModelPointsShader = CreateProgram({ vertex, fragment });
	}
	if (verticesType == VERTICES_POINTS_TEXTURE && ViewModelPointsTextureShader == -1) {
		int vertex = CreateShader("Assets/Shaders/ViewModelPointsTexture_v.txt", GL_VERTEX_SHADER);
		int fragment = CreateShader("Assets/Shaders/ViewModelPointsTexture_f.txt", GL_FRAGMENT_SHADER);

		ViewModelPointsTextureShader = CreateProgram({ vertex, fragment });
	}
}

void ViewModel::InitialiseVertices() {
	glGenVertexArrays(1, &ObjectVAO);
	glBindVertexArray(ObjectVAO);

	glGenBuffers(1, &ObjectVBO);
	glBindBuffer(GL_ARRAY_BUFFER, ObjectVBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

	if (verticesType == VERTICES_POINTS_ONLY) {
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		ObjectDrawSize = vertices.size() / 6;
	}
	if (verticesType == VERTICES_POINTS_TEXTURE) {
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
		glEnableVertexAttribArray(2);

		ObjectDrawSize = vertices.size() / 8;
	}
}

void ViewModel::Render() {
	glBindVertexArray(ObjectVAO);
	GLuint usedShader;

	if (verticesType == VERTICES_POINTS_ONLY) {
		glUseProgram(ViewModelPointsShader);
		usedShader = ViewModelPointsShader;
	}
	if (verticesType == VERTICES_POINTS_TEXTURE) {
		glUseProgram(ViewModelPointsTextureShader);

		glActiveTexture(GL_TEXTURE0);
		SetShaderInt(ViewModelPointsTextureShader, "texture0", 0);
		
		glBindTexture(GL_TEXTURE_2D, ObjectTextureID);
		usedShader = ViewModelPointsTextureShader;
	}
	
	SetShaderVec3(usedShader, "colour", ObjectColour);
	SetShaderMat4(usedShader, "view", PhysicsEngine::viewMatrix());

	mat4 modelMatrix = ParentObject()->GetComponent<Transform*>()->getModelMatrix();
	SetShaderMat4(usedShader, "model", modelMatrix);

	PointLight::ApplyPointLights(usedShader);
	DirectionalLight::ApplyDirectionalLights(usedShader);

	glDrawArrays(GL_TRIANGLES, 0, ObjectDrawSize);	
}