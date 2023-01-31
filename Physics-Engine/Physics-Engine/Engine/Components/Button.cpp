#include <Engine/Engine.h>
#include <Engine/Components/Button.h>

#include <GLM/gtc/matrix_transform.hpp>

#include <Engine/Background/Shaders.h>

void Button::Mainloop() {
	Initialise();

	Render();
	UpdateClicks();
}
void Button::Initialise() {

	if (initialised) {
		return;
	}

	InitialiseVertices();
	ButtonTextureID = LoadTexture(texturePath.data());
	
	initialised = true;
}

void Button::UpdateClicks() {
	mat4 CurrentModelMatrix = GetUIMatrix();
	CurrentColourMultiplier = 1.0f;

	vec2 PointOne = CurrentModelMatrix * vec4(-1.0f, -1.0f, 0.0f, 1.0f);
	vec2 PointTwo = CurrentModelMatrix * vec4(-1.0f, 1.0f, 0.0f, 1.0f);
	vec2 PointThree = CurrentModelMatrix * vec4(1.0f, -1.0f, 0.0f, 1.0f);
	vec2 PointFour = CurrentModelMatrix * vec4(1.0f, 1.0f, 0.0f, 1.0f);

	Transform* ParentTransform = ParentObject()->GetComponent<Transform*>();
	Scene* currentScene = &PhysicsEngine::loadedScenes[PhysicsEngine::currentScene];
	map<string, Object>* sceneObjects = &currentScene->SceneObjects;

	bool ClickedButtonOverlaying = false;
	for (map<string, Object>::iterator it = sceneObjects->begin(); it != sceneObjects->end(); it++) {
		if (it->first == ParentObjectName) {
			continue;
		}

		if (it->second.HasComponent<Button>()) {
			if (it->second.GetComponent<Transform*>()->position.z < ParentTransform->position.z) {
				Button* secondButton = it->second.GetComponent<Button*>();
				
				if (secondButton->LastFrameClickUpdate != PhysicsEngine::frameNumber) {
					secondButton->UpdateClicks();
				}

				if (secondButton->ClickedLastFrame || secondButton->ButtonPressedDown || secondButton->ButtonClicked) {
					ClickedButtonOverlaying = true;
				}
			}
		}
	}

	if (ClickedButtonOverlaying) {
		LastFrameClickUpdate = PhysicsEngine::frameNumber;
		ClickedLastFrame = false;
		return;
	}

	// On Click Logic
	bool MouseOverButton = Collider::pointInTriangle(PhysicsEngine::DisplayMousePosition, PointOne, PointTwo, PointThree) || Collider::pointInTriangle(PhysicsEngine::DisplayMousePosition, PointFour, PointTwo, PointThree);

	bool OldClicked = ClickedLastFrame;
	if (PhysicsEngine::MouseLeftDown) {
		if (MouseOverButton) {
			ClickedLastFrame = true;
			ButtonPressedDown = true;
			CurrentColourMultiplier = ClickColourMultiplier;
		}
		else {
			ClickedLastFrame = false;
		}
	}
	else {
		ClickedLastFrame = false;
		ButtonPressedDown = false;

		if (MouseOverButton) {
			CurrentColourMultiplier = HoverColourMultiplier;
		}
	}
	
	if (OldClicked && !ClickedLastFrame) {
		if (ButtonOnClickFunction != nullptr) {
			ButtonOnClickFunction();
		}
		ButtonClicked = true;
	}
	else {
		ButtonClicked = false;
	}

	LastFrameClickUpdate = PhysicsEngine::frameNumber;
}

mat4 Button::GetUIMatrix() {
	Transform* objectTransform = ParentObject()->GetComponent<Transform*>();

	mat4 newModelMatrix = mat4(1.0f);
	newModelMatrix = translate(newModelMatrix, objectTransform->position);

	vec3 newScale = objectTransform->scale;
	newModelMatrix = scale(newModelMatrix, vec3(PhysicsEngine::displayHeight / PhysicsEngine::displayWidth, 1.0f, 1.0f));

	vec3 rotation = objectTransform->rotation;
	newModelMatrix = rotate(newModelMatrix, radians(rotation.x), vec3(1.0f, 0.0f, 0.0f));
	newModelMatrix = rotate(newModelMatrix, radians(rotation.y), vec3(0.0f, 1.0f, 0.0f));
	newModelMatrix = rotate(newModelMatrix, radians(rotation.z), vec3(0.0f, 0.0f, 1.0f));
	
	newModelMatrix = scale(newModelMatrix, newScale);

	return newModelMatrix;
}
void Button::Render() {
	mat4 modelMatrix = GetUIMatrix();
	
	// Render
	glBindVertexArray(ButtonVAO);
	glUseProgram(ButtonShader);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, ButtonTextureID);
	SetShaderInt(ButtonShader, "texture0", 0);

	SetShaderVec3(ButtonShader, "colour", ButtonColour * vec3(CurrentColourMultiplier));
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
