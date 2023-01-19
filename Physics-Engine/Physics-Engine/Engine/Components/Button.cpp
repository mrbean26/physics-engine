#include <Engine/Engine.h>
#include <Engine/Components/Button.h>

#include <GLM/gtc/matrix_transform.hpp>

#include <Engine/Background/Shaders.h>

void Button::Mainloop() {
	Initialise();

	Render();
}
void Button::Initialise() {
	if (initialised) {
		return;
	}

	InitialiseVertices();
	ButtonTextureID = LoadTexture(texturePath.data());

	initialised = true;
}

mat4 Button::GetUIMatrix() {
	Transform* objectTransform = parentObject->GetComponent<Transform*>();

	mat4 newModelMatrix = mat4(1.0f);
	newModelMatrix = translate(newModelMatrix, objectTransform->position);

	vec3 newScale = objectTransform->scale * vec3(PhysicsEngine::displayHeight / PhysicsEngine::displayWidth, 1.0f, 1.0f);
	newModelMatrix = scale(newModelMatrix, newScale);

	return newModelMatrix;
}
void Button::Render() {
	mat4 modelMatrix = GetUIMatrix();

	// Render
	glBindVertexArray(ButtonVAO);
	glUseProgram(ButtonShader);

	glActiveTexture(GL_TEXTURE0);
	SetShaderInt(ButtonShader, "texture0", 0);

	SetShaderVec3(ButtonShader, "colour", ButtonColour);
	SetShaderMat4(ButtonShader, "model", modelMatrix);

	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Button::InitialiseShader() {
	int vertex = CreateShader("Assets/Shaders/Button_v.txt", GL_VERTEX_SHADER);
	int fragment = CreateShader("Assets/Shaders/Button_f.txt", GL_FRAGMENT_SHADER);

	ButtonShader = CreateProgram({ vertex, fragment });
}
void Button::InitialiseVertices() {
	if (ButtonVAO > -1) {
		return;
	}

	vector<float> buttonVertices = {
		-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
		-1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		1.0f, -1.0f, 0.0f, 1.0f, 0.0f,

		-1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 
		1.0f, 1.0f, 0.0f, 1.0f, 1.0f
	};

	glGenVertexArrays(1, &ButtonVAO);
	glBindVertexArray(ButtonVAO);

	glGenBuffers(1, &ButtonVBO);
	glBindBuffer(GL_ARRAY_BUFFER, ButtonVBO);

	glBufferData(GL_ARRAY_BUFFER, buttonVertices.size() * sizeof(float), buttonVertices.data(), GL_STATIC_DRAW);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	InitialiseShader();
}
