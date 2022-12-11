#include <Engine/Components/ViewModel.h>
#include <Engine/Background/Shaders.h>
#include <Engine/Engine.h>

void ViewModel::Mainloop() {
	Initialise();
	Render();
}
void ViewModel::Initialise() {
	if (initialised) {
		return;
	}
	
	// Set Shaders To Uninitialised
	initialiseShader();
	InitialiseVertices();
}

void ViewModel::initialiseShader() {
	if (verticesType == VERTICES_POINTS_ONLY && ViewModelPointsShader == -1) {
		int vertex = CreateShader("Assets/Shaders/ViewModelPoints_v.txt", GL_VERTEX_SHADER);
		int fragment = CreateShader("Assets/Shaders/ViewModelPoints_f.txt", GL_FRAGMENT_SHADER);

		ViewModelPointsShader = CreateProgram({ vertex, fragment });
	}
	if (verticesType == VERTICES_POINTS_COLOURS && ViewModelPointsColourShader == -1) {
		int vertex = CreateShader("Assets/Shaders/ViewModelPointsColours_v.txt", GL_VERTEX_SHADER);
		int fragment = CreateShader("Assets/Shaders/ViewModelPointsColours_f.txt", GL_FRAGMENT_SHADER);

		ViewModelPointsShader = CreateProgram({ vertex, fragment });
	}
	if (verticesType == VERTICES_POINTS_TEXTURE && ViewModelPointsTextureShader == -1) {
		int vertex = CreateShader("Assets/Shaders/ViewModelPointsTexture_v.txt", GL_VERTEX_SHADER);
		int fragment = CreateShader("Assets/Shaders/ViewModelPointsTexture_f.txt", GL_FRAGMENT_SHADER);

		ViewModelPointsShader = CreateProgram({ vertex, fragment });
	}
	if (verticesType == VERTICES_POINTS_COLOUR_TEXTURE && ViewModelPointsColourTextureShader == -1) {
		int vertex = CreateShader("Assets/Shaders/ViewModelPointsColoursTexture_v.txt", GL_VERTEX_SHADER);
		int fragment = CreateShader("Assets/Shaders/ViewModelPointsColoursTexture_f.txt", GL_FRAGMENT_SHADER);

		ViewModelPointsShader = CreateProgram({ vertex, fragment });
	}
}

void ViewModel::InitialiseVertices() {
	glGenVertexArrays(1, &ObjectVAO);
	glBindVertexArray(ObjectVAO);

	glGenBuffers(1, &ObjectVBO);
	glBindBuffer(GL_ARRAY_BUFFER, ObjectVBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

	if (verticesType == VERTICES_POINTS_ONLY) {
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		ObjectDrawSize = vertices.size() / 3;
	}
	if (verticesType == VERTICES_POINTS_COLOURS) {
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		ObjectDrawSize = vertices.size() / 6;
	}
	if (verticesType == VERTICES_POINTS_TEXTURE) {
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)3);
		glEnableVertexAttribArray(1);

		ObjectDrawSize = vertices.size() / 5;
	}
	if (verticesType == VERTICES_POINTS_COLOUR_TEXTURE) {
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)3);
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)6);
		glEnableVertexAttribArray(2);

		ObjectDrawSize = vertices.size() / 8;
	}
}

mat4 ViewModel::getModelMatrix() {
	return mat4(1.0f);
}
void ViewModel::Render() {
	glBindVertexArray(ObjectVAO);
	GLuint usedShader;

	if (verticesType == VERTICES_POINTS_ONLY) {
		glUseProgram(ViewModelPointsShader);
		SetShaderVec3(ViewModelPointsShader, "colour", ObjectColour);
		usedShader = ViewModelPointsShader;
	}
	if (verticesType == VERTICES_POINTS_COLOURS) {
		glUseProgram(ViewModelPointsColourShader);
		SetShaderVec3(ViewModelPointsColourShader, "colour", ObjectColour);
		usedShader = ViewModelPointsColourShader;
	}
	if (verticesType == VERTICES_POINTS_TEXTURE) {
		glUseProgram(ViewModelPointsTextureShader);
		SetShaderVec3(ViewModelPointsColourShader, "colour", ObjectColour);
		glBindTexture(GL_TEXTURE_2D, ObjectTextureID);
		usedShader = ViewModelPointsTextureShader;
	}
	if (verticesType == VERTICES_POINTS_COLOUR_TEXTURE) {
		glUseProgram(ViewModelPointsColourTextureShader);
		SetShaderVec3(ViewModelPointsColourTextureShader, "colour", ObjectColour);
		usedShader = ViewModelPointsColourTextureShader;
	}

	SetShaderMat4(usedShader, "view", PhysicsEngine::viewMatrix());
	SetShaderMat4(usedShader, "projection", PhysicsEngine::projectionMatrix());
	SetShaderMat4(usedShader, "model", getModelMatrix());

	glDrawArrays(GL_TRIANGLES, 0, ObjectDrawSize);	
}