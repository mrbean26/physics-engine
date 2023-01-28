#include <Engine/Engine.h>
#include <Engine/Components/Scrollbar.h>

#include <GLM/gtc/matrix_transform.hpp>

void Scrollbar::Mainloop() {
	Initialise();

	UpdateObjectTransforms();
}
void Scrollbar::Initialise() {
	if (initialised) {
		return;
	}
	
	CreateSubObjects();

	initialised = true;
}

void Scrollbar::CreateSubObjects() {
	PhysicsEngine::loadedScenes[PhysicsEngine::currentScene].GetSceneObjectByID(parentObject->name)->AddComponent<Button>();
	PhysicsEngine::loadedScenes[PhysicsEngine::currentScene].GetSceneObjectByID(parentObject->name)->GetComponent<Button*>()->texturePath = ScrollbarBackgroundTexturePath;

	ScrollbarSlider = PhysicsEngine::loadedScenes[PhysicsEngine::currentScene].CreateSceneObject((string(parentObject->name) + "_ScrollbarSlider").data());
	ScrollbarSlider->AddComponent<Button>();
	ScrollbarSlider->GetComponent<Button*>()->texturePath = ScrollbarSliderTexturePath;
	ScrollbarSlider->GetComponent<Transform*>()->scale = ScrollbarSliderScale;
}
mat4 Scrollbar::GetUIMatrix() {
	Transform* ParentTransform = parentObject->GetComponent<Transform*>();

	mat4 NewMatrix = mat4(1.0f);
	NewMatrix = translate(NewMatrix, ParentTransform->position);

	vec3 newScale = ParentTransform->scale * vec3(PhysicsEngine::displayHeight / PhysicsEngine::displayWidth, 1.0f, 1.0f);
	NewMatrix = scale(NewMatrix, newScale);

	vec3 rotation = ParentTransform->rotation;
	NewMatrix = rotate(NewMatrix, radians(rotation.x), vec3(1.0f, 0.0f, 0.0f));
	NewMatrix = rotate(NewMatrix, radians(rotation.y), vec3(0.0f, 1.0f, 0.0f));
	NewMatrix = rotate(NewMatrix, radians(rotation.z), vec3(0.0f, 0.0f, 1.0f));

	return NewMatrix;
}
void Scrollbar::UpdateObjectTransforms() {
	Transform* ParentTransform = parentObject->GetComponent<Transform*>();
	
	vec2 NewPosition = PhysicsEngine::DisplayMousePosition;
	mat4 TransformationMatrix = GetUIMatrix();

	// Generate Bound Points For Slider Position ("Right" and "Left")
	TransformationMatrix = translate(TransformationMatrix, vec3(-1.0f, 0.0f, 0.0f));
	vec2 MinimumPoint = TransformationMatrix * vec4(0.0f, 0.0f, 0.0f, 1.0f);

	TransformationMatrix = translate(TransformationMatrix, vec3(2.0f, 0.0f, 0.0f));
	vec2 MaximumPoint = TransformationMatrix * vec4(0.0f, 0.0f, 0.0f, 1.0f);

	vec2 VectorDeltas = MaximumPoint - MinimumPoint;
	
	if (ScrollbarSlider->GetComponent<Button*>()->ClickedLastFrame) {
		// Solve (for lambda) A Vector Equation r = min + lambda (max - min) to find closest point on line of slider path to shift it
		ScrollbarValue = (VectorDeltas.x * (NewPosition.x - MinimumPoint.x) + VectorDeltas.y * (NewPosition.y - MinimumPoint.y)) / (powf(VectorDeltas.x, 2.0f) + powf(VectorDeltas.y, 2.0f));
		ScrollbarValue = glm::clamp(ScrollbarValue, 0.0f, 1.0f);
	}

	vec2 NewSliderPosition = MinimumPoint + ScrollbarValue * VectorDeltas;
	ScrollbarSlider->GetComponent<Transform*>()->position = vec3(NewSliderPosition, ParentTransform->position.z - 0.05f);
	ScrollbarSlider->GetComponent<Transform*>()->scale = ParentTransform->scale * ScrollbarSliderScale;
}